/**
 * @file Switch.h
 * @author Lyam (lyam.brs@gmail.com)
 * @brief This file contains the core
 * classes of the switch class.
 * @version 0.1
 * @date 2023-05-09
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

#ifndef SWITCH_H
  #define SWITCH_H
//=============================================//
//	Include
//=============================================//
#include "Globals.h"
//=============================================//
//	Define
//=============================================//

/**
 * @brief The cSwitch class holds the class that
 * reads buttons on GamePad.
 */
class cSwitch
 {       
    private:
        bool _state = false;
        bool _stateChanged = false;
        int _pinNumber = 0;

    public:
        /// @brief set to true if the class is constructed.
        bool built = false;
        //////////////////////////////////////////////
        cSwitch(int pinSwitch);
        cSwitch();
        //////////////////////////////////////////////

        /**
         * @brief Returns the latest value
         * from the switch that this class is using.
         * 
         * @param switchValue 
         * @return Execution 
         */
        Execution GetLatestValue(bool* switchValue);

        /**
         * @brief Time base function which needs to be
         * called at a constant interval in order to
         * update the joystick's values.
         * @return Execution 
         */
        Execution Update();
 };

#endif