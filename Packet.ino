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

cPacket::cPacket()
{
  built = true;
}
////////////////////////////////////////////////////////////

/**
 * @brief Get the function ID from a given packet.
 * @param packetID 
 * @return Execution 
 */
Execution cPacket::GetID(unsigned short* packet, int packetSize, unsigned char* packetID)
{
    Execution execution;
    int returnedType = 255;
    unsigned char returnedByte = 255;
    unsigned short firstChunk = packet[0];

    execution = Chunk.ToType(firstChunk, &returnedType);
    if(execution != Execution::Passed)
    {
        // INCORRECT CHUNK TYPE GOTTEN
        return Execution::Incompatibility;
    }

    if(returnedType != ChunkType::Start)
    {
        // First chunk of the packet is not a start chunk
        return Execution::Failed;
    }

    execution = Chunk.ToByte(packet[0], &returnedByte);
    if(execution != Execution::Passed)
    {
        // Function failed to execute
        return Execution::Failed;
    }

    // Success! ID was extracted
    *packetID = returnedByte;
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
    int resultedType = 255;
    unsigned char resultedByte = 255;

    if(packetSize < 2)
    {
        // What even are you trying to verify bruh
        return Execution::Crashed;
    }

    execution = Chunk.ToType(packet[packetSize-1], &resultedType);
    if(execution != Execution::Passed)
    {
        // Failed to get the type of that chunk
        return Execution::Crashed;
    }

    if(resultedType != ChunkType::Check)
    {
        // Incorrect chunk type returned
        return Execution::Incompatibility;
    }

    execution = Chunk.ToByte(packet[packetSize-1], &resultedByte);
    if(execution != Execution::Passed)
    {
        return Execution::Crashed;
    }

    if(resultedByte != checkSumToVerify)
    {
        return Execution::Failed;
    }

    return Execution::Passed;
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
    execution = GetID(packet, packetSize, &result);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("135:Packet -> Packet.GetID    ");
        return Execution::Crashed;
    }

    for(unsigned char currentID; currentID < _AMOUNT_OF_SUPPORTED_ID; currentID++)
    {
        if(supportedBFIOIDs[currentID] == result)
        {
            return Execution::Passed;
        }
    }

    return Execution::Incompatibility;
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
    int result = 0;
    unsigned char divisionCounter;
    divisionCounter = 0;
    *resultedParamCount = 0;

    if(packetSize < 4)
    {
        if(packetSize == 2)
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
            result = 0;
            execution = Chunk.ToType(packet[currentChunk], &result);
            if(execution != Execution::Passed)
            {
                // An error occured while checking for Div chunks
                Device.SetErrorMessage(DIV_COUNTING);
                return Execution::Crashed;
            }

            if(result == ChunkType::Div)
            {
                divisionCounter++;
            }
        }

        switch(divisionCounter)
        {
          case(0):
              Device.SetErrorMessage("Detected free bytes in packet");
              return Execution::Failed;
              break;
          
          default:
              *resultedParamCount = divisionCounter;
              return Execution::Passed;
        }
    }
}
/**
 * @brief Transform a variable converted to bytes
 * into a valid packet segment.
 * @attention
 * if the buffer is oversized, the rest will be
 * filled with 0s once the parameters boarded
 * the plane's class.
 * 
 * @param bytesToConvert
 * Passengers to put in seats 
 * @param resultedSegment 
 * The resulted plane segment of passengers.
 * @param byteCount 
 * How many passengers do we need to seat in the segment?
 * @param resultedSegmentSize
 * How much space is there for the seated passengers?
 * @return Execution 
 */
Execution cPacket::GetParameterSegmentFromBytes(unsigned char* bytesToConvert, unsigned short* resultedSegment, int byteCount, int resultedSegmentSize)
{
    Execution execution;
    unsigned char result = 255;
    unsigned short chunk = 0;

    if(resultedSegmentSize < (byteCount + 1))
    {
        Device.SetErrorMessage(INTERNAL_BUFFER_SIZE_ERROR);
        return Execution::Failed;
    }

    // Set first chunk as a div chunk
    resultedSegment[0] = ChunkType::Div;

    for(int currentByte = 0; currentByte < resultedSegmentSize; currentByte++)
    {
        if(currentByte < byteCount)
        {
            unsigned char byte = bytesToConvert[currentByte];
            execution = Chunk.ToChunk(byte, &chunk, ChunkType::Byte);
            if(execution != Execution::Passed)
            {
                Device.SetErrorMessage(INTERNAL_CHUNK_CONVERTION_FAIL);
                return Execution::Crashed;
            }
            resultedSegment[currentByte+1] = chunk;
        }
        else
        {
            // If the buffer is oversized, it will be filled with 0s.
            // resultedSegment[currentByte+1] = 0;
        }
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

    if(*sizeOfResult < (sizeOfFirstSegment + sizeOfSecondSegment))
    {
        Device.SetErrorMessage("287:Packet: Buffer too small  ");
        return Execution::Failed;
    }

    // Serial.println("\n\n\n");
    // Serial.println("[APPENDING]");
    // Serial.println("\n");
    // Serial.println("[FIRST]");
    for(int i=0; i<sizeOfFirstSegment; i++)
    {
        appendResult[i] = FirstSegment[i];
        // Serial.print("i: ");
        // Serial.print(i);
        // PrintChunk(FirstSegment[i]);
    }

    // Serial.println("\n");
    // Serial.println("[SECOND]");
    for(int i=0; i<sizeOfSecondSegment; i++)
    {
        appendResult[i+sizeOfFirstSegment] = secondSegment[i];
        // Serial.print("i: ");
        // Serial.print(i);
        // PrintChunk(appendResult[i+sizeOfFirstSegment]);
    }

    // Check last bytes just in case
    if(appendResult[sizeOfFirstSegment + sizeOfSecondSegment - 1] != secondSegment[sizeOfSecondSegment-1])
    {
        Device.SetErrorMessage("304:Packet: Mismatch found    ");
        return Execution::Failed;
    }

    // Check first byte just in case
    if(appendResult[0] != FirstSegment[0])
    {
        Device.SetErrorMessage("311:Packet: Mismatch found    ");
        return Execution::Failed;
    }
    // Serial.println("RESULT");
    // PrintOutPacket(appendResult, *sizeOfResult);
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
Execution cPacket::CreateFromSegments(unsigned char functionID, unsigned short* paramSegments, int sizeOfParamSegments, unsigned short* resultedPacket, int sizeOfResultedPacket)
{
    Execution execution;
    unsigned short chunkResult = 0;
    unsigned char checksum = functionID;
    unsigned char byteOfChunk = 0;
    int type = 0;
    bool requiresDivChunk = false;

    if(sizeOfResultedPacket < (sizeOfParamSegments+2))
    {
        Device.SetErrorMessage("335:Packet Buffer too small   ");
        return Execution::Crashed;
    }

    // Verify that the start of the parameter segment is a div chunk.
    execution = Chunk.ToType(paramSegments[0], &type);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("343:Packet Chunk.ToType      ");
        return Execution::Crashed;
    }

    if(type != ChunkType::Div)
    {
        Device.SetErrorMessage("349:Packet NoDivChunk         ");
        return Execution::Incompatibility;
    }

    // Attempting to convert functionID to Start chunk
    execution = Chunk.ToChunk(functionID, &chunkResult, ChunkType::Start);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("351:Packet Chunk.ToChunk      ");
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
            Device.SetErrorMessage("370:Packet Chunk.ToByte       ");
            return Execution::Failed;
        }

        checksum = checksum + byteOfChunk;
        resultedPacket[i+1] = paramSegments[i];
    }

    // Put checksum in packet
    execution = Chunk.ToChunk(checksum, &chunkResult, ChunkType::Check);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("387:Packet -> Chunk.ToChunk   ");
        return Execution::Crashed;
    }
    resultedPacket[sizeOfParamSegments+1] = chunkResult;
    return Execution::Passed;
}

/**
 * @brief Get the array of unsigned char values from
 * a plane's valid segment. the segment must start with
 * a Div Chunk.
 * 
 * @param paramSegment
 * The segment to extract bytes from 
 * @param sizeOfParameterSegment 
 * How many chunks total is in the segment?
 * @param resultedBytes 
 * Array where the extracted bytes from the segment will be placed.
 * @param sizeOfResultedBytes 
 * The extracted bytes array must be at least 1 less than the size
 * of the parameter segment.
 * @return Execution::Passed = Worked | Execution::Failed = Parameter segment is wrong | Execution::Crashed = Internal functions could not execute.
 */
Execution cPacket::GetBytesFromParameterSegment(unsigned short* paramSegment, int sizeOfParameterSegment, unsigned char* resultedBytes, int sizeOfResultedBytes)
{
    Execution execution;
        int resultedChunkType = 0;

    // - Test given buffer sizes - //
    if(sizeOfParameterSegment <= 1)
    {
        Device.SetErrorMessage("Packet:396");
        return Execution::Failed;
    }

    if(sizeOfResultedBytes < sizeOfParameterSegment-1)
    {
        Device.SetErrorMessage("Packet:402");
        return Execution::Failed;
    }

    // -  Check div chunk - //
    execution = Chunk.ToType(paramSegment[0], &resultedChunkType);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("Packet:421 -> Chunk.ToType");
        return Execution::Crashed;
    }

    if(resultedChunkType != ChunkType::Div)
    {
        Device.SetErrorMessage("Packet:427");
        return Execution::Failed;      
    }

    // - Convert to bytes - //
    for(int index = 1; index < sizeOfParameterSegment; index++)
    {
        unsigned char extractedByte = 0;
        unsigned short currentChunk = paramSegment[index];
        execution = Chunk.ToType(currentChunk, &resultedChunkType);
        if(execution != Execution::Passed)
        {
            Device.SetErrorMessage("Packet:428 -> Chunk.ToType");
            return Execution::Crashed;
        }

        if(resultedChunkType != ChunkType::Byte)
        {
            Device.SetErrorMessage("Packet:434");
            return Execution::Failed;
        }

        execution = Chunk.ToByte(currentChunk, &extractedByte);
        if(execution != Execution::Passed)
        {
            Device.SetErrorMessage("Packet:442 -> Chunk.ToByte");
            return Execution::Crashed;
        }

        resultedBytes[index-1] = extractedByte;
    }

    return Execution::Passed;
}

/**
 * @brief Gets a specific segment from a
 * given packet/plane in bytes.
 * A segment is an array of unsigned char
 * @param packet
 * An array of segment or parameter segment or validated packet to get an array of bytes from.
 * @param packetSize 
 * The size of the array to extract bytes from.
 * @param resultParameter 
 * Array of bytes where the parameter will be stored.
 * @param sizeOfResultParameter 
 * How much space is available to store that array.
 * @return Execution 
 */
Execution cPacket::GetBytes(unsigned short* packet, int packetSize, int segmentNumber, unsigned char* resultParameter, int sizeOfResultParameter)
{
    Execution execution;
    int extractedType = 0;
    unsigned char extractedByte = 0;
    unsigned char parameterSize = 0;
    unsigned char currentParameter = 0;
    int calculatedSizeOfParameter = 0;
    bool CheckChunkFound = false;
    bool StartChunkFound = false;
    bool divChunkFound = false;
    int indexAtWhichDivWasFound = 0;

    // if(sizeOfResultParameter < (packetSize-3)) // There is 3 useless passengers in there.
    // {
        // Device.SetErrorMessage("497:Packet Buffer too small   ");
        // 
        // return Execution::Failed;
    // }

    for (int index = 0; index < packetSize; index++)
    {
        unsigned short extractedChunk = packet[index];

        // - Check Type - //
        execution = Chunk.ToType(extractedChunk, &extractedType);
        if(execution != Execution::Passed)
        {
            Device.SetErrorMessage("503:Packet -> Chunk.ToType");
            return Execution::Crashed;
        }

        execution = Chunk.ToByte(extractedChunk, &extractedByte);
        if(execution != Execution::Passed)
        {
            Device.SetErrorMessage("512:Packet -> Chunk.ToByte");
            return Execution::Crashed;
        }

        switch(extractedType)
        {
            case(ChunkType::Start):
                if(!StartChunkFound)
                {
                    StartChunkFound = true;
                }
                else
                {
                    Device.SetErrorMessage("530:Packet -> Multiple Starts ");
                    return Execution::Failed;
                }
                break;
            case(ChunkType::Check):
                if(!CheckChunkFound)
                {
                    CheckChunkFound = true;
                }
                else
                {
                    Device.SetErrorMessage("527:Packet -> Multiple Ends   ");
                    return Execution::Crashed;
                }
                break;
            case(ChunkType::Byte):
                if(divChunkFound)
                {
                    // First byte
                    divChunkFound = false;
                }

                if(currentParameter == segmentNumber)
                {
                    calculatedSizeOfParameter++;
                    if(calculatedSizeOfParameter > sizeOfResultParameter)
                    {
                        Device.SetErrorMessage("539:Packet -> Param Too Big   ");
                        Serial.println(calculatedSizeOfParameter);
                        Device.SetStatus(Status::HardwareError);
                        return Execution::Crashed;
                    }
                    else
                    {
                        resultParameter[index - indexAtWhichDivWasFound] = extractedByte;
                    }
                }
                
                break;
            case(ChunkType::Div):
                if(!divChunkFound)
                {
                    // found the start of a parameter!
                    divChunkFound = true;
                    currentParameter++;

                    if(currentParameter == segmentNumber)
                    {
                        indexAtWhichDivWasFound = index+1;
                    }
                }
                else
                {
                    Device.SetErrorMessage("555:Packet -> Consecutive Divs");
                    return Execution::Crashed;
                }
                break;
        }
    }
    if(segmentNumber > currentParameter)
    {
        Device.SetErrorMessage("569:Packet -> Not Enough Param");
        return Execution::Failed;
    }

    return Execution::Passed;
}

/**
 * @brief Function that fully analyzes a
 * given packet of any size.
 * 
 * @param packetToAnalyze
 * The unkown packet that needs to be analyzed
 * @param resultedPacketsize 
 * The total size of the packet including start and check chunks.
 * @param amountOfParameters 
 * How many parameters were found in that pakcet.
 * @param packetID 
 * The extracted ID from the packet.
 * @return Execution::Passed = size found | Execution::Crashed = fatal analisis error | Execution::Incompatibility = Not in BFIO ids | Execution::Failed Something went wrong
 */
Execution cPacket::FullyAnalyze(unsigned short* packetToAnalyze, int* resultedPacketsize, int* amountOfParameters, unsigned char* packetID)
{
    Execution execution;
    int extractedType = 0;
    unsigned char extractedByte = 0;
    unsigned char extractedCheckSum = 0;
    unsigned char calculatedCheckSum = 0;
    int calculatedParamCount = 0;
    bool divChunkFound = false;
    bool StartChunkFound = false;
    bool CheckChunkFound = false;

    #pragma region STEP_1 = Can we get the ID successfully?
    execution = GetID(packetToAnalyze, 2, packetID);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("Packet:543 -> Packet.GetID    ");
        return Execution::Crashed;
    }
    #pragma endregion

    #pragma region STEP_2 = Is the second chunk a div chunk.
    execution = Chunk.ToType(packetToAnalyze[1], &extractedType);
    if(execution != Execution::Passed)
    {
        TestFailed("553:Packet -> Chunk.ToType    ");
        return Execution::Crashed;
    }

    if(extractedType != ChunkType::Div && extractedType != ChunkType::Check)
    {
        Device.SetErrorMessage("559:Packet -> Incorrect Chunk.");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region STEP_3 = Is the ID valid
    execution = VerifyID(packetToAnalyze, 2);
    if(execution != Execution::Passed)
    {
        if(execution == Execution::Incompatibility)
        {
            Device.SetErrorMessage("572:Packet: Unsupported Plane.");
            Device.SetStatus(Status::CompatibilityError);
            return Execution::Incompatibility;
        }

        Device.SetErrorMessage("569:Packet -> Packet.VerifyID");
        return Execution::Crashed;
    }
    #pragma endregion

    #pragma region STEP_4 = If plane is empty, get checksum, compare and return immediately.
    if(extractedType == ChunkType::Check)
    {
        *resultedPacketsize = 2;
        *amountOfParameters = 0;


        execution = Chunk.ToByte(packetToAnalyze[1], &extractedCheckSum);
        if(execution != Execution::Passed)
        {
            Device.SetErrorMessage("575:Packet -> Chunk.ToByte");
            return Execution::Crashed;
        }

        if(extractedCheckSum != *packetID)
        {
            Device.SetErrorMessage("581:Packet -> Checksm mismatch");
            return Execution::Failed;
        }

        return Execution::Passed;
    }
    #pragma endregion

    #pragma region STEP_5 = Calculate checksum, check div segments until checkChunk is found.
    for (int index = 0; index < MAX_PLANE_PASSENGER_CAPACITY; index++)
    {
        unsigned short UNSAFE_extractedChunk = packetToAnalyze[index];

        // - Check Type - //
        execution = Chunk.ToType(UNSAFE_extractedChunk, &extractedType);
        if(execution != Execution::Passed)
        {
            Device.SetErrorMessage("618:Packet -> Chunk.ToType");
            return Execution::Crashed;
        }

        // - Extract byte - //
        execution = Chunk.ToByte(UNSAFE_extractedChunk, &extractedByte);
        if(execution != Execution::Passed)
        {
            Device.SetErrorMessage("674:Packet -> Chunk.ToByte");
            return Execution::Crashed;
        }

        switch(extractedType)
        {
            case(ChunkType::Start):
                if(!StartChunkFound)
                {
                    StartChunkFound = true;
                    *packetID = extractedByte;
                }
                else
                {
                    Device.SetErrorMessage("631:Packet -> Multiple Starts ");
                    return Execution::Failed;
                }
                break;
            case(ChunkType::Check):
                if(!CheckChunkFound)
                {
                    CheckChunkFound = true;
                    extractedCheckSum = extractedByte;
                    *amountOfParameters = calculatedParamCount;
                    *resultedPacketsize = index+1;

                    if(calculatedCheckSum != extractedCheckSum)
                    {
                        Device.SetErrorMessage("655:Packet -> Invalid checksum");
                        return Execution::Failed;
                    }
                    else
                    {
                        // YOUPIIIII
                        return Execution::Passed;
                    }
                }
                else
                {
                    Device.SetErrorMessage("643:Packet -> Multiple Ends   ");
                    return Execution::Crashed;
                }
                break;
            case(ChunkType::Byte):
                if(divChunkFound)
                {
                    // First byte
                    divChunkFound = false;
                }
                break;
            case(ChunkType::Div):
                if(!divChunkFound)
                {
                    // found the start of a parameter!
                    divChunkFound = true;
                    calculatedParamCount++;
                }
                else
                {
                    Device.SetErrorMessage("664:Packet -> Consecutive Divs");
                    return Execution::Crashed;
                }
                break;
        }
    
        // - calculate checksum - //
        calculatedCheckSum = calculatedCheckSum + extractedByte;
    }
    #pragma endregion

    // Hum... well that isnt good...
    Device.SetErrorMessage("697:Packet -> Corrupted Plane.");
    return Execution::Crashed;
}
#pragma endregion