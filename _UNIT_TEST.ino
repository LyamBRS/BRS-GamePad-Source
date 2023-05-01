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



    // SETTING SUCCESSFUL UNIT TEST RGB COLOR
    Rgb.SetColors(UT_PASSED_COLOR);
    Rgb.SetErrorMode(UT_PASSED_CODE);

    return Execution::Passed;
}