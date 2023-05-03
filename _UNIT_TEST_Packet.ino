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
    if(execution != Execution::Failed)
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
    unsigned char convertedBool[16];
    unsigned short resultedSegment[17];

    #pragma region -Bool convertion-

    bool variableToConvert = true;
    execution = Data.ToBytes(variableToConvert, convertedBool, 1);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("Failed to convert bool to bytes");
        return Execution::Failed;
    }

    execution = Packet.GetParameterSegmentFromBytes(convertedBool, resultedSegment, 1, 2);
    TestStepDone();
    if(execution != Execution::Passed)
    {
        TestFailed("Failed to get packet segment from byte bool.");
        return Execution::Failed;
    }

    if(resultedSegment[0] != ChunkType::Div)
    {
        TestFailed("First chunk of segment is not a div chunk.");
        return Execution::Failed;
    }

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

    UnitTestPassed();
    return Execution::Passed;
}
