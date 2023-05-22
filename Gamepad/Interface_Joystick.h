/**
 * @file Interface_Joystick.h
 * @author Lyam (lyam.brs@gmail.com)
 * @brief Contains the definition
 * of the function called whenever
 * the timebase executes. This
 * function's purpose is to read
 * the two joysticks of GamePad
 * and queue potential functions
 * to send depending on read
 * values.
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

#ifndef INTERFACE_JOYSTICK_H
  #define INTERFACE_JOYSTICK_H
//=============================================//
//	Include
//=============================================//
#include "Globals.h"


/**
 * @brief Timebase function handling the
 * joysticks periodically. This will call
 * the update function of joystick objects
 * and Queue their planes on runways aswell
 * as execute their received requests.
 */
void InterfaceJoysticks();


#endif