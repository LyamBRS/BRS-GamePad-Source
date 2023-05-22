/**
 * @file _UNIT_TEST_Rgb.h
 * @author Lyam (lyam.brs@gmail.com)
 * @brief This file contains the various
 * definitions of unit test functions used
 * to verify that the RGB class functions
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

#ifndef RGB_UNIT_TEST_H
  #define RGB_UNIT_TEST_H

/**
 * @brief Function that tests the integrity
 * of this RGB method. It tests that colors
 * are applied and limits return the correct
 * execution value.
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_SetColors();
/**
 * @brief Function that tests the integrity
 * of this RGB method. It tests that modes
 * are applied and limits return the correct
 * execution value.
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_SetMode();
/**
 * @brief Function that tests the integrity
 * of this RGB method. It tests that animations
 * are applied and limits return the correct
 * execution value.
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_SetAnimations();
/**
 * @brief Function that tests the integrity
 * of this RGB method. It tests that errors
 * are applied and limits return the correct
 * execution value.
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_SetErrorMode();
/**
 * @brief Function that tests the integrity
 * of this RGB method. It tests that the
 * correct value is returned depending on
 * modes and other animation factors
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_GetCycleRed();
/**
 * @brief Function that tests the integrity
 * of this RGB method. It tests that the
 * correct value is returned depending on
 * modes and other animation factors
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_GetCycleGreen();
/**
 * @brief Function that tests the integrity
 * of this RGB method. It tests that the
 * correct value is returned depending on
 * modes and other animation factors
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_GetCycleBlue();
/**
 * @brief Function that tests the integrity
 * of this RGB method. It verifies that
 * the colors are updated correctly.
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_UpdateColors();
/**
 * @brief Function that tests the integrity
 * of this RGB method. It tests that updates
 * occures when it is called multiple times.
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_Update();
/**
 * @brief Unit test function which returns
 * Execution::Passed if RGB works
 * successfully for each methods it has.
 * 
 * It will return Execution::Failed if any
 * function fails to convert data and read
 * back the same exact values.
 * @return Execution 
 */
Execution RGB_LaunchTests();


#endif