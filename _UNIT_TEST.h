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

#ifndef _UNIT_TEST_H
    #define _UNIT_TEST_H

#include "Globals.h"

/**
 * @brief Used to keep track
 * of how many steps a test from
 * a unit test takes.
 */
long double _testStepCounter = 0;

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
Execution StartOfUnitTest(const char* nameOfUnitTest);

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
Execution TestStart(const char* nameOfTest);

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
Execution TestFailed(const char* reasonForFailing);

/**
 * @brief Function to call when all the steps
 * of a test within an unit test passes.
 * This function will mark the end of a test,
 * not a test step.
 * 
 * @return Execution 
 */
Execution TestPassed();

/**
 * @brief Function to call each time a
 * singular test is executed. This function
 * increases a value which keeps track of
 * hoe many steps were executed for that
 * specific test of the unit test.
 * @return Execution 
 */
Execution TestStepDone();

/**
 * @brief Function to call when your unit test
 * fails and quits further testing as a result
 * of one of the tests failing.
 * @return Execution 
 */
Execution UnitTestFailed();
/**
 * @brief Function called at the end of your
 * main unit test function when it passes all
 * of its tests.
 * @return Execution 
 */
Execution UnitTestPassed();

/**
 * @brief Function which launches
 * every unit tests for this program.
 * They are printed in the debug window
 * and it also handles the LED indicators
 * which will indicate to the user through
 * hardware which unit failed.
 */
Execution TestAllUnits();

#endif