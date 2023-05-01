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

#ifndef DATA_UNIT_TEST_H
  #define DATA_UNIT_TEST_H

#pragma region Convertions
/// @brief Tests of boolean convertions
/// @return 
Execution TEST_cData_bools();

/// @brief Tests of unsigned char convertions
/// @return 
Execution TEST_cData_UC();

/// @brief Tests of char convertions
/// @return 
Execution TEST_cData_char();

/// @brief Tests of unsigned short convertions
/// @return 
Execution TEST_cData_US();

/// @brief Tests of short convertions
/// @return 
Execution TEST_cData_short();

/// @brief Tests of int convertions
/// @return 
Execution TEST_cData_int();
/// @brief Tests of unsigned int convertions
/// @return 
Execution TEST_cData_UI();

/// @brief Tests of long convertions
/// @return 
Execution TEST_cData_long();

/// @brief Tests of unsigned long convertions
/// @return 
Execution TEST_cData_UL();

/// @brief Tests of long long convertions
/// @return 
Execution TEST_cData_longlong();

/// @brief Tests of unsigned long long convertions
/// @return 
Execution TEST_cData_ULL();

/// @brief Tests of float convertions
/// @return 
Execution TEST_cData_float();

/// @brief Tests of double convertions
/// @return 
Execution TEST_cData_double();

/// @brief Tests of string convertions
/// @return 
Execution TEST_cData_string();
#pragma endregion

#pragma region Executions
/// @brief Tests of boolean executions results
/// @return 
Execution TEST_cData_boolsExecutions();

/// @brief Tests of unsigned char executions results
/// @return 
Execution TEST_cData_UCExecutions();

/// @brief Tests of char executions results
/// @return 
Execution TEST_cData_charExecutions();

/// @brief Tests of unsigned short executions results
/// @return 
Execution TEST_cData_USExecutions();

/// @brief Tests of short executions results
/// @return 
Execution TEST_cData_shortExecutions();

/// @brief Tests of int executions results
/// @return 
Execution TEST_cData_intExecutions();
/// @brief Tests of unsigned int executions results
/// @return 
Execution TEST_cData_UIExecutions();

/// @brief Tests of long executions results
/// @return 
Execution TEST_cData_longExecutions();

/// @brief Tests of unsigned long executions results
/// @return 
Execution TEST_cData_ULExecutions();

/// @brief Tests of long long executions results
/// @return 
Execution TEST_cData_longlongExecutions();

/// @brief Tests of unsigned long long executions results
/// @return 
Execution TEST_cData_ULLExecutions();

/// @brief Tests of float executions results
/// @return 
Execution TEST_cData_floatExecutions();

/// @brief Tests of double executions results
/// @return 
Execution TEST_cData_doubleExecutions();

/// @brief Tests of string executions results
/// @return 
Execution TEST_cData_stringExecutions();
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
Execution cData_LaunchTests();


#endif