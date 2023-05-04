/**
 * @file _UNIT_TEST_Packet.ino
 * @author Lyam (lyam.brs@gmail.com)
 * @brief This file contains the various
 * definitions of unit test functions used
 * to verify that the Chunk class functions
 * as intended.
 * @version 0.1
 * @date 2023-04-27
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

#include "Globals.h"

/**
 * @brief Tests if the packet class
 * can successfully gather the ID
 * of valid predetermined packets / planes
 * 
 * @return Execution 
 */
Execution TEST_PACKET_GetID()
{
    TestStart("GetID");
    Execution execution;
    unsigned char extractedID = 0;

    // - Packets used for the tests - //
                                     // Start: ID = 0  // Div              // Byte A: 255        // Check: 255
    unsigned short planeA[4]         = {0b0000001000000000, 0b0000000100000000, 0b0000000011111111, 0b0000001111111111};
    unsigned short badPlaneA[4]      = {0b0000001100000000, 0b0000000100000000, 0b0000000011111111, 0b0000001111111111};
    unsigned short badPlaneB[4]      = {0b0000000100000000, 0b0000000100000000, 0b0000000011111111, 0b0000001111111111};
    unsigned short badPlaneC[4]      = {0b0000000000000000, 0b0000000100000000, 0b0000000011111111, 0b0000001111111111};
    unsigned short corruptedPlane[4] = {0b0111001000011000, 0b0000000100000000, 0b0000000011111111, 0b0000001111111111};

    #pragma region -255 possible packet IDs-
    for (int i=0; i<255; ++i)
    {
        unsigned short newStartChunk = 0;
        unsigned char extractedID = 0;

        // Build start chunk:
        execution = Chunk.ToChunk((unsigned char)i, &newStartChunk, ChunkType::Start);
        TestStepDone();
        if(execution != Execution::Passed)
        {
            TestFailed("Chunk.ToChunk failed to create start chunk from given parameters");
            return Execution::Failed;
        }

        // Chunk built, changing packet with new start chunk
        planeA[0] = newStartChunk;

        // Testing ID extraction from the new plane.
        execution = Packet.GetID(planeA, 4, &extractedID);
        TestStepDone();
        if(execution != Execution::Passed)
        {
            TestFailed("Packet.GetID returned unexpected execution result from correct parameters");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region -Invalid packets starts-

    execution = Packet.GetID(badPlaneA, 4, &extractedID);
    TestStepDone();
    if(execution != Execution::Failed)
    {
        TestFailed("Execution::Failed not returned after badPlaneA was given.");
        return Execution::Failed;
    }

    execution = Packet.GetID(badPlaneB, 4, &extractedID);
    TestStepDone();
    if(execution != Execution::Failed)
    {
        TestFailed("Execution::Failed not returned after badPlaneB was given.");
        return Execution::Failed;
    }

    execution = Packet.GetID(badPlaneC, 4, &extractedID);
    TestStepDone();
    if(execution != Execution::Failed)
    {
        TestFailed("Execution::Failed not returned after badPlaneC was given.");
        return Execution::Failed;
    }

    #pragma endregion

    #pragma region -Corrupted Packets-
    execution = Packet.GetID(corruptedPlane, 4, &extractedID);
    TestStepDone();
    if(execution != Execution::Incompatibility)
    {
        TestFailed("Execution::Incompatibility not returned after corrupted plane was given.");
        return Execution::Failed;
    }
    #pragma endregion
    
    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Test to check the packet
 * class can successfully verify a
 * given checksum with a checksum from
 * valid predetermined packets.
 * 
 * @return Execution 
 */
Execution TEST_PACKET_VerifyCheckSum()
{
    TestStart("VerifyCheckSum");
    Execution execution;
    unsigned char wantedCheckSum = 0;

    // - Packets used for the tests - //
                                     // Start: ID = 0  // Div              // Byte A: 255        // Check: 255
    unsigned short planeA[4]         = {0b0000001000000000, 0b0000000100000000, 0b0000000011111111, 0b0000001111111111};
    
    #pragma region -Correct Checksums Verifications-
    for(unsigned char i=0; i<255; ++i)
    {
        // - Create new fake checksum - //
        unsigned short newChecksum = 0;
        execution = Chunk.ToChunk(i, &newChecksum, ChunkType::Check);
        TestStepDone();
        if(execution != Execution::Passed)
        {
            TestFailed("Unexpected execution returned from Chunk.ToChunk when creating CheckChunk.");
            return Execution::Failed;
        }

        // - Insert new checksum in packet - //
        planeA[3] = newChecksum;

        // - Verify checksum - //
        execution = Packet.VerifyCheckSum(planeA, 4, (unsigned char)i);
        TestStepDone();
        if(execution != Execution::Passed)
        {
            TestFailed("Incorrect execution returned when valid planed passed to Packet.VerifyCheckSum");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region -Incorrect Checksums Verifications-
    for(unsigned char i=0; i<255; ++i)
    {
        // - Create new fake checksum - //
        unsigned short newChecksum = 0;
        execution = Chunk.ToChunk(i, &newChecksum, ChunkType::Check);
        TestStepDone();
        if(execution != Execution::Passed)
        {
            TestFailed("Unexpected execution returned from Chunk.ToChunk when creating CheckChunk in Incorrect checksums");
            return Execution::Failed;
        }

        // - Insert new checksum in packet - //
        planeA[3] = newChecksum;

        // - Verify checksum - //
        execution = Packet.VerifyCheckSum(planeA, 4, (unsigned char)i-1);
        TestStepDone();
        if(execution != Execution::Failed)
        {
            TestFailed("Incorrect execution returned when incorrect planed passed to Packet.VerifyCheckSum");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region -Incorrect End Packet Verifications-
    execution = Packet.VerifyCheckSum(planeA, 3, 255);
    TestStepDone();
    if(execution != Execution::Incompatibility)
    {
        TestFailed("Function did not return Execution::Incopatibility when last valid chunk isnt CheckChunk.");
    }
    #pragma endregion

    #pragma region -Impossible Packet Verifications-
    planeA[3] = 0b0010001111111111;

    execution = Packet.VerifyCheckSum(planeA, 4, 255);
    TestStepDone();
    if(execution != Execution::Crashed)
    {
        TestFailed("Function did not return Execution::Crashed when last chunk is corrupted.");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region -Impossible packet sizes-
    planeA[3] = 0b0000000011111111;

    execution = Packet.VerifyCheckSum(planeA, 1, 1);
    TestStepDone();
    if(execution != Execution::Crashed)
    {
        TestFailed("Function did not return Execution::Crashed when specified packet size is impossible");
        return Execution::Failed;
    }
    #pragma endregion

    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Function that checks if the
 * packet class can successfully
 * identify valid predetermined packets
 * based on the list of IDs in BFIO.h
 * 
 * @return Execution 
 */
Execution TEST_PACKET_VerifyID()
{
    TestStart("VerifyID");
    Execution execution;

    // - Packets used for the tests - //
                                     // Start: ID = 0  // Div              // Byte A: 255        // Check: 255
    unsigned short planeA[4]         = {0b0000001000000000, 0b0000000100000000, 0b0000000011111111, 0b0000001111111111};
    

    #pragma region -Correct IDs-
    for(unsigned char index=0; index<_AMOUNT_OF_SUPPORTED_ID; ++index)
    {
        unsigned short newStartChunk = 0;
        unsigned char currentID = supportedBFIOIDs[index];

        // Build start chunk:
        execution = Chunk.ToChunk(currentID, &newStartChunk, ChunkType::Start);
        TestStepDone();
        if(execution != Execution::Passed)
        {
            TestFailed("Chunk.ToChunk failed to create start chunk from given parameters");
            return Execution::Failed;
        }

        // Chunk built, changing packet with new start chunk
        planeA[0] = newStartChunk;

        // Testing ID extraction from the new plane.
        execution = Packet.VerifyID(planeA, 4);
        TestStepDone();
        if(execution != Execution::Passed)
        {
            TestFailed("Packet.VerifyID returned unexpected execution result when given valid ID number.");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region -Incorrect ID-
    planeA[0] = 0b0000001011111111;
    execution = Packet.VerifyID(planeA, 4);
    TestStepDone();
    if(execution != Execution::Incompatibility)
    {
        TestFailed("Packet.VerifyID did not return Execution::Failed when invalid ID was given.");
        return Execution::Failed;
    }

    #pragma endregion

    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Function that checks if the
 * packet class can successfully get
 * how many parameters valid predetermined
 * packets have.
 * 
 * @return Execution 
 */
Execution TEST_PACKET_GetAmountOfParameters()
{
    TestStart("GetAmountOfParameters");
    Execution execution;
    unsigned char parameterCount = 0;

    // - Packets used for the tests - //
                                        // Start: ID = 0  // Div              // Byte A: 255        // Check: 255
    unsigned short planeA[4]         = {0b0000001000000000, 0b0000000100000000, 0b0000000011111111, 0b0000001111111111};                                            // Needs to return 1 parameter.
                                        // Start: ID = 1  // Div               // Byte A: 255       // Byte B: 255      // Check: 255
    unsigned short planeB[5]         = {0b0000001000000001, 0b0000000100000000, 0b0000000011111111, 0b0000000011111111, 0b0000001111111111};                        // Needs to return 1 parameter
                                        // Start: ID = 2  // Div               // Byte A: 255       // Div              // Byte B: 255      // Check: 255
    unsigned short planeC[6]         = {0b0000001000000010, 0b0000000100000000, 0b0000000011111111, 0b0000000100000000, 0b0000000011111111, 0b0000001111111111};    // Needs to return 2 parameters
    unsigned short planeD[12]         = {0b0000001000000011, 0b0000000000000000, 0b0000000011111111, 0b0000000000000000, 0b0000000011111111, 0b0000001111111111};    // Needs to return 0 parameters

    #pragma region -Regular plane tests-
    execution = Packet.GetAmountOfParameters(planeA, 4, &parameterCount);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("Unexpected execution returned from Packet.GetAmountOfParameters when valid packet is given.");
        Serial.println(execution);
        return Execution::Failed;
    }

    if(parameterCount != 1)
    {
        TestFailed("PlaneA parameter count was not 1.");
        Execution::Failed;
    }

    execution = Packet.GetAmountOfParameters(planeB, 5, &parameterCount);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("Unexpected execution returned from Packet.GetAmountOfParameters when valid packet is given.");
        Serial.println(execution);
        return Execution::Failed;
    }

    if(parameterCount != 1)
    {
        TestFailed("PlaneB parameter count was not 1.");
        Execution::Failed;
    }

    execution = Packet.GetAmountOfParameters(planeC, 6, &parameterCount);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("Unexpected execution returned from Packet.GetAmountOfParameters when valid packet is given.");
        Serial.println(execution);
        return Execution::Failed;
    }

    if(parameterCount != 2)
    {
        TestFailed("PlaneC parameter count was not 2.");
        Execution::Failed;
    }

    #pragma endregion

    #pragma region -Weird packets-
    execution = Packet.GetAmountOfParameters(planeA, 2, &parameterCount);
    TestStepDone();
    if(execution != Execution::Unecessary)
    {
        TestFailed("Did not return Execution::Unecessary when plane only have 2 passengers");
        return Execution::Failed;
    }

    execution = Packet.GetAmountOfParameters(planeA, 3, &parameterCount);
    TestStepDone();
    if(execution != Execution::Failed)
    {
        TestFailed("Did not return Execution::Failed when plane is only 3 passengers");
        return Execution::Failed;
    }

    execution = Packet.GetAmountOfParameters(planeA, 0, &parameterCount);
    TestStepDone();
    if(execution != Execution::Failed)
    {
        TestFailed("Did not return Execution::Failed when plane is only 0 passengers");
        return Execution::Failed;
    }

    execution = Packet.GetAmountOfParameters(planeD, 6, &parameterCount);
    TestStepDone();
    if(execution != Execution::Failed)
    {
        TestFailed("Did not return Execution::Failed when plane has 0 div passengers");
        Serial.println(parameterCount);
        Serial.println(execution);
        return Execution::Failed;
    }

    #pragma endregion

    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Function that verifies that the
 * packet class can successfully build a
 * segment from an array of bytes.
 * Array of bytes are built using the cData
 * class.
 * 
 * @return Execution 
 */
Execution TEST_PACKET_GetParameterSegmentFromBytes()
{
    TestStart("GetParameterSegmentFromBytes");
    Execution execution;
    unsigned char convertedBytes[45];
    unsigned short resultedSegment[45];

    #pragma region -Bool convertion-
    bool boolToSend = true;
    bool boolReceived = false;

    #pragma region --ToByte--
    execution = Data.ToBytes(boolToSend, convertedBytes, 1);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("427: Failed Data.ToBytes");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --GetParameterSegmentFromBytes--
    execution = Packet.GetParameterSegmentFromBytes(convertedBytes, resultedSegment, 1, 2);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("436: Failed to get packet segment from bytes");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --IsFirstPassengerDiv?-
    TestStepDone();
    if(resultedSegment[0] != ChunkType::Div)
    {
        TestFailed("443: First chunk of segment is not a div chunk.");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --ConvertSegmentBack--
    execution = Packet.GetBytesFromParameterSegment(resultedSegment, 2, convertedBytes, 1);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("450: GetBytes failed to return appropriate execution");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --ConvertValueBack--
    execution = Data.ToData(&boolReceived, convertedBytes, 1);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("459: Incorrect execution returned from Data.ToData");
        return Execution::Failed;
    }

    #pragma endregion
    #pragma region --CompareValues--
    TestStepDone();
    if(boolToSend != boolReceived)
    {
        TestFailed("467: converted values did not match.");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion
    #pragma region -Short convertion-
    short shortToSend = 0xAA;
    short shortReceived = 0;

    #pragma region --ToByte--
    execution = Data.ToBytes(shortToSend, convertedBytes, 2);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("486: Failed Data.ToBytes");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --GetParameterSegmentFromBytes--
    execution = Packet.GetParameterSegmentFromBytes(convertedBytes, resultedSegment, 2, 3);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("495: Failed to get packet segment from bytes");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --IsFirstPassengerDiv?-
    TestStepDone();
    if(resultedSegment[0] != ChunkType::Div)
    {
        TestFailed("503: First chunk of segment is not a div chunk.");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --ConvertSegmentBack--
    execution = Packet.GetBytesFromParameterSegment(resultedSegment, 3, convertedBytes, 2);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("512: GetBytes failed to return appropriate execution");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --ConvertValueBack--
    execution = Data.ToData(&shortReceived, convertedBytes, 2);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("521: Incorrect execution returned from Data.ToData");
        return Execution::Failed;
    }

    #pragma endregion
    #pragma region --CompareValues--
    TestStepDone();
    if(shortToSend != shortReceived)
    {
        TestFailed("530: converted values did not match.");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion
    #pragma region -Int convertion-
    int intToSend = -255;
    int intReceived = 0;

    #pragma region --ToByte--
    execution = Data.ToBytes(intToSend, convertedBytes, 4);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("543: Failed Data.ToBytes");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --GetParameterSegmentFromBytes---
    execution = Packet.GetParameterSegmentFromBytes(convertedBytes, resultedSegment, 4, 5);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("552: Failed to get packet segment from bytes");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --IsFirstPassengerDiv?-
    TestStepDone();
    if(resultedSegment[0] != ChunkType::Div)
    {
        TestFailed("560: First chunk of segment is not a div chunk.");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --ConvertSegmentBack--
    execution = Packet.GetBytesFromParameterSegment(resultedSegment, 5, convertedBytes, 4);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("569: GetBytes failed to return appropriate execution");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --ConvertValueBack--
    execution = Data.ToData(&intReceived, convertedBytes, 4);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("578: Incorrect execution returned from Data.ToData");
        return Execution::Failed;
    }

    #pragma endregion
    #pragma region --CompareValues--
    TestStepDone();
    if(intReceived != intToSend)
    {
        TestFailed("587: converted values did not match.");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion
    #pragma region -Float convertion-
    float floatToSend = -20.45f;
    float floatReceived = 0;

    #pragma region --ToByte--
    execution = Data.ToBytes(floatToSend, convertedBytes, 4);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("601: Failed Data.ToBytes");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --GetParameterSegmentFromBytes---
    execution = Packet.GetParameterSegmentFromBytes(convertedBytes, resultedSegment, 4, 5);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("610: Failed to get packet segment from bytes");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --IsFirstPassengerDiv?-
    TestStepDone();
    if(resultedSegment[0] != ChunkType::Div)
    {
        TestFailed("618: First chunk of segment is not a div chunk.");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --ConvertSegmentBack--
    execution = Packet.GetBytesFromParameterSegment(resultedSegment, 5, convertedBytes, 4);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("627: GetBytes failed to return appropriate execution");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --ConvertValueBack--
    execution = Data.ToData(&floatReceived, convertedBytes, 4);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("636: Incorrect execution returned from Data.ToData");
        return Execution::Failed;
    }

    #pragma endregion
    #pragma region --CompareValues--
    TestStepDone();
    if(floatToSend != floatReceived)
    {
        TestFailed("645: converted values did not match.");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion
    #pragma region -Long Long convertion-
    long long longlongToSend = 98675;
    long long longlongReceived = 0;

    #pragma region --ToByte--
    execution = Data.ToBytes(longlongToSend, convertedBytes, 8);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("659: Failed Data.ToBytes");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --GetParameterSegmentFromBytes---
    execution = Packet.GetParameterSegmentFromBytes(convertedBytes, resultedSegment, 8, 9);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("668: Failed to get packet segment from bytes");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --IsFirstPassengerDiv?-
    TestStepDone();
    if(resultedSegment[0] != ChunkType::Div)
    {
        TestFailed("676: First chunk of segment is not a div chunk.");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --ConvertSegmentBack--
    execution = Packet.GetBytesFromParameterSegment(resultedSegment, 9, convertedBytes, 8);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("685: GetBytes failed to return appropriate execution");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --ConvertValueBack--
    execution = Data.ToData(&longlongReceived, convertedBytes, 8);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("694: Incorrect execution returned from Data.ToData");
        return Execution::Failed;
    }

    #pragma endregion
    #pragma region --CompareValues--
    TestStepDone();
    if(longlongToSend != longlongReceived)
    {
        TestFailed("703: converted values did not match.");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion
    #pragma region -String convertion-
    std::string stringToSend = "Frank is very sus because he plays among us.";
    int lengthOfStringToSend = stringToSend.length();
    std::string stringReceived = "";

    #pragma region --ToByte--
    execution = Data.ToBytes(stringToSend, convertedBytes, lengthOfStringToSend);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("718: Failed Data.ToBytes");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --GetParameterSegmentFromBytes---
    execution = Packet.GetParameterSegmentFromBytes(convertedBytes, resultedSegment, lengthOfStringToSend, lengthOfStringToSend+1);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("727: Failed to get packet segment from bytes");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --IsFirstPassengerDiv?-
    TestStepDone();
    if(resultedSegment[0] != ChunkType::Div)
    {
        TestFailed("735: First chunk of segment is not a div chunk.");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --ConvertSegmentBack--
    execution = Packet.GetBytesFromParameterSegment(resultedSegment, lengthOfStringToSend+1, convertedBytes, lengthOfStringToSend);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("744: GetBytes failed to return appropriate execution");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --ConvertValueBack--
    execution = Data.ToData(stringReceived, convertedBytes, lengthOfStringToSend);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("753: Incorrect execution returned from Data.ToData");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region --CompareValues--
    TestStepDone();
    Serial.println(stringToSend.c_str());
    Serial.println(stringReceived.c_str());
    if(stringToSend != stringReceived)
    {
        TestFailed("762: converted values did not match.");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion  
    
    
    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Function that verifies that the
 * packet class can successfully merge 2
 * segments of chunks togheter into one
 * large segment.
 * 
 * @return Execution 
 */
Execution TEST_PACKET_AppendSegments()
{
    TestStart("AppendSegments");
    Execution execution;
    
    unsigned short resultedSegment[10];
    unsigned short segmentA[10];
    unsigned short segmentB[10];

    for (int index = 0; index < 200; index++)
    {
        unsigned char bytesA[10];
        unsigned char bytesB[10];
        int valueToConvert_A = index;
        int valueToConvert_B = -index;
        int convertedValue_A = 0;
        int convertedValue_B = 0;

        #pragma region -ToBytes-
        execution = Data.ToBytes(convertedValue_A, bytesA, 4);
        TestStepDone();
        if(execution != Execution::Passed)
        {
            TestFailed("803: Data.ToBytes");
            return Execution::Failed;
        }

        execution = Data.ToBytes(convertedValue_B, bytesB, 4);
        TestStepDone();
        if(execution != Execution::Passed)
        {
            TestFailed("810: Data.ToBytes");
            return Execution::Failed;
        }
        #pragma endregion
    
        #pragma region -ToSegment-
        execution = Packet.GetParameterSegmentFromBytes(bytesA, segmentA, 4, 5);
        TestStepDone();
        if(execution != Execution::Passed)
        {
            TestFailed("823: Failed to get segment.");
        }

        execution = Packet.GetParameterSegmentFromBytes(bytesB, segmentB, 4, 5);
        TestStepDone();
        if(execution != Execution::Passed)
        {
            TestFailed("830: Failed to get segment.");
        }
        #pragma endregion
    
        #pragma region -Append-
        int expectedSize = 10;
        execution = Packet.AppendSegments(segmentA, 5, segmentB, 5, resultedSegment, &expectedSize);
        TestStepDone();
        if(execution != Execution::Passed)
        {
            TestFailed("839: Incorrect execution returned from AppendSegments");
            return Execution::Failed;
        }
        #pragma endregion
    
        #pragma region -ConvertBackFirstSegment-
        execution = Packet.GetBytesFromParameterSegment(resultedSegment, 5, bytesA, 4);
        TestStepDone();
        if(execution != Execution::Passed)
        {
            TestFailed("849: Incorrect execution returned from GetBytesFromParameterSegment");
            return Execution::Failed;
        }

        int result = 0;
        execution = Data.ToData(&result, bytesA, 4);
        TestStepDone();
        if(execution != Execution::Passed)
        {
            TestFailed("858: Data.ToData failed to convert.");
            return Execution::Failed;
        }
        #pragma endregion
    }

    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Function that verifies that
 * the packet class can successfully
 * build a packet form a bunch of segments
 * 
 * @return Execution 
 */
Execution TEST_PACKET_CreateFromSegments()
{
    TestStart("CreateFromSegments");
    Execution execution;
    // - Segments used for the tests - //
                                     // Start: ID = 0  // Div              // Byte A: 255        // Check: 255
    unsigned short segmentA[4]       = {0b0000000100000000, 0b0000000000000000, 0b0000000000000000, 0b0000000000000000}; // 1 parameter, 3 empty bytes
    unsigned short segmentB[4]       = {0b0000000100000000, 0b0000000000000000, 0b0000000100000000, 0b0000000000000000}; // 2 parameters, 2 empty bytes
    unsigned short segmentC[4]       = {0b0000000100000000, 0b0000000001111111, 0b0000000100000000, 0b0000000001111111}; // 2 parameters, 2 bytes of 127
    unsigned short badSegmentA[4]    = {0b0000000001111111, 0b0000000001111111, 0b0000000001111111, 0b0000000001111111}; // Array containing no div chunks
    unsigned short badSegmentB[4]    = {0b0010000100000000, 0b0000000000000000, 0b0000000011111111, 0b0000001111111111}; // Array containing corrupted chunks
    unsigned short resultedPlane[6];
    unsigned char resultedID = 0;
    unsigned char resultedParamCount = 0;

    #pragma region -segmentA-
    // Create a plane of callsign 20 from segmentA
    execution = Packet.CreateFromSegments(20, segmentA, 4, resultedPlane, 6);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("894: Failed to create packet.");
        return Execution::Failed;
    }

    execution = Packet.GetID(resultedPlane, 6, &resultedID);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("904: Failed to get ID of plane.");
        return Execution::Failed;
    }

    if(resultedID != 20)
    {
        TestFailed("910: GetID's value did not match plane's wanted ID");
        return Execution::Failed;
    }

    execution = Packet.GetAmountOfParameters(resultedPlane, 6, &resultedParamCount);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("919: Failed to get segment count from plane.");
        return Execution::Failed;
    }

    if(resultedParamCount != 1)
    {
        TestFailed("925: Incorrect amount of parameters resulted from plane.");
        return Execution::Failed;
    }

    execution = Packet.VerifyCheckSum(resultedPlane, 6, 20);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("927: Failed to verify checksum.");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region -segmentB-
    // Create a plane of callsign 100 from segmentB
    execution = Packet.CreateFromSegments(100, segmentB, 4, resultedPlane, 6);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("944: Failed to create packet.");
        return Execution::Failed;
    }

    execution = Packet.GetID(resultedPlane, 6, &resultedID);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("904: Failed to get ID of plane.");
        return Execution::Failed;
    }

    if(resultedID != 100)
    {
        TestFailed("958: GetID's value did not match plane's wanted ID");
        return Execution::Failed;
    }

    execution = Packet.GetAmountOfParameters(resultedPlane, 6, &resultedParamCount);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("966: Failed to get segment count from plane.");
        return Execution::Failed;
    }

    if(resultedParamCount != 2)
    {
        TestFailed("972: Incorrect amount of parameters resulted from plane.");
        return Execution::Failed;
    }

    execution = Packet.VerifyCheckSum(resultedPlane, 6, 100);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("980: Failed to verify checksum.");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region -segmentC-
    // Create a plane of callsign 55 from segmentC
    execution = Packet.CreateFromSegments(55, segmentC, 4, resultedPlane, 6);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("991: Failed to create packet.");
        return Execution::Failed;
    }

    execution = Packet.GetID(resultedPlane, 6, &resultedID);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("999: Failed to get ID of plane.");
        return Execution::Failed;
    }

    if(resultedID != 55)
    {
        TestFailed("1005: GetID's value did not match plane's wanted ID");
        return Execution::Failed;
    }

    execution = Packet.GetAmountOfParameters(resultedPlane, 6, &resultedParamCount);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("1013: Failed to get segment count from plane.");
        return Execution::Failed;
    }

    if(resultedParamCount != 2)
    {
        TestFailed("1019: Incorrect amount of parameters resulted from plane.");
        return Execution::Failed;
    }

    execution = Packet.VerifyCheckSum(resultedPlane, 6, 53);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("1027: Failed to verify checksum.");
        return Execution::Failed;
    }
    #pragma endregion
    
    execution = Packet.CreateFromSegments(255, badSegmentA, 4, resultedPlane, 6);
    TestStepDone();
    if(execution == Execution::Passed)
    {
        TestFailed("1036: Execution::Passed returned from plane with no div chunks");
        return Execution::Failed;
    }

    execution = Packet.CreateFromSegments(255, badSegmentB, 4, resultedPlane, 6);
    TestStepDone();
    if(execution == Execution::Passed)
    {
        TestFailed("1044: Execution::Passed returned from plane with corrupted div chunks");
        return Execution::Failed;
    }
    
    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Test function that verifies that the
 * packet class can successfully extract every
 * parameter segments from valid predetermined
 * packets.
 * 
 * @return Execution 
 */
Execution TEST_PACKET_GetParametersFromPacket()
{
    TestStart("GetParametersFromPacket");

    TestPassed();
    return Execution::Passed;
}

Execution TEST_PACKET_EntireProcess()
{
    TestStart("ULTIMATE SUPER ULTRA MEGA TEST");
    Execution execution;
    unsigned short plane[100];
    unsigned short segmentsToSend[100];
    unsigned short segmentToSendA[26];
    unsigned short segmentToSendB[28];
    unsigned char bytesToSendA[25];
    unsigned char bytesToSendB[27];

    unsigned short receivedSegmentA[26];
    unsigned short receivedSegmentB[28];
    unsigned char receivedBytesA[25];
    unsigned char receivedBytesB[27];
    unsigned char functionID = 8;
    unsigned char extractedFunctionID = 0;
    int resultedPlaneSize = 100;
    int extractedParameterCount = 0;

    std::string stringToSendA = "Frank is the imposter! :O";
    std::string stringToSendB = "God damn this computer slow";
    std::string receivedStringA;
    std::string receivedStringB;

    #pragma region --- CONVERT TO BYTES
    execution = Data.ToBytes(stringToSendA, bytesToSendA, 25);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("1093: Failed to convert string A to bytes");
        return Execution::Failed;
    }

    execution = Data.ToBytes(stringToSendB, bytesToSendB, 27);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("1101: Failed to convert string B to bytes");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region --- CONVERT TO SEGMENTS
    execution = Packet.GetParameterSegmentFromBytes(bytesToSendA, segmentToSendA, 25, 27);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("1111: Failed to get segment from bytes A");
        return Execution::Failed;
    }

    execution = Packet.GetParameterSegmentFromBytes(bytesToSendB, segmentToSendB, 27, 28);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("1119: Failed to get segment from bytes B");
        return Execution::Failed;
    }  

    #pragma endregion

    #pragma region --- APPEND SEGMENTS
    execution = Packet.AppendSegments(segmentToSendA, 26, segmentToSendB, 28, segmentsToSend, &resultedPlaneSize);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("1130: Failed to append segment A to B");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region --- CREATE PLANE
    execution = Packet.CreateFromSegments(functionID, segmentsToSend, 54, plane, 100);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("1140: Failed to create packet from segmentA and segmentB");
        return Execution::Failed;
    }
    #pragma endregion
    
    #pragma region --- Verify ID
    execution = Packet.GetID(plane, 100, &extractedFunctionID);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("1166: GetID failed its execution.");
    }
    #pragma endregion
    
    #pragma region --- PACKET VERIFICATIONS

    execution = Packet.FullyAnalyze(plane, &resultedPlaneSize, &extractedParameterCount, &extractedFunctionID);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("1176: FullyAnalyzeFailed");
        return Execution::Failed;
    }
   
    if(extractedFunctionID != functionID)
    {
        TestFailed("1176: ID did not match");
        return Execution::Failed;
    }

    if(extractedParameterCount != 2)
    {
        TestFailed("1182: Packet did not have 2 parameters");
        Serial.println(extractedParameterCount);
        return Execution::Failed;
    }

    if(resultedPlaneSize != 56)
    {
        TestFailed("1188: plane is not the same size (56)");
        Serial.println(extractedParameterCount);
        return Execution::Failed;
    }
   
    #pragma endregion
    
    #pragma region --- EXTRACTING PARAMETERS
    execution = Packet.GetBytes(plane, resultedPlaneSize, 1, receivedBytesA, 25);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        Serial.println(execution);
        TestFailed("1199: GetBytes failed to execute");
        return Execution::Failed;
    }

    execution = Packet.GetBytes(plane, resultedPlaneSize, 2, receivedBytesB, 27);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("1207: GetBytes failed to execute");
        return Execution::Failed;
    }
    #pragma endregion
    
    #pragma region --- CONVERTING PARAMETERS
    execution = Data.ToData(receivedStringA, receivedBytesA, 25);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("1215: Failed to convert bytes A to string");
        return Execution::Passed;
    }

    execution = Data.ToData(receivedStringB, receivedBytesB, 27);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("1223: Failed to convert bytes B to string");
        return Execution::Passed;
    }

    #pragma endregion
    
    #pragma region --- COMPARAISON
    if(receivedStringA != stringToSendA)
    {
        TestFailed("1232: Received string does not equal to sent string.");
        Serial.println(stringToSendA.c_str());
        Serial.println(receivedStringA.c_str());
        return Execution::Failed;
    }

    if(receivedStringB != stringToSendB)
    {
        Serial.println(stringToSendB.c_str());
        Serial.println(receivedStringB.c_str());
        TestFailed("1238: Received string does not equal to sent string.");
        return Execution::Failed;
    }
    #pragma endregion
    
    Serial.println(stringToSendA.c_str());
    Serial.println(receivedStringA.c_str());
    Serial.println(stringToSendB.c_str());
    Serial.println(receivedStringB.c_str());
    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Unit test function which returns
 * Execution::Passed if packet works
 * successfully for each methods it has.
 * 
 * It will return Execution::Failed if any
 * function fails
 * @return Execution 
 */
Execution cPacket_LaunchTests()
{
    StartOfUnitTest("cPacket");

    if(TEST_PACKET_GetID() != Execution::Passed){
        UnitTestFailed();
        return Execution::Failed;
    }

    if(TEST_PACKET_VerifyCheckSum() != Execution::Passed){
        UnitTestFailed();
        return Execution::Failed;
    }

    if(TEST_PACKET_VerifyID() != Execution::Passed){
        UnitTestFailed();
        return Execution::Failed;
    }

    if(TEST_PACKET_GetAmountOfParameters() != Execution::Passed){
        UnitTestFailed();
        return Execution::Failed;
    }

    if(TEST_PACKET_GetParameterSegmentFromBytes() != Execution::Passed){
        UnitTestFailed();
        return Execution::Failed;
    }

    if(TEST_PACKET_AppendSegments() != Execution::Passed){
        UnitTestFailed();
        return Execution::Failed;
    }

    if(TEST_PACKET_CreateFromSegments() != Execution::Passed){
        UnitTestFailed();
        return Execution::Failed;
    }

    if(TEST_PACKET_GetParametersFromPacket() != Execution::Passed){
        UnitTestFailed();
        return Execution::Failed;
    }

    if(TEST_PACKET_EntireProcess() != Execution::Passed){
        UnitTestFailed();
        return Execution::Failed;
    }

    UnitTestPassed();
    return Execution::Passed;
}
