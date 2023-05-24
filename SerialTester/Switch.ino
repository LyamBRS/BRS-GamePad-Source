/**
 * @file Switch.ino
 * @author Lyam (lyam.brs@gmail.com)
 * @brief This file contains the core
 * methods of the switch class.
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
    ############    ####      ##   ##########   */
/////////////////////////////////////////////////////////////////////////////
#include "Switch.h"
////////////////////// - Local Defines

cSwitch::cSwitch(int pinSwitch)
{
    _pinNumber = pinSwitch;
    pinMode(pinSwitch, INPUT);
    built = true;
}
cSwitch::cSwitch()
{
    built = false;
}


/**
 * @brief Returns the latest value
 * from the switch that this class is using.
 * 
 * @param switchValue 
 * @return Execution 
 */
Execution cSwitch::GetLatestValue(bool* switchValue)
{
    if(_stateChanged)
    {
        _stateChanged = false;
        *switchValue = _state;
        return Execution::Passed;
    }
    else
    {
        *switchValue = _state;
        return Execution::Unecessary;      
    }
    return Execution::Crashed;
}

/**
 * @brief Time base function which needs to be
 * called at a constant interval in order to
 * update the joystick's values.
 * @return Execution 
 */
Execution cSwitch::Update()
{
    bool newValue = digitalRead(_pinNumber);

    if(newValue != _state)
    {
        _state = newValue;
        _stateChanged = true;
        return Execution::Passed;
    }
    return Execution::Unecessary;
}