/**
 * @file Handler_Timebase.h
 * @author Lyam (lyam.brs@gmail.com)
 * @brief Contains the definitions of 
 * the timebase callback function
 * and defines specific to timebase
 * operations and executions.
 * @version 0.1
 * @date 2023-05-08
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

#ifndef HANDLER_TIMEBASE_H
  #define HANDLER_TIMEBASE_H
//=============================================//
//	Include
//=============================================//
#include "Globals.h"

/**
 * @brief This function is the core callback
 * function of your application. It is executed
 * each X amount of clock cycles and executes all
 * the interfaces or handlers within your
 * program.
 */
void ApplicationCallback();

#endif