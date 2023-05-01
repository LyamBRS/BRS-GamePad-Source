/**
 * @file Data_UNIT_TEST.h
 * @author Lyam (lyam.brs@gmail.com)
 * @brief This file contains the declaration
 * of the method that allows a quick and
 * simple unit test to the cData class
 * defined in Data.h
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

#pragma region Convertions
/// @brief Tests of boolean convertions
/// @return 
Execution TEST_cData_bools()
{
    TestStart("bools conversion");
    unsigned char Array[16];
    int sizeOfArray = 1;
    int typeResult = -1;
    bool toConvert = true;
    bool converted = false;
    int wantedType = DataType::Bool;

    #pragma region ToBytes ToData
    toConvert = true;
    Data.ToBytes(toConvert, Array, sizeOfArray);
    Data.ToData(&converted, Array, sizeOfArray);
    TestStepDone();

    if(toConvert != converted)
    {
        TestFailed("Value did not match after conversion");
        return Execution::Failed;
    }

    toConvert = false;
    Data.ToBytes(toConvert, Array, sizeOfArray);
    Data.ToData(&converted, Array, sizeOfArray);
    TestStepDone();

    if(toConvert != converted)
    {
        TestFailed("Value did not match after conversion");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region ToType
    Execution result = Data.ToType(toConvert, &typeResult);
    TestStepDone();
    if(typeResult != wantedType)
    {
        TestFailed("ToType did not return correct type.");
        return Execution::Failed;
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of unsigned char convertions
/// @return 
Execution TEST_cData_UC()
{
    TestStart("unsigned char convertion");
    unsigned char Array[16];
    int sizeOfArray = 1;
    int typeResult = -1;
    int wantedType = DataType::UnsignedChar;
    unsigned char toConvert = true;
    unsigned char converted = false;

    #pragma region ToBytes ToData
    for(toConvert = 1; toConvert != 0; toConvert++)
    {
        Data.ToBytes(toConvert, Array, sizeOfArray);
        Data.ToData(&converted, Array, sizeOfArray);
        TestStepDone();

        if(toConvert != converted)
        {
            TestFailed("Value did not match after conversion");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region ToType
    Execution result = Data.ToType(toConvert, &typeResult);
    TestStepDone();
    if(typeResult != wantedType)
    {
        TestFailed("ToType did not return correct type.");
        return Execution::Failed;
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of char convertions
/// @return 
Execution TEST_cData_char()
{
    TestStart("char convertion");
    unsigned char Array[16];
    int sizeOfArray = 1;
    int typeResult = -1;
    int wantedType = DataType::Char;
    char toConvert = true;
    char converted = false;

    #pragma region ToBytes ToData
    for(toConvert = 1; toConvert != 0; toConvert++)
    {
        Data.ToBytes(toConvert, Array, sizeOfArray);
        Data.ToData(&converted, Array, sizeOfArray);
        TestStepDone();
    
        if(toConvert != converted)
        {
            TestFailed("Value did not match after conversion");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region ToType
    Execution result = Data.ToType(toConvert, &typeResult);
    TestStepDone();
    if(typeResult != wantedType)
    {
        TestFailed("ToType did not return correct type.");
        return Execution::Failed;
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of unsigned short convertions
/// @return 
Execution TEST_cData_US()
{
    TestStart("unsigned short convertion");
    unsigned char Array[16];
    int sizeOfArray = 2;
    int typeResult = -1;
    int wantedType = DataType::UnsignedShort;
    unsigned short toConvert = true;
    unsigned short converted = false;

    #pragma region ToBytes ToData
    for(toConvert = 1; toConvert != 0; toConvert++)
    {
        Data.ToBytes(toConvert, Array, sizeOfArray);
        Data.ToData(&converted, Array, sizeOfArray);
        TestStepDone();
    
        if(toConvert != converted)
        {
            TestFailed("Value did not match after conversion");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region ToType
    Execution result = Data.ToType(toConvert, &typeResult);
    TestStepDone();
    if(typeResult != wantedType)
    {
        TestFailed("ToType did not return correct type.");
        return Execution::Failed;
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of short convertions
/// @return 
Execution TEST_cData_short()
{
    TestStart("short convertion");
    unsigned char Array[16];
    int sizeOfArray = 2;
    int typeResult = -1;
    int wantedType = DataType::Short;
    short toConvert = true;
    short converted = false;

    #pragma region ToBytes ToData
    for(toConvert = 1; toConvert != 0; toConvert++)
    {
        Data.ToBytes(toConvert, Array, sizeOfArray);
        Data.ToData(&converted, Array, sizeOfArray);
        TestStepDone();
    
        if(toConvert != converted)
        {
            TestFailed("Value did not match after conversion");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region ToType
    Execution result = Data.ToType(toConvert, &typeResult);
    TestStepDone();
    if(typeResult != wantedType)
    {
        TestFailed("ToType did not return correct type.");
        return Execution::Failed;
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of int convertions
/// @return 
Execution TEST_cData_int()
{
    TestStart("int convertion");
    unsigned char Array[16];
    int sizeOfArray = 4;
    int typeResult = -1;
    int wantedType = DataType::Int;
    int toConvert = 1;
    int converted = false;

    #pragma region ToBytes ToData
    for(toConvert = 1; toConvert != 0; toConvert = -toConvert*2)
    {
        Data.ToBytes(toConvert, Array, sizeOfArray);
        Data.ToData(&converted, Array, sizeOfArray);
        TestStepDone();
    
        if(toConvert != converted)
        {
            TestFailed("Value did not match after conversion");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region ToType
    Execution result = Data.ToType(toConvert, &typeResult);
    TestStepDone();
    if(typeResult != wantedType)
    {
        TestFailed("ToType did not return correct type.");
        return Execution::Failed;
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}
/// @brief Tests of unsigned int convertions
/// @return 
Execution TEST_cData_UI()
{
    TestStart("unsigned int convertion");
    unsigned char Array[16];
    int sizeOfArray = 4;
    int typeResult = -1;
    int wantedType = DataType::UnsignedInt;
    unsigned int toConvert = 1;
    unsigned int converted = false;

    #pragma region ToBytes ToData
    for(toConvert = 1; toConvert != 0; toConvert = -toConvert*2)
    {
        Data.ToBytes(toConvert, Array, sizeOfArray);
        Data.ToData(&converted, Array, sizeOfArray);
        TestStepDone();
    
        if(toConvert != converted)
        {
            TestFailed("Value did not match after conversion");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region ToType
    Execution result = Data.ToType(toConvert, &typeResult);
    TestStepDone();
    if(typeResult != wantedType)
    {
        TestFailed("ToType did not return correct type.");
        return Execution::Failed;
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of long convertions
/// @return 
Execution TEST_cData_long()
{
    TestStart("long convertion");
    unsigned char Array[16];
    int sizeOfArray = 8;
    int typeResult = -1;
    int wantedType = DataType::Long;
    long toConvert = 1;
    long converted = false;

    #pragma region ToBytes ToData
    for(toConvert = 1; toConvert != 0; toConvert = -toConvert*2)
    {
        Data.ToBytes(toConvert, Array, sizeOfArray);
        Data.ToData(&converted, Array, sizeOfArray);
        TestStepDone();
    
        if(toConvert != converted)
        {
            TestFailed("Value did not match after conversion");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region ToType
    Execution result = Data.ToType(toConvert, &typeResult);
    TestStepDone();
    if(typeResult != wantedType)
    {
        TestFailed("ToType did not return correct type.");
        return Execution::Failed;
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of unsigned long convertions
/// @return 
Execution TEST_cData_UL()
{
    TestStart("unsigned long convertion");
    unsigned char Array[16];
    int sizeOfArray = 8;
    int typeResult = -1;
    int wantedType = DataType::UnsignedLong;
    unsigned long toConvert = 1;
    unsigned long converted = false;

    #pragma region ToBytes ToData
    for(toConvert = 1; toConvert != 0; toConvert = -toConvert*2)
    {
        Data.ToBytes(toConvert, Array, sizeOfArray);
        Data.ToData(&converted, Array, sizeOfArray);
        TestStepDone();
    
        if(toConvert != converted)
        {
            TestFailed("Value did not match after conversion");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region ToType
    Execution result = Data.ToType(toConvert, &typeResult);
    TestStepDone();
    if(typeResult != wantedType)
    {
        TestFailed("ToType did not return correct type.");
        return Execution::Failed;
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of long long convertions
/// @return 
Execution TEST_cData_longlong()
{
    TestStart("long long convertion");
    unsigned char Array[16];
    int sizeOfArray = 8;
    int typeResult = -1;
    int wantedType = DataType::LongLong;
    long long toConvert = 1;
    long long converted = false;

    #pragma region ToBytes ToData
    for(toConvert = 1; toConvert != 0; toConvert = -toConvert*2)
    {
        Data.ToBytes(toConvert, Array, sizeOfArray);
        Data.ToData(&converted, Array, sizeOfArray);
        TestStepDone();
    
        if(toConvert != converted)
        {
            TestFailed("Value did not match after conversion");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region ToType
    Execution result = Data.ToType(toConvert, &typeResult);
    TestStepDone();
    if(typeResult != wantedType)
    {
        TestFailed("ToType did not return correct type.");
        return Execution::Failed;
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of unsigned long long convertions
/// @return 
Execution TEST_cData_ULL()
{
    TestStart("unsigned long long convertion");
    unsigned char Array[16];
    int sizeOfArray = 8;
    int typeResult = -1;
    int wantedType = DataType::UnsignedLongLong;
    unsigned long long toConvert = 1;
    unsigned long long converted = false;

    #pragma region ToBytes ToData
    for(toConvert = 1; toConvert != 0; toConvert = -toConvert*2)
    {
        Data.ToBytes(toConvert, Array, sizeOfArray);
        Data.ToData(&converted, Array, sizeOfArray);
        TestStepDone();
    
        if(toConvert != converted)
        {
            TestFailed("Value did not match after conversion");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region ToType
    Execution result = Data.ToType(toConvert, &typeResult);
    TestStepDone();
    if(typeResult != wantedType)
    {
        TestFailed("ToType did not return correct type.");
        return Execution::Failed;
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of float convertions
/// @return 
Execution TEST_cData_float()
{
    TestStart("float convertion");
    unsigned char Array[16];
    int sizeOfArray = 4;
    int typeResult = -1;
    int wantedType = DataType::Float;
    float toConvert = 1;
    float oldConvert = 0;
    float converted = false;
    unsigned char testCount = 0;

    #pragma region ToBytes ToData
    for(toConvert = 1; toConvert != oldConvert; toConvert = toConvert*2)
    {
        testCount++;
        if(testCount > 200)
        {
          testCount = 0;
          break;
        }
        oldConvert = toConvert;
        Data.ToBytes(toConvert, Array, sizeOfArray);
        Data.ToData(&converted, Array, sizeOfArray);
        TestStepDone();
    
        if(toConvert != converted)
        {
            TestFailed("Value did not match after conversion");
            return Execution::Failed;
        }
    }

    for(toConvert = 1; toConvert != oldConvert; toConvert = toConvert*-2)
    {
        testCount++;
        if(testCount > 200)
        {
          testCount = 0;
          break;
        }
        oldConvert = toConvert;
        Data.ToBytes(toConvert, Array, sizeOfArray);
        Data.ToData(&converted, Array, sizeOfArray);
        TestStepDone();
    
        if(toConvert != converted)
        {
            TestFailed("Value did not match after conversion");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region ToType
    Execution result = Data.ToType(toConvert, &typeResult);
    TestStepDone();
    if(typeResult != wantedType)
    {
        TestFailed("ToType did not return correct type.");
        return Execution::Failed;
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of double convertions
/// @return 
Execution TEST_cData_double()
{
    TestStart("float convertion");
    unsigned char Array[16];
    int sizeOfArray = 8;
    int typeResult = -1;
    int wantedType = DataType::Double;
    double toConvert = 1;
    double oldConvert = 0;
    double converted = false;
    unsigned char testCount = 0;

    #pragma region ToBytes ToData
    for(toConvert = 1; toConvert != oldConvert; toConvert = toConvert*2)
    {
        testCount++;
        if(testCount > 200)
        {
          testCount = 0;
          break;
        }

        oldConvert = toConvert;
        Data.ToBytes(toConvert, Array, sizeOfArray);
        Data.ToData(&converted, Array, sizeOfArray);
        TestStepDone();
    
        if(toConvert != converted)
        {
            TestFailed("Value did not match after conversion");
            return Execution::Failed;
        }
    }

    for(toConvert = 1; toConvert != oldConvert; toConvert = toConvert*-2)
    {
        oldConvert = toConvert;
        Data.ToBytes(toConvert, Array, sizeOfArray);
        Data.ToData(&converted, Array, sizeOfArray);
        TestStepDone();
    
        testCount++;
        if(testCount > 200)
        {
          testCount = 0;
          break;
        }

        if(toConvert != converted)
        {
            TestFailed("Value did not match after conversion");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region ToType
    Execution result = Data.ToType(toConvert, &typeResult);
    TestStepDone();
    if(typeResult != wantedType)
    {
        TestFailed("ToType did not return correct type.");
        return Execution::Failed;
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of string convertions
/// @return 
Execution TEST_cData_string()
{
    TestStart("string convertion");
    Execution result;
    unsigned char Array[71];
    int sizeOfArray = 71;
    int typeResult = -1;
    int wantedType = DataType::String;
    std::string toConvert = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-=.^<>*()";
    std::string converted;

    #pragma region ToBytes ToData
    result = Data.ToBytes(toConvert, Array, sizeOfArray);
    TestStepDone();
    if(result != Execution::Passed)
    {
      TestFailed("ToBytes returned unexpected execution results.");
    }
    result = Data.ToData(converted, Array, sizeOfArray);
    TestStepDone();
    if(result != Execution::Passed)
    {
      TestFailed("ToBytes returned unexpected execution results.");
    }
    
    if(toConvert != converted)
    {
        TestFailed("Value did not match after conversion");
        Serial.println("Original:");
        Serial.println(toConvert.c_str());
        Serial.println("Converted:");
        Serial.println(converted.c_str());
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region ToType
    result = Data.ToType(toConvert, &typeResult);
    TestStepDone();
    if(typeResult != wantedType)
    {
        TestFailed("ToType did not return correct type.");
        return Execution::Failed;
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}
#pragma endregion

#pragma region Executions
/// @brief Tests of boolean executions results
/// @return 
Execution TEST_cData_boolsExecutions()
{
    TestStart("bools execution");
    Execution result;
    unsigned char Array[16];
    int resultedType = -1;
    int sizeOfArray = 1;
    bool toConvert = true;
    bool converted = false;

    #pragma region ToType
    result = Data.ToType(toConvert, &resultedType);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned on ToType");
    }
    #pragma endregion

    #pragma region ToByte
    for(int fakeArraySize=0; fakeArraySize<=16; fakeArraySize++)
    {
        Execution resultToByte = Data.ToBytes(toConvert, Array, fakeArraySize);
        Execution resultToData = Data.ToData(&converted, Array, fakeArraySize);
        TestStepDone();

        if(fakeArraySize < sizeOfArray)
        {
            if(resultToByte != Execution::Failed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Failed)
            {
                TestFailed("ToData returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }     
        }
        else
        {
            if(resultToByte != Execution::Passed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Passed)
            {
                TestFailed("ToData returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }   
        }
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of unsigned char executions results
/// @return 
Execution TEST_cData_UCExecutions()
{
    TestStart("unsigned char execution");
    Execution result;
    unsigned char Array[16];
    int resultedType = -1;
    int sizeOfArray = 1;
    unsigned char toConvert = true;
    unsigned char converted = false;

    #pragma region ToType
    result = Data.ToType(toConvert, &resultedType);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned on ToType");
    }
    #pragma endregion

    #pragma region ToByte
    for(int fakeArraySize=0; fakeArraySize<=16; fakeArraySize++)
    {
        Execution resultToByte = Data.ToBytes(toConvert, Array, fakeArraySize);
        Execution resultToData = Data.ToData(&converted, Array, fakeArraySize);
        TestStepDone();

        if(fakeArraySize < sizeOfArray)
        {
            if(resultToByte != Execution::Failed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Failed)
            {
                TestFailed("ToData returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }     
        }
        else
        {
            if(resultToByte != Execution::Passed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Passed)
            {
                TestFailed("ToData returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }   
        }
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of char executions results
/// @return 
Execution TEST_cData_charExecutions()
{
    TestStart("char execution");
    Execution result;
    unsigned char Array[16];
    int resultedType = -1;
    int sizeOfArray = 1;
    char toConvert = true;
    char converted = false;

    #pragma region ToType
    result = Data.ToType(toConvert, &resultedType);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned on ToType");
    }
    #pragma endregion

    #pragma region ToByte
    for(int fakeArraySize=0; fakeArraySize<=16; fakeArraySize++)
    {
        Execution resultToByte = Data.ToBytes(toConvert, Array, fakeArraySize);
        Execution resultToData = Data.ToData(&converted, Array, fakeArraySize);
        TestStepDone();

        if(fakeArraySize < sizeOfArray)
        {
            if(resultToByte != Execution::Failed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Failed)
            {
                TestFailed("ToData returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }     
        }
        else
        {
            if(resultToByte != Execution::Passed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Passed)
            {
                TestFailed("ToData returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }   
        }
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of unsigned short executions results
/// @return 
Execution TEST_cData_USExecutions()
{
    TestStart("unsigned short execution");
    Execution result;
    unsigned char Array[16];
    int resultedType = -1;
    int sizeOfArray = 2;
    unsigned short toConvert = true;
    unsigned short converted = false;

    #pragma region ToType
    result = Data.ToType(toConvert, &resultedType);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned on ToType");
    }
    #pragma endregion

    #pragma region ToByte
    for(int fakeArraySize=0; fakeArraySize<=16; fakeArraySize++)
    {
        Execution resultToByte = Data.ToBytes(toConvert, Array, fakeArraySize);
        Execution resultToData = Data.ToData(&converted, Array, fakeArraySize);
        TestStepDone();

        if(fakeArraySize < sizeOfArray)
        {
            if(resultToByte != Execution::Failed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Failed)
            {
                TestFailed("ToData returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }     
        }
        else
        {
            if(resultToByte != Execution::Passed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Passed)
            {
                TestFailed("ToData returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }   
        }
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of short executions results
/// @return 
Execution TEST_cData_shortExecutions()
{
    TestStart("short execution");
    Execution result;
    unsigned char Array[16];
    int resultedType = -1;
    int sizeOfArray = 2;
    short toConvert = true;
    short converted = false;

    #pragma region ToType
    result = Data.ToType(toConvert, &resultedType);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned on ToType");
    }
    #pragma endregion

    #pragma region ToByte
    for(int fakeArraySize=0; fakeArraySize<=16; fakeArraySize++)
    {
        Execution resultToByte = Data.ToBytes(toConvert, Array, fakeArraySize);
        Execution resultToData = Data.ToData(&converted, Array, fakeArraySize);
        TestStepDone();

        if(fakeArraySize < sizeOfArray)
        {
            if(resultToByte != Execution::Failed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Failed)
            {
                TestFailed("ToData returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }     
        }
        else
        {
            if(resultToByte != Execution::Passed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Passed)
            {
                TestFailed("ToData returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }   
        }
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of int executions results
/// @return 
Execution TEST_cData_intExecutions()
{
    {
    TestStart("int execution");
    Execution result;
    unsigned char Array[16];
    int resultedType = -1;
    int sizeOfArray = 4;
    int toConvert = true;
    int converted = false;

    #pragma region ToType
    result = Data.ToType(toConvert, &resultedType);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned on ToType");
    }
    #pragma endregion

    #pragma region ToByte
    for(int fakeArraySize=0; fakeArraySize<=16; fakeArraySize++)
    {
        Execution resultToByte = Data.ToBytes(toConvert, Array, fakeArraySize);
        Execution resultToData = Data.ToData(&converted, Array, fakeArraySize);
        TestStepDone();

        if(fakeArraySize < sizeOfArray)
        {
            if(resultToByte != Execution::Failed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Failed)
            {
                TestFailed("ToData returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }     
        }
        else
        {
            if(resultToByte != Execution::Passed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Passed)
            {
                TestFailed("ToData returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }   
        }
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}
}
/// @brief Tests of unsigned int executions results
/// @return 
Execution TEST_cData_UIExecutions()
{
    TestStart("unsigned short execution");
    Execution result;
    unsigned char Array[16];
    int resultedType = -1;
    int sizeOfArray = 4;
    unsigned int toConvert = true;
    unsigned int converted = false;

    #pragma region ToType
    result = Data.ToType(toConvert, &resultedType);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned on ToType");
    }
    #pragma endregion

    #pragma region ToByte
    for(int fakeArraySize=0; fakeArraySize<=16; fakeArraySize++)
    {
        Execution resultToByte = Data.ToBytes(toConvert, Array, fakeArraySize);
        Execution resultToData = Data.ToData(&converted, Array, fakeArraySize);
        TestStepDone();

        if(fakeArraySize < sizeOfArray)
        {
            if(resultToByte != Execution::Failed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Failed)
            {
                TestFailed("ToData returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }     
        }
        else
        {
            if(resultToByte != Execution::Passed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Passed)
            {
                TestFailed("ToData returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }   
        }
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of long executions results
/// @return 
Execution TEST_cData_longExecutions()
{
    TestStart("long execution");
    Execution result;
    unsigned char Array[16];
    int resultedType = -1;
    int sizeOfArray = 8;
    long toConvert = true;
    long converted = false;

    #pragma region ToType
    result = Data.ToType(toConvert, &resultedType);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned on ToType");
    }
    #pragma endregion

    #pragma region ToByte
    for(int fakeArraySize=0; fakeArraySize<=16; fakeArraySize++)
    {
        Execution resultToByte = Data.ToBytes(toConvert, Array, fakeArraySize);
        Execution resultToData = Data.ToData(&converted, Array, fakeArraySize);
        TestStepDone();

        if(fakeArraySize < sizeOfArray)
        {
            if(resultToByte != Execution::Failed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Failed)
            {
                TestFailed("ToData returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }     
        }
        else
        {
            if(resultToByte != Execution::Passed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Passed)
            {
                TestFailed("ToData returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }   
        }
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of unsigned long executions results
/// @return 
Execution TEST_cData_ULExecutions()
{
    TestStart("unsigned long execution");
    Execution result;
    unsigned char Array[16];
    int resultedType = -1;
    int sizeOfArray = 8;
    unsigned long toConvert = true;
    unsigned long converted = false;

    #pragma region ToType
    result = Data.ToType(toConvert, &resultedType);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned on ToType");
    }
    #pragma endregion

    #pragma region ToByte
    for(int fakeArraySize=0; fakeArraySize<=16; fakeArraySize++)
    {
        Execution resultToByte = Data.ToBytes(toConvert, Array, fakeArraySize);
        Execution resultToData = Data.ToData(&converted, Array, fakeArraySize);
        TestStepDone();

        if(fakeArraySize < sizeOfArray)
        {
            if(resultToByte != Execution::Failed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Failed)
            {
                TestFailed("ToData returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }     
        }
        else
        {
            if(resultToByte != Execution::Passed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Passed)
            {
                TestFailed("ToData returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }   
        }
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of long long executions results
/// @return 
Execution TEST_cData_longlongExecutions()
{
    TestStart("long long execution");
    Execution result;
    unsigned char Array[16];
    int resultedType = -1;
    int sizeOfArray = 8;
    long long toConvert = true;
    long long converted = false;

    #pragma region ToType
    result = Data.ToType(toConvert, &resultedType);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned on ToType");
    }
    #pragma endregion

    #pragma region ToByte
    for(int fakeArraySize=0; fakeArraySize<=16; fakeArraySize++)
    {
        Execution resultToByte = Data.ToBytes(toConvert, Array, fakeArraySize);
        Execution resultToData = Data.ToData(&converted, Array, fakeArraySize);
        TestStepDone();

        if(fakeArraySize < sizeOfArray)
        {
            if(resultToByte != Execution::Failed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Failed)
            {
                TestFailed("ToData returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }     
        }
        else
        {
            if(resultToByte != Execution::Passed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Passed)
            {
                TestFailed("ToData returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }   
        }
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of unsigned long long executions results
/// @return 
Execution TEST_cData_ULLExecutions()
{
    TestStart("unsigned long long execution");
    Execution result;
    unsigned char Array[16];
    int resultedType = -1;
    int sizeOfArray = 8;
    unsigned long long toConvert = true;
    unsigned long long converted = false;

    #pragma region ToType
    result = Data.ToType(toConvert, &resultedType);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned on ToType");
    }
    #pragma endregion

    #pragma region ToByte
    for(int fakeArraySize=0; fakeArraySize<=16; fakeArraySize++)
    {
        Execution resultToByte = Data.ToBytes(toConvert, Array, fakeArraySize);
        Execution resultToData = Data.ToData(&converted, Array, fakeArraySize);
        TestStepDone();

        if(fakeArraySize < sizeOfArray)
        {
            if(resultToByte != Execution::Failed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Failed)
            {
                TestFailed("ToData returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }     
        }
        else
        {
            if(resultToByte != Execution::Passed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Passed)
            {
                TestFailed("ToData returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }   
        }
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of float executions results
/// @return 
Execution TEST_cData_floatExecutions()
{
    TestStart("float execution");
    Execution result;
    unsigned char Array[16];
    int resultedType = -1;
    int sizeOfArray = 4;
    float toConvert = true;
    float converted = false;

    #pragma region ToType
    result = Data.ToType(toConvert, &resultedType);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned on ToType");
    }
    #pragma endregion

    #pragma region ToByte
    for(int fakeArraySize=0; fakeArraySize<=16; fakeArraySize++)
    {
        Execution resultToByte = Data.ToBytes(toConvert, Array, fakeArraySize);
        Execution resultToData = Data.ToData(&converted, Array, fakeArraySize);
        TestStepDone();

        if(fakeArraySize < sizeOfArray)
        {
            if(resultToByte != Execution::Failed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Failed)
            {
                TestFailed("ToData returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }     
        }
        else
        {
            if(resultToByte != Execution::Passed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Passed)
            {
                TestFailed("ToData returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }   
        }
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of double executions results
/// @return 
Execution TEST_cData_doubleExecutions()
{
    TestStart("double execution");
    Execution result;
    unsigned char Array[16];
    int resultedType = -1;
    int sizeOfArray = 8;
    double toConvert = true;
    double converted = false;

    #pragma region ToType
    result = Data.ToType(toConvert, &resultedType);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned on ToType");
    }
    #pragma endregion

    #pragma region ToByte
    for(int fakeArraySize=0; fakeArraySize<=16; fakeArraySize++)
    {
        Execution resultToByte = Data.ToBytes(toConvert, Array, fakeArraySize);
        Execution resultToData = Data.ToData(&converted, Array, fakeArraySize);
        TestStepDone();

        if(fakeArraySize < sizeOfArray)
        {
            if(resultToByte != Execution::Failed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Failed)
            {
                TestFailed("ToData returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }     
        }
        else
        {
            if(resultToByte != Execution::Passed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Passed)
            {
                TestFailed("ToData returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }   
        }
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/// @brief Tests of string executions results
/// @return 
Execution TEST_cData_stringExecutions()
{
    TestStart("string execution");
    Execution result;
    unsigned char Array[16];
    int resultedType = -1;
    int sizeOfArray = 12;
    std::string toConvert = "SUS AMONG US";
    std::string converted;

    #pragma region ToType
    result = Data.ToType(toConvert, &resultedType);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned on ToType");
    }
    #pragma endregion

    #pragma region ToByte
    for(int fakeArraySize=0; fakeArraySize<=16; fakeArraySize++)
    {
        Execution resultToByte = Data.ToBytes(toConvert, Array, fakeArraySize);
        Execution resultToData = Data.ToData(converted, Array, fakeArraySize);
        TestStepDone();

        if(fakeArraySize < sizeOfArray)
        {
            if(resultToByte != Execution::Failed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is smaller than minimum.");
                return Execution::Failed;
            }

            // if(resultToData != Execution::Failed)
            // {
                // TestFailed("ToData returned incorrect execution when specified array is smaller than minimum.");
                // return Execution::Passed;
            // }     
        }
        else
        {
            if(resultToByte != Execution::Passed)
            {
                TestFailed("ToByte returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }

            if(resultToData != Execution::Passed)
            {
                TestFailed("ToData returned incorrect execution when specified array is correct.");
                return Execution::Failed;
            }   
        }
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}
#pragma endregion
/**
 * @brief Unit test function which returns
 * Execution::Passed if cData can successfully
 * convert C++ typed variables to arrays of
 * bytes and vise versa.
 * 
 * It will return Execution::Failed if any
 * function fails to convert data and read
 * back the same exact values.
 * @return Execution 
 */
Execution cData_LaunchTests()
{
    StartOfUnitTest("cData");
    Execution result;

    result = TEST_cData_bools();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_UC();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_char();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_int();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_UI();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_UL();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_long();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_longlong();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_ULL();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_float();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_double();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_string();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    ////////////////////////////////////////////////

    result = TEST_cData_boolsExecutions();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_UCExecutions();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_charExecutions();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_intExecutions();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_UIExecutions();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_ULExecutions();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_longExecutions();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_longlongExecutions();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_ULLExecutions();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_floatExecutions();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_doubleExecutions();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    result = TEST_cData_stringExecutions();
    if(result != Execution::Passed)
    {
        UnitTestFailed();
        return result;
    }

    UnitTestPassed();
    return Execution::Passed;
}