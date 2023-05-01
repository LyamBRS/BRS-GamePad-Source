/**
 * @file _UNIT_TEST_Joystick.h
 * @author Lyam (Lyam.brs@gmail.com)
 * @brief This file contains the declaration
 * of unit test functions made to test Joystick
 * class and functions
 * @version 0.1
 * @date 2023-05-01
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

#ifndef JOYSTICK_UNIT_TEST_H
  #define JOYSTICK_UNIT_TEST_H

#pragma region Functions
/**
 * @brief Unit test function that tests every
 * aspects of CalculateJoystickAxisDeadzone.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_CalculateJoystickAxisDeadzone();
/**
 * @brief Unit test function that tests every
 * aspects of CalculateJoystickAxisTrim.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_CalculateJoystickAxisTrim();
#pragma endregion

#pragma region Methods
/**
 * @brief Unit test function that tests the
 * Get and the Set methods for the Joystick's
 * modes.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetSetMode();

/**
 * @brief Unit test function that tests the
 * Get and the Set methods for the Joystick's
 * DeadZone_X.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetSetDeadZone_X();

/**
 * @brief Unit test function that tests the
 * Get and the Set methods for the Joystick's
 * DeadZone_Y.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetSetDeadZone_Y();

/**
 * @brief Unit test function that tests the
 * Get and the Set methods for the Joystick's
 * Trim_X.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetSetTrim_X();

/**
 * @brief Unit test function that tests the
 * Get and the Set methods for the Joystick's
 * Trim_Y.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetSetTrim_Y();

/**
 * @brief Unit test function that tests the
 * Get methods for the Joystick's
 * CurrentAxis_X.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetCurrentAxis_X();

/**
 * @brief Unit test function that tests the
 * Get methods for the Joystick's
 * CurrentAxis_Y.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetCurrentAxis_Y();

/**
 * @brief Unit test function that tests the
 * Get method of the Joystick's CurrentSwitch.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetCurrentSwitch();

/**
 * @brief Unit test function that tests the
 * Get method of the Joystick's Everything.
 * This function is expected to behave like
 * GetCurrentSwitch and GetCurrentAxis
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetEverything();

/**
 * @brief Unit test function that tests the
 * Update method of the Joystick's class.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * 
 * @attention
 * YOU MUST NOT TOUCH THE JOYSTICKS DURING
 * UNIT TESTS.
 * 
 * @return Execution 
 */
Execution TEST_JOYSTICK_Update();
#pragma endregion

/**
 * @brief Unit test function which returns
 * Execution::Passed if cJoystick can 
 * successfully be used to read and analyze
 * joysticks beahaviours
 * 
 * It will return Execution::Failed if any
 * function fails.
 * @return Execution 
 */
Execution cJoystick_LaunchTests();


#endif