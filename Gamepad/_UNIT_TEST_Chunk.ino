/**
 * @file _UNIT_TEST_Chunk.ino
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
 * @brief Function that returns
 * execution::passed if every aspects
 * of ToType from the cChunk class
 * behaves as espected.
 * 
 * @return Execution 
 */
Execution TEST_CHUNK_ToType()
{
    Execution result;

    #pragma region Byte
    TestStart("ToType - Byte");
    for(unsigned short i=0; i<256; ++i)
    {
        TestStepDone();
        unsigned short chunk = i + 0;
        int resultedType = -1;

        result = Chunk.ToType(chunk, &resultedType);

        if(result != Execution::Failed)
        {
            if(resultedType != ChunkType::Byte)
            {
                TestFailed("A value did not identify as a Byte Chunk.");
                return Execution::Failed;
            }
        }
        else
        {
            TestFailed("Unexpected execution returned when testing Byte chunk identifications.");
            return Execution::Failed;
        }
    }
    TestPassed();
    #pragma endregion

    #pragma region Check
    TestStart("ToType - Check");
    for(unsigned short i=0; i<256; ++i)
    {
        TestStepDone();
        unsigned short chunk = i + 768;
        int resultedType = -1;

        result = Chunk.ToType(chunk, &resultedType);

        if(result != Execution::Failed)
        {
            if(resultedType != ChunkType::Check)
            {
                TestFailed("A value did not identify as a Check Chunk.");
                return Execution::Failed;
            }
        }
        else
        {
            TestFailed("Unexpected execution returned when testing Check chunk identifications.");
            return Execution::Failed;  
        }
    }
    TestPassed();
    #pragma endregion

    #pragma region Div
    TestStart("ToType - Div");
    for(unsigned short i=0; i<256; ++i)
    {
        TestStepDone();
        unsigned short chunk = i + 256;
        int resultedType = -1;

        result = Chunk.ToType(chunk, &resultedType);

        if(result != Execution::Failed)
        {
            if(resultedType != ChunkType::Div)
            {
                TestFailed("A value did not identify as a Div Chunk.");
                return Execution::Failed;
            }
        }
        else
        {
            TestFailed("Unexpected execution returned when testing Div chunk identifications.");
            return Execution::Failed;  
        }
    }
    TestPassed();
    #pragma endregion

    #pragma region Start
    TestStart("ToType - Start");
    for(unsigned short i=0; i<256; ++i)
    {
        TestStepDone();
        unsigned short chunk = i + 512;
        int resultedType = -1;

        result = Chunk.ToType(chunk, &resultedType);

        if(result != Execution::Failed)
        {
            if(resultedType != ChunkType::Start)
            {
                TestFailed("A value did not identify as a Start Chunk.");
                Serial.println(i);
                Serial.println(chunk);
                Serial.println(resultedType);
                Serial.println(ChunkType::Start);
                return Execution::Failed;
            }
        }
        else
        {
            TestFailed("Unexpected execution returned when testing Start chunk identifications.");
            return Execution::Failed;  
        }
    }
    TestPassed();
    #pragma endregion

    #pragma region Impossible values
    TestStart("ToType - Executions");
    unsigned short incorrectChunk = 0xFF00;
    int returnedType = 0;
    result = Chunk.ToType(incorrectChunk, &returnedType);
    if(result != Execution::Failed)
    {
        TestFailed("Function did not identify incorrect chunk type.");
        return Execution::Failed;
    }
    TestPassed();
    #pragma endregion

    return Execution::Passed;
}
/**
 * @brief Function that returns
 * execution::passed if every aspects
 * of ToByte from the cChunk class
 * behaves as espected.
 * 
 * @return Execution 
 */
Execution TEST_CHUNK_ToByte()
{
    Execution result;

    #pragma region Byte
    TestStart("ToByte - Byte");
    for(unsigned short i=0; i<256; ++i)
    {
        TestStepDone();
        unsigned short chunk = i + 0;
        unsigned char resultedByte = -1;

        result = Chunk.ToByte(chunk, &resultedByte);

        if(result != Execution::Failed)
        {
            if(resultedByte != ((unsigned char)(chunk & 0x00FF)))
            {
                TestFailed("A Byte chunk did not convert to a byte.");
                return Execution::Failed;
            }
        }
        else
        {
            TestFailed("Unexpected execution returned when converting Byte chunks.");
            return Execution::Failed;
        }
    }
    TestPassed();
    #pragma endregion

    #pragma region Check
    TestStart("ToByte - Check");
    for(unsigned short i=0; i<256; ++i)
    {
        TestStepDone();
        unsigned short chunk = i + 768;
        unsigned char resultedByte = -1;

        result = Chunk.ToByte(chunk, &resultedByte);

        if(result != Execution::Failed)
        {
            if(resultedByte != ((unsigned char)(chunk & 0x00FF)))
            {
                TestFailed("A Check chunk did not convert to a byte.");
                return Execution::Failed;
            }
        }
        else
        {
            TestFailed("Unexpected execution returned when converting Check chunks.");
            return Execution::Failed;
        }
    }
    TestPassed();
    #pragma endregion
    
    #pragma region Div
    TestStart("ToByte - Div");
    for(unsigned short i=0; i<256; ++i)
    {
        TestStepDone();
        unsigned short chunk = i + 256;
        unsigned char resultedByte = -1;

        result = Chunk.ToByte(chunk, &resultedByte);

        if(result != Execution::Failed)
        {
            if(resultedByte != ((unsigned char)(chunk & 0x00FF)))
            {
                TestFailed("A Div chunk did not convert to a byte.");
                return Execution::Failed;
            }
        }
        else
        {
            TestFailed("Unexpected execution returned when converting Div chunks.");
            return Execution::Failed;
        }
    }
    TestPassed();
    #pragma endregion

    #pragma region Start
    TestStart("ToByte - Start");
    for(unsigned short i=0; i<256; ++i)
    {
        TestStepDone();
        unsigned short chunk = i + 512;
        unsigned char resultedByte = -1;

        result = Chunk.ToByte(chunk, &resultedByte);

        if(result != Execution::Failed)
        {
            if(resultedByte != ((unsigned char)(chunk & 0x00FF)))
            {
                TestFailed("A Start chunk did not convert to a byte.");
                return Execution::Failed;
            }
        }
        else
        {
            TestFailed("Unexpected execution returned when converting Start chunks.");
            return Execution::Failed;
        }
    }
    TestPassed();
    #pragma endregion

    #pragma region Impossible values
    TestStart("ToByte - Execution");
    unsigned short incorrectChunk = 1024;
    unsigned char returnedByte = 0;
    result = Chunk.ToByte(incorrectChunk, &returnedByte);
    if(result != Execution::Failed)
    {
        TestFailed("Function did not reject incorrect chunk.");
        return Execution::Failed;
    }
    TestPassed();
    #pragma endregion

    return Execution::Passed;
}
/**
 * @brief Function that returns
 * execution::passed if every aspects
 * of ToChunk from the cChunk class
 * behaves as espected.
 * 
 * @return Execution 
 */
Execution TEST_CHUNK_ToChunk()
{
    Execution result;

    #pragma region Byte
    TestStart("ToChunk - Byte");
    for(unsigned char i=1; i!=0; ++i)
    {
        TestStepDone();
        unsigned short resultedChunk = -1;
        int type = ChunkType::Byte;
        int convertedType;

        result = Chunk.ToChunk(i, &resultedChunk, type);

        if(result != Execution::Failed)
        {
            if(i != ((unsigned char)(resultedChunk & 0x00FF)))
            {
                TestFailed("A byte did not convert to a Byte chunk.");
                return Execution::Failed;
            }

            result = Chunk.ToType(resultedChunk, &convertedType);
            TestStepDone();
            if(result != Execution::Passed)
            {
                TestFailed("Unepexted execution resulted from Chunk.ToType while attempting to confirm Byte chunk type.");
                return Execution::Failed;
            }
            else
            {
                if(convertedType != type)
                {
                    TestFailed("ToType did not return Byte chunk type");
                    return Execution::Failed;
                }
            }
        }
        else
        {
            TestFailed("Unexpected execution returned when converting bytes to Byte chunks.");
            return Execution::Failed;
        }
    }
    TestPassed();
    #pragma endregion

    #pragma region Check
    TestStart("ToChunk - Check");
    for(unsigned char i=1; i!=0; ++i)
    {
        TestStepDone();
        unsigned short resultedChunk = -1;
        int type = ChunkType::Check;
        int convertedType;

        result = Chunk.ToChunk(i, &resultedChunk, type);

        if(result != Execution::Failed)
        {
            if(i != ((unsigned char)(resultedChunk & 0x00FF)))
            {
                TestFailed("A byte did not convert to a Check chunk.");
                return Execution::Failed;
            }

            result = Chunk.ToType(resultedChunk, &convertedType);
            TestStepDone();
            if(result != Execution::Passed)
            {
                TestFailed("Unepexted execution resulted from Chunk.ToType while attempting to confirm Check chunk type.");
                return Execution::Failed;
            }
            else
            {
                if(convertedType != type)
                {
                    TestFailed("ToType did not return Check chunk type");
                    return Execution::Failed;
                }
            }
        }
        else
        {
            TestFailed("Unexpected execution returned when converting bytes to Check chunks.");
            return Execution::Failed;
        }
    }
    TestPassed();
    #pragma endregion
    
    #pragma region Div
    TestStart("ToChunk - Div");
    for(unsigned char i=1; i!=0; ++i)
    {
        TestStepDone();
        unsigned short resultedChunk = -1;
        int type = ChunkType::Div;
        int convertedType;

        result = Chunk.ToChunk(i, &resultedChunk, type);

        if(result != Execution::Failed)
        {
            if(i != ((unsigned char)(resultedChunk & 0x00FF)))
            {
                TestFailed("A byte did not convert to a Div chunk.");
                return Execution::Failed;
            }

            result = Chunk.ToType(resultedChunk, &convertedType);
            TestStepDone();
            if(result != Execution::Passed)
            {
                TestFailed("Unepexted execution resulted from Chunk.ToType while attempting to confirm Div chunk type.");
                return Execution::Failed;
            }
            else
            {
                if(convertedType != type)
                {
                    TestFailed("ToType did not return Div chunk type");
                    return Execution::Failed;
                }
            }
        }
        else
        {
            TestFailed("Unexpected execution returned when converting bytes to Byte chunks.");
            return Execution::Failed;
        }
    }
    TestPassed();
    #pragma endregion
    
    #pragma region Start
    TestStart("ToChunk - Start");
    for(unsigned char i=1; i!=0; ++i)
    {
        TestStepDone();
        unsigned short resultedChunk = -1;
        int type = ChunkType::Byte;
        int convertedType;

        result = Chunk.ToChunk(i, &resultedChunk, type);

        if(result != Execution::Failed)
        {
            if(i != ((unsigned char)(resultedChunk & 0x00FF)))
            {
                TestFailed("A byte did not convert to a Start chunk.");
                return Execution::Failed;
            }

            result = Chunk.ToType(resultedChunk, &convertedType);
            TestStepDone();
            if(result != Execution::Passed)
            {
                TestFailed("Unepexted execution resulted from Chunk.ToType while attempting to confirm Start chunk type.");
                return Execution::Failed;
            }
            else
            {
                if(convertedType != type)
                {
                    TestFailed("ToType did not return Start chunk type");
                    return Execution::Failed;
                }
            }
        }
        else
        {
            TestFailed("Unexpected execution returned when converting bytes to Byte chunks.");
            return Execution::Failed;
        }
    }
    TestPassed();
    #pragma endregion

    #pragma region Impossible values
    TestStart("ToChunk - Execution");
    unsigned short resultedChunk = 0;
    unsigned char byteToConvert = 1;

    result = Chunk.ToChunk(byteToConvert, &resultedChunk, 1);
    TestStepDone();
    if(result != Execution::Failed)
    {
        TestFailed("Unexpected execution value while attempting to convert to inexisting chunk type (1)");
        return Execution::Failed;
    }
    TestPassed();
    #pragma endregion

    return Execution::Passed;
}

/**
 * @brief Unit test function which returns
 * Execution::Passed if chunk works
 * successfully for each methods it has.
 * 
 * It will return Execution::Failed if any
 * function fails to convert data and read
 * back the same exact values.
 * @return Execution 
 */
Execution cChunk_LaunchTests()
{
    StartOfUnitTest("class cChunk");
    Execution result;

    result = TEST_CHUNK_ToType();
    if(result == Execution::Failed)
    {
        UnitTestFailed();
        return Execution::Failed;
    }
    
    result = TEST_CHUNK_ToByte();
    if(result == Execution::Failed)
    {
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_CHUNK_ToChunk();
    if(result == Execution::Failed)
    {
        UnitTestFailed();
        return Execution::Failed;
    }

    UnitTestPassed();
    return Execution::Passed;
}