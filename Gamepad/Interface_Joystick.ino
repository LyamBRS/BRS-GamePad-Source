/**
 * @file Interface_Joystick.ino
 * @author Lyam (lyam.brs@gmail.com)
 * @brief Contains the core functions
 * defined and declared in the
 * header file of the same name.
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
#include "Interface_Joystick.h"
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief Timebase function handling the
 * joysticks periodically. This will call
 * the update function of joystick objects
 * and Queue their planes on runways aswell
 * as execute their received requests.
 */
void InterfaceJoysticks()
{
    LeftJoystick.Update();
    RightJoystick.Update();
}