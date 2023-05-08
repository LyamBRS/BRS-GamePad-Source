/**
 * @file Protocol_BFIO.h
 * @author Lyam (lyam.brs@gmail.com)
 * @brief Contains the definition
 * of the function called whenever
 * the timebase executes. This function
 * handles all BFIO methods and objects.
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

#ifndef PROTOCOL_BFIO_H
  #define PROTOCOL_BFIO_H
//=============================================//
//	Include
//=============================================//
#include "Globals.h"


/**
 * @brief Timebase function handling the
 * BFIO protocol periodically. This will call
 * the update function of all objects
 * and Queue their planes on runways aswell
 * as execute their received requests.
 */
void ProtocolBFIO();


#endif