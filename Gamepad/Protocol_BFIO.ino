/**
 * @file Protocol_BFIO.ino
 * @author Lyam (lyam.brs@gmail.com)
 * @brief Contains the core function
 * executed each timebase cycle
 * that parses all the BFIO plane
 * shenanigans.
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
    ############    ####      ##   ##########   */
/////////////////////////////////////////////////////////////////////////////
#include "Protocol_BFIO.h"
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief Timebase function handling the
 * BFIO protocol periodically. This will call
 * the update function of all objects
 * and Queue their planes on runways aswell
 * as execute their received requests.
 */
void ProtocolBFIO()
{
    // TO DO
}