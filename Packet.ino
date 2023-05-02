/**
 * @file Packet.ino
 * @author Lyam (Lyam.brs@gmail.com)
 * @brief stores the backend of the
 * class declared in the header file.
 * @version 0.1
 * @date 2023-05-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*  ############    ############     ##########
    ############    ############     ##########
              ##              ##   ## 
    ####    ##      ####    ##     ############
    ####    ##      ####    ##     ############
              ##              ##             ##
    ############    ####      ##   ##########
    ############    ####      ##   ##########*/

#pragma region  Include
#include "Packet.h"
#pragma endregion

#pragma region Class
cPacket::cPacket();
////////////////////////////////////////////////////////////

/**
 * @brief Get the function ID from a given packet.
 * @param packetID 
 * @return Execution 
 */
Execution cPacket::GetID(unsigned short* packet, int packetSize, unsigned char* packetID)
{
    Execution execution;
    unsigned char returned = 255;

    execution = Chunk.ToType(packet[0], &returned);
    if(execution != Execution::Passed)
    {
        // INCORRECT CHUNK TYPE GOTTEN
        return Execution::Incompatibility;
    }

    if(returned != ChunkType::Start)
    {
        // First chunk of the packet is not a start chunk
        return Execution::Failed;
    }

    execution = Chunk.ToByte(packet[0], &returned);
    if(execution != Execution::Passed)
    {
        // Function failed to execute
        return Execution::Failed;
    }

    // Success! ID was extracted
    *packetID = returned;
    return Execution::Passed;
}

/**
 * @brief Check if a given checksum corresponds
 * to a given packet's checksum.
 * 
 * @param packet 
 * @param packetSize
 * @param checkSumToverify 
 * @return Execution 
 */
Execution cPacket::VerifyCheckSum(unsigned short* packet, int packetSize, unsigned char checkSumToVerify)
{
    Execution execution;
    unsigned char result = 255;

    execution = Chunk.ToType(packet[packetSize-1], &result);
    if(execution != Execution::Passed)
    {
        // Failed to get the type of that chunk
        return Execution::Crashed;
    }

    if(result != ChunkType::Check)
    {
        // Incorrect chunk type returned
        return Execution::Incompatibility;
    }

    execution = Chunk.ToByte(packet[packetSize-1], &result);
    if(execution != Execution::Passed)
    {
        return Execution::Crashed;
    }

    if(result != checkSumToVerify)
    {
        return Execution::Failed;
    }

    return Execution::Passed
}
/**
 * @brief Check if the ID of a given packet
 * corresponds to the list of supported IDs of
 * your device.
 * @param packet 
 * @param packetSize 
 * @return Execution 
 */
Execution cPacket::VerifyID(unsigned short* packet, int packetSize)
{
    Execution execution;
    unsigned char result = 255;

    // Get ID from packet
    execution GetID(packet, packetSize, &result);
    if(execution != Execution::Passed)
    {
        return execution;
    }

    for(unsigned char currentID; currentID < _AMOUNT_OF_SUPPORTED_ID; currentID++)
    {
        if(supportedBFIOIDs[currentID] == result)
        {
            return Execution::Passed;
        }
    }

    return Execution::Failed;
}
/**
 * @brief Gets the amount of parameters inside
 * a packet.
 * @param packet 
 * @param packetSize 
 * @param resultedParamCount 
 * @return Execution 
 */
Execution cPacket::GetAmountOfParameters(unsigned short* packet, int packetSize, unsigned char* resultedParamCount)
{
    Execution execution;
    unsigned char result = 0;
    unsigned char divCounter = 0;

    if(packetSize < 4)
    {
        if(packetSize <= 2)
        {
            *resultedParamCount = 0;
            return Execution::Unecessary;
        }
    
        if(packetSize == 3)
        {
            // Div chunk but no byte chunk??
            *resultedParamCount = 0;
            return Execution::Failed;
        }

        return Execution::Failed;
    }
    else
    {
        for(int currentChunk = 0; currentChunk < packetSize; currentChunk++)
        {
            execution = Chunk.ToType(packet[currentChunk], &result);
            if(execution != Execution::Passed)
            {
                // An error occured while checking for Div chunks
                Device.SetErrorMessage(DIV_COUNTING);
                return Execution::Crashed;
            }

            if(result == ChunkType::Div)
            {
                divCounter++;
            }
        }

        if(divCounter == 0)
        {
            Device.SetErrorMessage(FREE_BYTES_IN_PACKET);
            return Execution::Failed;
        }
        else
        {
            *resultedParamCount = divCounter;
        }
    }
}
/**
 * @brief Transform a variable converted to bytes
 * into a valid packet segment.
 * @param bytesToConvert 
 * @param resultedSegment 
 * @param byteCount 
 * @param resultedSegmentSize 
 * @return Execution 
 */
Execution cPacket::GetParameterSegmentFromBytes(unsigned char* bytesToConvert, unsigned short* resultedSegment, int* byteCount, int* resultedSegmentSize)
{
    Execution execution;
    unsigned char result = 255;
    unsigned short chunk = 0;

    if(resultedSegmentSize != (byteCount + 1))
    {
        Device.SetStatus(INTERNAL_BUFFER_SIZE_ERROR);
        return Execution::Failed;
    }

    // Set first chunk as a div chunk
    resultedSegment[0] = ChunkType::Div;

    for(unsigned char currentByte = 0; currentByte<byteCount; currentByte++)
    {
        unsigned char byte = bytesToConvert[currentByte];
        execution = Chunk.ToChunk(byte, &chunk, ChunkType::Byte);
        if(execution != Execution::Passed)
        {
            Device.SetErrorMessage("INTERNAL CHUNK CONVERTION FAIL");
            return Execution::Crashed;
        }

        resultedSegment[currentByte+1] = chunk;
    }

    return Execution::Passed;
}
/**
 * @brief Combine 2 segments togheter into 1 array of chunks.
 * This is used to slowly build your packet using all the
 * different segments created from variables
 * @param FirstSegment 
 * @param sizeOfFirstSegment 
 * @param secondSegment 
 * @param sizeOfSecondSegment 
 * @param appendResult 
 * @param sizeOfResult 
 * @return Execution 
 */
Execution cPacket::AppendSegments(unsigned short* FirstSegment, int sizeOfFirstSegment, unsigned short* secondSegment, int sizeOfSecondSegment, unsigned short* appendResult, int* sizeOfResult)
{
    Execution execution;

    if(sizeOfResult != (sizeOfFirstSegment + sizeOfSecondSegment))
    {
        Device.SetErrorMessage(INTERNAL_BUFFER_SIZE_ERROR);
        return Execution::Failed;
    }

    for(int i=0; i<sizeOfFirstSegment; i++)
    {
        appendResult[i] = FirstSegment[i];
    }

    for(int i=sizeOfFirstSegment; i<sizeOfResult; i++)
    {
        appendResult[i] = secondSegment[i-sizeOfFirstSegment];
    }

    // Check last bytes just in case
    if(appendResult[sizeOfResult-1] != secondSegment[sizeOfSecondSegment-1])
    {
        Device.SetErrorMessage(INTERNAL_PACKET_BUILDING_FAIL);
        return Execution::Failed;
    }
    return Execution::Passed;
}
/**
 * @brief Transform an array of segments into
 * a valid packet. This creates the start chunk
 * and the check chunk automatically.
 * @param functionID
 * The ID to give to the start chunk of the packet
 * @param paramSegments 
 * The array of parameter segments created from AppendSegments
 * @param sizeOfParamSegments 
 * The size of the paramSegments array.
 * @param resultedPacket 
 * Pointer to where the resulted packet will be stored
 * @param sizeOfResultedPacket 
 * Available size needed to store the resulted packet.
 * @return Execution 
 */
Execution cPacket::CreateFromSegments(unsigned char functionID, unsigned short* paramSegments, int sizeOfParamSegments, unsigned short* resultedPacket, int* sizeOfResultedPacket)
{
    Execution execution;
    unsigned short chunkResult = 0;
    unsigned char checksum = functionID;
    unsigned char byteOfChunk = 0;

    if(sizeOfResultedPacket != (paramSegments+2))
    {
        Device.SetErrorMessage(INTERNAL_BUFFER_SIZE_ERROR);
        return Execution::Crashed;
    }

    // Attempting to convert functionID to Start chunk
    execution = Chunk.ToChunk(functionID, &chunkResult, ChunkType::Start);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage(INTERNAL_CHUNK_CONVERTION_FAIL);
        return Execution::Crashed;
    }
    resultedPacket[0] = chunkResult;

    // Calculate checksum and save chunks in resultedChunk
    for(int i=0; i<sizeOfParamSegments; i++)
    {
        unsigned short currentChunk = paramSegments[i];
        execution = Chunk.ToByte(currentChunk, &byteOfChunk);
        if(execution != Execution::Passed)
        {
            Device.SetErrorMessage(INTERNAL_PACKET_BUILDING_FAIL);
            return Execution::Failed;
        }

        checksum = checksum + byteOfChunk;
        resultedPacket[i+1] = paramSegments[i];
    }

    // Put checksum in packet
    execution = Chunk.ToChunk(checksum, &chunkResult, ChunkType::Check);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage(INTERNAL_CHUNK_CONVERTION_FAIL);
        return Execution::Crashed;
    }
    resultedPacket[sizeOfResultedPacket-1] = chunkResult;
    return Execution::Passed;
}

/**
 * @brief Get a segment from a packet with only 1 segment.
 * A segment is an array of unsigned char
 * @param packet 
 * @param packetSize 
 * @param resultParameter 
 * @param sizeOfResultParameter 
 * @return Execution 
 */
Execution cPacket::GetParametersFromPacket(unsigned short* packet, int packetSize, unsigned char* resultParameter, int sizeOfResultParameter)
{
    Execution execution = 0;

    if(sizeOfResultParameter < (packetSize-3)) // There is 3 useless passengers in there.
    {
        Device.SetErrorMessage(INTERNAL_BUFFER_SIZE_ERROR);
        return Execution::Failed;
    }

    // Get the singular passenger class from the plane
    for(int i=2; i<sizeOfResultParameter; i++)
    {
        unsigned char result = 0;
        unsigned short chunk = packet[i];
        // Get the type
        execution = Chunk.ToType(chunk, &result);
        if(execution != Execution::Passed)
        {
            Device.SetErrorMessage(INTERNAL_CHUNK_CONVERTION_FAIL);
            return Execution::Crashed;
        }

        // There is other types of chunk in this singular parameter function? Huh...
        if(result != ChunkType::Byte)
        {
            Device.SetErrorMessage("INTERNAL param conversion fail");
            return Execution::Crashed; 
        }

        // Convert to byte
        execution = Chunk.ToByte(chunk, &result);
        if(execution != Execution::Passed)
        {
            Device.SetErrorMessage(INTERNAL_CHUNK_CONVERTION_FAIL);
            return Execution::Crashed;
        }

        resultParameter[i-2] = result;
    }
    return Execution::Passed;
}

#pragma endregion