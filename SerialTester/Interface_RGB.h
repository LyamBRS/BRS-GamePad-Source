/**
 * @file Interface_RGB.h
 * @author Lyam (lyam.brs@gmail.com)
 * @brief Contains the definition
 * of the function called whenever
 * the timebase executes. This function
 * updates the RGB on GamePad's board
 * and parses arguments or queues their 
 * planes for takeoff.
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

#ifndef INTERFACE_SWITCH_H
  #define INTERFACE_SWITCH_H
//=============================================//
//	Include
//=============================================//
#include "Globals.h"


/**
 * @brief Timebase function handling the
 * switches periodically. This will call
 * the update function of switches objects
 * and Queue their planes on runways aswell
 * as execute their received requests.
 */
void InterfaceRGB();


#endif