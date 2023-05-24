/*
    ############    ############     ##########
    ############    ############     ##########
              ##              ##   ## 
    ####    ##      ####    ##     ############
    ####    ##      ####    ##     ############
              ##              ##             ##
    ############    ####      ##   ##########
    ############    ####      ##   ##########

    Title: BFIO.h
    Author: Lyam
*/

#ifndef BFIO_H
  #define BFIO_H
//=============================================//
//	Includes
//=============================================//
#include "Globals.h"
//=============================================//
//	Global Variables
//=============================================//
#define BFIO_TIMEOUT_MS 1000
#define BFIO_VERSION_ID 202305091044
#define BFIO_GIT_REPOSITORY "https://github.com/LyamBRS/BrSpand_GamePad.git"
#define _AMOUNT_OF_SUPPORTED_ID 20
#define MAX_PLANE_PASSENGER_CAPACITY 255

unsigned char supportedBFIOIDs[_AMOUNT_OF_SUPPORTED_ID] = {
    0, // [MANDATORY]  - Ping(None)
    1, // [MANDATORY]  - Status (Get)
    2, // [MANDATORY]  - Handshake
    3, // [MANDATORY]  - ErrorMessage
    4, // [MANDATORY]  - Device Type
    5, // [MANDATORY]  - ID
    6, // [MANDATORY]  - RESTART PROTOCOL
    7, // [MANDATORY]  - GetUniversalInfos
    8, // [MANDATORY]  - HandlingError
    9, // [MANDATORY]  - RESERVED
    10, // [MANDATORY] - RESERVED

    20, // [SPECIFIC] -TX: 0 -RX: 0 - ResetInputs(None)                                                     -> None
    21, // [SPECIFIC] -TX: 1 -RX: 1 - Joystick(unsigned char JoystickID)                                    -> char X, char Y, bool button
    22, // [SPECIFIC] -TX: 2 -RX: 1 - JoystickAxis(unsigned char Joystick_ID, unsigned char AxisID)         -> char AxisValue
    23, // [SPECIFIC] -TX: 6 -RX: 6 - Joysticks(char X, char Y, char X, char Y, bool left, bool right)      -> char X, char Y, char X, char Y, bool left, bool right
    24, // [SPECIFIC] -TX: 2 -RX: 1 - Trim(unsigned char JoystickID, unsigned char AxisID)                  -> char Trim
    25, // [SPECIFIC] -TX: 2 -RX: 1 - Deadzone(unsigned char JoystickID, unsigned char AxisID)              -> char Deadzone
    26, // [SPECIFIC] -TX: 1 -RX: 1 - Button(unsigned char ButtonID)                                        -> unsigned char buttonState
    27, // [SPECIFIC] -TX: 5 -RX: 5 - Buttons(uc ButtonA, uc ButtonB, uc ButtonC, uc ButtonD, uc ButtonE)   -> uc ButtonA, uc ButtonB, uc ButtonC, uc ButtonD, uc ButtonE
    28 // [SPECIFIC] -TX: 3 -RX: 3 - RGB(uc Red, uc Green, uc Blue)                                        -> uc Red, uc Green, uc Blue
};
//=============================================//
//	Classes
//=============================================//

/**
 * @brief Class that handles the high level
 * methods of the BFIO protocol. This also
 * contains the mandatory functions so you
 * can observe how they are defined and
 * handled.
 * 
 */
class cBFIO
 {       
    private:
           
    public:
        //////////////////////////////////// - CONSTRUCTOR -
        cBFIO();
        //////////////////////////////////// - Mandatory Functions -

        /**
         * @brief Mandatory BFIO function. This function
         * handles what to do when a ping function packet 
         * arrives at the master -> slave terminal. 
         * 
         * It automatically generates and queues the answer
         * it needs to send in the master -> slave terminal.
         * 
         * @param receivedPacket 
         * @param receivedPacketSize 
         * @return Execution 
         */
        // Execution Arrival_Ping(unsigned short* receivedPacket, int receivedPacketSize);

        // Execution Depart_Ping(unsigned );
 };

#endif