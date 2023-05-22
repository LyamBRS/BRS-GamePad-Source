/**
 * @file Handler_Timebase.ino
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
#include "Handler_Timebase.h"
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief This function is the core callback
 * function of your application. It is executed
 * each X amount of clock cycles and executes all
 * the interfaces or handlers within your
 * program.
 */
void ApplicationCallback()
{
    InterfaceSwitch();
    InterfaceJoysticks();

    ProtocolBFIO();

    InterfaceRGB();
}