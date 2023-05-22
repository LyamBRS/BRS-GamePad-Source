/**
 * @file Joystick.ino
 * @author Lyam (Lyam.brs@gmail.com)
 * @brief Declarations of cJoystick's methods.
 * Each method is written here for you to
 * see how they work inside of them.
 * 
 * See Joystick.h for definitions of the cJoystick class.
 * @version 0.1
 * @date 2023-04-28
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
#include "Joystick.h"
////////////////////// - Local Defines

/**
 * @brief Function that executes mathematics to
 * return a new value from -127 to 127 with
 * some amount of deadzone near the middle.
 * 
 * A deadzone of 0 will bypass this function.
 * 
 * @param Deadzone 
 * Deadzone to apply to axisToModify.
 * Value needs to be within 0 to 127.
 * @param axisToModify
 * Pointer to the axis value that will be
 * modified.
 * @return Execution 
 */
Execution CalculateJoystickAxisDeadzone(int* axisToModify, int Deadzone)
{
    if(Deadzone > 0)
    {
        int oldAxis = *axisToModify;
        double maxAxisWithDeadzone = _JOY_MAX_VAL - (double) Deadzone;
        double currentAxis = (double)(*axisToModify);

        if(oldAxis <= Deadzone && oldAxis >= -Deadzone)
        {
            *axisToModify = _JOY_MID_VAL;
            return Execution::Passed;
        }
        else
        {
            // Converts deadzone offset applied so the axis is still from -2048 to 2048
            currentAxis = ((currentAxis * maxAxisWithDeadzone) / _JOY_MAX_VAL);
            if(oldAxis < 0)
            {
                currentAxis = currentAxis + (double) Deadzone;
            }
            else
            {
                currentAxis = currentAxis - (double) Deadzone;
            }   
            *axisToModify = (int)currentAxis;
            return Execution::Passed;
        }
    }
    else
    {
        if(Deadzone < 0)
        {
            return Execution::Failed;
        }
        return Execution::Unecessary;
    }
}

/**
 * @brief Executes math functions to apply a trim
 * to a specified axis and puts the result on a
 * specified pointer.
 * 
 * @attention
 * It is adviced that you call this function
 * AFTER you passed the axis through 
 * CalculateJoystickAxisDeadzone
 * @param axisToModify 
 * Pointer to the axis that will be modified.
 * @param Trim 
 * Trim that will be applied to currentAxisValue.
 * Trim goes from -127 to 127.
 * @return Execution 
 */
Execution CalculateJoystickAxisTrim(int* axisToModify, int Trim)
{
    if(Trim != 0)
    {
        if(*axisToModify == _JOY_MID_VAL)
        {
            *axisToModify = Trim;
            return Execution::Passed;
        }
        
        double maxValue = 0;
        double resultAxis = (double) *axisToModify;
        double trim = (double)Trim;
        
        if(Trim > 0){
            maxValue = _JOY_MAX_VAL - trim;
        }
        else{
            maxValue = _JOY_MAX_VAL + trim;
        }
        resultAxis = ((resultAxis * maxValue)/_JOY_MAX_VAL) + trim;
        *axisToModify = (int)resultAxis;
        return Execution::Passed;
    }
    else
    {
        return Execution::Unecessary;
    }
}

/////////////////////////////////////////////////////////////////////////////
cJoystick::cJoystick(int pinAxisX, int pinAxisY, int pinSwitch)
{
    if(pinAxisX < 46){
        _analogXPin = pinAxisX;
        pinMode(_analogXPin, INPUT);
    }
    else{
        built = false;
        return;
    }

    if(pinAxisY < 46 && pinAxisX != pinAxisY){
        _analogYPin = pinAxisY;
        pinMode(_analogYPin, INPUT);
    }
    else{
        built = false;
        return;
    }

    if(pinSwitch < 46 && pinSwitch != pinAxisY && pinSwitch != pinAxisX){
        _switchPin = pinSwitch;
        pinMode(_switchPin, INPUT_PULLUP);
    }
    else{
        built = false;
        return;
    }

    built = true;
}

cJoystick::cJoystick()
{
}

/**
 * @brief Set the joystick's mode to a new mode.
 * Modes are listed in the parameter's info.
 * 
 * @param newMode 
 * 0: Default, regular functionning
 * 1: Bypassed (always return 0 / released)
 * @return Execution 
 */
Execution cJoystick::SetMode(unsigned char newMode)
{
    if(newMode < 2)
    {
        if(newMode != _mode)
        {
            _mode = newMode;
            return Execution::Passed;
        }
        else
        {
            return Execution::Unecessary;
        }
    }
    else
    {
        return Execution::Failed;
    }
}

/**
 * @brief Get the joystick's current mode.
 * Use SetMode to set the joystick into
 * another mode.
 * 
 * @param currentMode 
 * 0: Default, regular functionning
 * 1: Bypassed (always return 0 / released)
 * @return Execution 
 */
Execution cJoystick::GetMode(unsigned char* currentMode)
{
    *currentMode = _mode;
    return Execution::Passed;
}

/**
 * @brief Sets the joystick's X axis deadzone.
 * Values are compensated when Get functions
 * are called.
 * @param newDeadZone
 * Deazone value. sign does not matter. It is
 * applied on both signs (positive / negative)
 * @return Execution 
 */
Execution cJoystick::SetDeadZone_X(int newDeadZone)
{
    if(newDeadZone != _xDeadzone)
    {
        if(newDeadZone < 0){
            newDeadZone = -newDeadZone;
        }
        _xDeadzone = newDeadZone;
        return Execution::Passed;
    }
    else
    {
        return Execution::Unecessary;
    }
}
/**
 * @brief Sets the joystick's Y axis deadzone.
 * Values are compensated when Get functions
 * are called.
 * @param newDeadZone
 * Deazone value. sign does not matter. It is
 * applied on both signs (positive / negative)
 * @return Execution 
 */
Execution cJoystick::SetDeadZone_Y(int newDeadZone)
{
    if(newDeadZone != _yDeadzone)
    {
        if(newDeadZone < 0){
            newDeadZone = -newDeadZone;
        }
        _yDeadzone = newDeadZone;
        return Execution::Passed;
    }
    else
    {
        return Execution::Unecessary;
    }
}
/**
 * @brief Gets the current deadzone set for
 * the X axis. Default value is 0. Value
 * returned is always positive (0-127)
 * 
 * @param currentDeadZone 
 * Deadzone (0-127)
 * @return Execution 
 */
Execution cJoystick::GetDeadZone_X(int* currentDeadZone)
{
    *currentDeadZone = _xDeadzone;
    return Execution::Passed;
}
/**
 * @brief Gets the current deadzone set for
 * the Y axis. Default value is 0. Value
 * returned is always positive (0-127)
 * @param currentDeadZone
 * Deadzone (0-127)
 * @return Execution 
 */
Execution cJoystick::GetDeadZone_Y(int* currentDeadZone)
{
    *currentDeadZone = _yDeadzone;
    return Execution::Passed;
}

/**
 * @brief Set a new trim for the X axis. Trim
 * is applied when Get functions are called.
 * 
 * @param newTrim 
 * value from -127 to 127. Defaults to 0.
 * @return Execution 
 */
Execution cJoystick::SetTrim_X(int newTrim)
{
    if(newTrim != _xTrim)
    {
        _xTrim = newTrim;
        return Execution::Passed;
    }
    else
    {
        return Execution::Unecessary;
    }
}
/**
 * @brief Set a new trim for the Y axis. Trim
 * is applied when Get functions are called.
 * 
 * @param newTrim 
 * value from -127 to 127. Defaults to 0.
 * @return Execution 
 */
Execution cJoystick::SetTrim_Y(int newTrim)
{
    if(newTrim != _yTrim)
    {
        _yTrim = newTrim;
        return Execution::Passed;
    }
    else
    {
        return Execution::Unecessary;
    }
}
/**
 * @brief Gets the current trim set for
 * the X axis. Default value is 0.
 * 
 * @param currentTrim 
 * Current trim (-127 to 127). Defaults
 * to 0.
 * @return Execution 
 */
Execution cJoystick::GetTrim_X(int* currentTrim)
{
    *currentTrim = _xTrim;
    return Execution::Passed;
}
/**
 * @brief Gets the current trim set for
 * the Y axis. Default value is 0.
 * 
 * @param currentTrim 
 * Current trim (-127 to 127). Defaults
 * to 0.
 * @return Execution 
 */
Execution cJoystick::GetTrim_Y(int* currentTrim)
{
    *currentTrim = _yTrim;
    return Execution::Passed;
}

/**
 * @brief Get the current X axis. The value is
 * updated when Update() is called.
 * 
 * @param currentAxis 
 * Value from (-127 to 127) when no deadzone or
 * trim is applied.
 * @return Execution 
 */
Execution cJoystick::GetCurrentAxis_X(int* currentAxis)
{
    if(_mode == 0)
    {
        *currentAxis = _xAxis;
        return Execution::Passed;
    }
    else
    {
        *currentAxis = 0;
        return Execution::Passed;
    }
}
/**
 * @brief Get the current Y axis. The value is
 * updated when Update() is called.
 * 
 * @param currentAxis 
 * Value from (-127 to 127) when no deadzone or
 * trim is applied.
 * @return Execution 
 */
Execution cJoystick::GetCurrentAxis_Y(int* currentAxis)
{
    if(_mode == 0)
    {
        *currentAxis = _yAxis;
        return Execution::Passed;
    }
    else
    {
        *currentAxis = 0;
        return Execution::Passed;
    }
}
/**
 * @brief Get the current state of the joystick's
 * switch. The value is only updated when
 * Update() is called.
 * @param currentSwitchState 
 * @return Execution 
 */
Execution cJoystick::GetCurrentSwitch(bool* currentSwitchState)
{
    if(_mode == 0)
    {
        *currentSwitchState = _switch;
        return Execution::Passed;
    }
    else
    {
        *currentSwitchState = false;
        return Execution::Passed;
    }
}

/**
 * @brief Gets the current state of all the
 * joysticks's inputs. This is the equivalent
 * of calling each Get functions related to
 * current values in one big function.
 * 
 * The values are only updated when Update()
 * is called.
 * 
 * @param currentAxisX 
 * @param currentAxisY 
 * @param currentSwitchState 
 * @return Execution 
 */
Execution cJoystick::GetEverything(int* currentAxisX, int* currentAxisY, bool* currentSwitchState)
{
    if(GetCurrentAxis_X(currentAxisX) != Execution::Passed){
        return Execution::Failed;
    }

    if(GetCurrentAxis_Y(currentAxisY) != Execution::Passed){
        return Execution::Failed;
    }

    if(GetCurrentSwitch(currentSwitchState) != Execution::Passed){
        return Execution::Failed;
    }

    return Execution::Passed;
}
//////////////////////////////////////////

/**
 * @brief Time base function which needs to be
 * called at a constant interval in order to
 * update the joystick's values.
 * @return Execution 
 */
Execution cJoystick::Update()
{
    if(built)
    {
        if(_mode == 0)
        {
            _xAxis = analogRead(_analogXPin) - 2048;
            _yAxis = analogRead(_analogYPin) - 2048;
            _switch = digitalRead(_switchPin);

            // Converting unsigned value to signed value to keep 0 as not moving
            // _xAxis = (int)(xAxis - _JOY_MAX_VAL);
            // _yAxis = (int)(yAxis - _JOY_MAX_VAL);

            CalculateJoystickAxisDeadzone(&_xAxis, _xDeadzone);
            CalculateJoystickAxisDeadzone(&_yAxis, _yDeadzone);

            CalculateJoystickAxisTrim(&_xAxis, _xTrim);
            CalculateJoystickAxisTrim(&_yAxis, _yTrim);
            return Execution::Passed;
        }
        else
        {
            _xAxis = _JOY_MID_VAL;
            _yAxis = _JOY_MID_VAL;
            _switch = _JOY_MID_VAL;
            return Execution::Passed;
        }
    }
    else
    {
        return Execution::Failed;
    }
    return Execution::Crashed;
}