/**
 * @file _UNIT_TEST.h
 * @author your name (you@domain.com)
 * @brief 
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

#include "_UNIT_TEST.h"

/**
 * @brief Function called at the start of a whole
 * unit test. It resets the variables used
 * through out steps and test units and displays
 * the header of the current unit test that is
 * executed.
 * @attention Do not call this at the start of individual tests. Only at the start of a unit.
 * @param nameOfUnitTest 
 * Name of the unit being tested.
 * @return Execution 
 */
Execution StartOfUnitTest(const char* nameOfUnitTest)
{
    Serial.println("");
    Serial.println("====================");
    Serial.print("[UNIT TEST] - ");
    Serial.println(nameOfUnitTest);

    _testStepCounter = 0;
    return Execution::Passed;
}

/**
 * @brief Function to call at the very top
 * of individual tests from a unit test.
 * This will print the name of the current
 * test aswell as reset the counter which
 * keeps track of the step numbers within
 * a test.
 * 
 * @param nameOfTest 
 * @return Execution 
 */
Execution TestStart(const char* nameOfTest)
{
    Serial.print("|\t[");
    Serial.print(nameOfTest);
    Serial.println("]");

    _testStepCounter = 0;
    return Execution::Passed;
}

/**
 * @brief Function to call when a step inside a
 * test from a unit test fails. This is to call
 * right before you return a fail to the main
 * function and marks the end of that specific test,
 * not necessarly of the whole unit test.
 * 
 * @param reasonForFailing 
 * @return Execution 
 */
Execution TestFailed(const char* reasonForFailing)
{
    Serial.print("|\t|\tTests done: ");
    Serial.println(std::to_string(_testStepCounter).c_str());

    Serial.print("|\t|\tReason:     ");
    Serial.println(reasonForFailing);

    Serial.println("|\t|\tResult:     [FAIL]");

    return Execution::Passed;
}


Execution PrintChunk(unsigned short chunkToPrint)
{
    int extractedType = 0;
    unsigned char extractedByte = 0;
    Execution execution;
    Serial.print(" Chunk: ");
    Serial.print("\t");

    execution = Chunk.ToType(chunkToPrint, &extractedType);
    if(execution != Execution::Passed)
    {
        Serial.print("FAIL");
        Serial.println("\t");
        Serial.println("");
        return Execution::Failed;            
    }

    switch(extractedType)
    {
        case(ChunkType::Byte):
            Serial.print("BYTE \t");
            break;

        case(ChunkType::Start):
            Serial.print("START\t");
            break;

        case(ChunkType::Div):
            Serial.print("DIV\t  ");
            break;

        case(ChunkType::Check):
            Serial.print("CHECK\t");
            break;
    }

    execution = Chunk.ToByte(chunkToPrint, &extractedByte);
    if(execution != Execution::Passed)
    {
        Serial.print("FAIL");
        Serial.println("\t");
        Serial.println("");
        return Execution::Failed;            
    }

    Serial.print(std::to_string(extractedByte).c_str());
    Serial.println("");
    return Execution::Passed;
}

/**
 * @brief This function will print
 * out a segment or series of
 * chunks until an error is received.
 * 
 * @param packetToPrint 
 * array of chunks to print.
 * @return Execution 
 */
Execution PrintOutPacket(unsigned short* packetToPrint, int max)
{
    Execution execution;
    for(int index = 0; index<max; index++)
    {
        unsigned short chunk = packetToPrint[index];

        Serial.print("index: ");
        Serial.print(index);
        execution = PrintChunk(chunk);
        if(execution != Execution::Passed)
        {
            return Execution::Passed;
        }
    }
    return Execution::Passed;
}

/**
 * @brief This function will print
 * out a segment or series of
 * chunks until an error is received.
 * 
 * @param packetToPrint 
 * array of chunks to print.
 * @return Execution 
 */
Execution PrintOutPacket(unsigned short* packetToPrint)
{
    Execution execution;
    for(int index = 0; index<MAX_PLANE_PASSENGER_CAPACITY; index++)
    {
        unsigned short chunk = packetToPrint[index];

        Serial.print("index: ");
        Serial.print(index);
        execution = PrintChunk(chunk);
        if(execution != Execution::Passed)
        {
            return Execution::Passed;
        }
    }
    return Execution::Passed;
}

/**
 * @brief Normalizes the printing of
 * expected values turned into strings
 * versus received values for printing
 * out failed tests.
 * 
 * @param expected 
 * What were we expected to get from that test?
 * @param gotten 
 * What did we end up getting instead?
 * @return Execution 
 */
Execution TestExpectedVSGotten(const char* expected, const char* gotten)
{
    Serial.print("|\t|\tExpected:   ");
    Serial.println(expected);

    Serial.print("|\t|\tReceived:   ");
    Serial.println(gotten);

    return Execution::Passed;
}

/**
 * @brief Function that displays whats the
 * execution that was resulted from
 * a function call. This function is
 * indented like TestFails.
 * 
 * @param execution 
 * @return Execution 
 */
Execution TestExecution(int execution)
{
    Serial.print("|\t|\tExecution:  ");

    switch(execution)
    {
        case(Execution::Bypassed):
            Serial.println("Bypassed");
            break;

        case(Execution::Crashed):
            Serial.println("Crashed");
            break;

        case(Execution::Failed):
            Serial.println("Failed");
            break;

        case(Execution::Incompatibility):
            Serial.println("Incompatibility");
            break;

        case(Execution::NoConnection):
            Serial.println("NoConnection");
            break;

        case(Execution::Passed):
            Serial.println("Passed");
            break;

        case(Execution::Unecessary):
            Serial.println("Unecessary");
            break;

        default:
            Serial.println("[UNKNOWN]");
            break;       
    }

    return Execution::Passed;
}

/**
 * @brief Function to call when all the steps
 * of a test within an unit test passes.
 * This function will mark the end of a test,
 * not a test step.
 * 
 * @return Execution 
 */
Execution TestPassed()
{
    Serial.print("|\t|\tTests done: ");
    Serial.println(std::to_string(_testStepCounter).c_str());

    Serial.println("|\t|\tResult:    [PASS]");

    return Execution::Passed;
}

/**
 * @brief Function to call each time a
 * singular test is executed. This function
 * increases a value which keeps track of
 * hoe many steps were executed for that
 * specific test of the unit test.
 * @return Execution 
 */
Execution TestStepDone()
{
    _testStepCounter++;
    return Execution::Passed;
}

/**
 * @brief Function to call when your unit test
 * fails and quits further testing as a result
 * of one of the tests failing.
 * @return Execution 
 */
Execution UnitTestFailed()
{
    Serial.println("[UNIT TEST RESULTS] - FAIL");
    return Execution::Passed;
}
/**
 * @brief Function called at the end of your
 * main unit test function when it passes all
 * of its tests.
 * @return Execution 
 */
Execution UnitTestPassed()
{
    Serial.println("[UNIT TEST RESULTS] - PASS");
    return Execution::Passed;
}

/**
 * @brief Function which launches
 * every unit tests for this program.
 * They are printed in the debug window
 * and it also handles the LED indicators
 * which will indicate to the user through
 * hardware which unit failed.
 */
Execution TestAllUnits()
{
    Serial.println("#############################");
    Serial.println("# -[START OF UNIT TESTING]- #");
    Serial.println("#############################");
    Execution testResults;

    testResults = RGB_LaunchTests();
    if(testResults == Execution::Bypassed)
    {
        Serial.println("#############################");
        Serial.println("! ! !- TEST  BYPASSED - ! ! !");
        Serial.println("#############################");    
    }
    if(testResults == Execution::Failed)
    {
        Rgb.SetColors(UT_ERROR_COLOR);
        Rgb.SetErrorMode(UT_CRGB_ERROR_CODE);
        return testResults;
    }

    testResults = cChunk_LaunchTests();
    if(testResults == Execution::Bypassed)
    {
        Serial.println("#############################");
        Serial.println("! ! !- TEST  BYPASSED - ! ! !");
        Serial.println("#############################");    
    }
    if(testResults == Execution::Failed)
    {
        Rgb.SetColors(UT_ERROR_COLOR);
        Rgb.SetErrorMode(UT_CCHUNK_ERROR_CODE);
        return testResults;
    }

    testResults = cData_LaunchTests();
    if(testResults == Execution::Bypassed)
    {
        Serial.println("#############################");
        Serial.println("! ! !- TEST  BYPASSED - ! ! !");
        Serial.println("#############################");    
    }
    if(testResults == Execution::Failed)
    {
        Rgb.SetColors(UT_ERROR_COLOR);
        Rgb.SetErrorMode(UT_CDATA_ERROR_CODE);
        return testResults;
    }

    testResults = cJoystick_LaunchTests();
    if(testResults == Execution::Bypassed)
    {
        Serial.println("#############################");
        Serial.println("! ! !- TEST  BYPASSED - ! ! !");
        Serial.println("#############################");    
    }
    if(testResults == Execution::Failed)
    {
        Rgb.SetColors(UT_ERROR_COLOR);
        Rgb.SetErrorMode(UT_CJOYSTICK_ERROR_CODE);
        return testResults;
    }

    testResults = cPacket_LaunchTests();
    if(testResults == Execution::Bypassed)
    {
        Serial.println("#############################");
        Serial.println("! ! !- TEST  BYPASSED - ! ! !");
        Serial.println("#############################");    
    }
    if(testResults == Execution::Failed)
    {
        Rgb.SetColors(UT_ERROR_COLOR);
        Rgb.SetErrorMode(UT_CPACKET_ERROR_CODE);
        return testResults;
    }

    // SETTING SUCCESSFUL UNIT TEST RGB COLOR
    Rgb.SetColors(UT_PASSED_COLOR);
    Rgb.SetErrorMode(UT_PASSED_CODE);

    return Execution::Passed;
}