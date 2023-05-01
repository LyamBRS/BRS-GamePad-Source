/**
 * @file Joystick.h
 * @author Lyam (Lyam.brs@gmail.com)
 * @brief This file contains the declaration of
 * the cJoystick class. You can see all of its
 * methods and members in this file.
 * See Joystick.ino for the core methods
 * and handling of this class.
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
    ############    ####      ##   ##########*/

#ifndef JOYSTICK_H
  #define JOYSTICK_H
//=============================================//
//	Include
//=============================================//
#include "Globals.h"
//=============================================//
//	Define
//=============================================//
#define _JOY_MAX_VAL 127
#define _JOY_MIN_VAL -127
#define _JOY_MID_VAL 0

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
Execution CalculateJoystickAxisDeadzone(signed char* axisToModify, signed char Deadzone);

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
Execution CalculateJoystickAxisTrim(signed char* axisToModify, signed char Trim);

/**
 * @brief The cJoystick class allows
 * the handling of a joystick on a PCB.
 * It reads and stores data each time its
 * update function is called.
 */
class cJoystick
 {       
    private:
        int _status = Status::Booting;

        /// @brief The currently stored x axis updated from Update();
        signed char _xAxis = 0;
        /// @brief The currently stored y axis updated from Update();
        signed char _yAxis = 0;
        /// @brief The currently stored switch updated from Update();
        bool _switch = 0;  
  
        /// @brief The currently stored trim to apply when getting x axis
        signed char _xTrim = 0;
        /// @brief The currently stored trim to apply when getting y axis
        signed char _yTrim = 0;

        /// @brief Deazone to apply to the X axis. If within that deadzone, 0 is returned.
        signed char _xDeadzone = 0;
        /// @brief Deazone to apply to the Y axis. If within that deadzone, 0 is returned.
        signed char _yDeadzone = 0;

        /// @brief 0: Normal functions 1: Bypassed (always return 0)
        unsigned char _mode = 0;

        /// @brief Pin used for the X axis
        int _analogXPin = -1;
        int _analogYPin = -1;
        int _switchPin = -1;

    public:
        /// @brief set to true if the class is constructed.
        bool built = false;
        //////////////////////////////////////////////
        cJoystick(int pinAxisX, int pinAxisY, int pinSwitch);
        cJoystick();
        //////////////////////////////////////////////

        /**
         * @brief Set the joystick's mode to a new mode.
         * Modes are listed in the parameter's info.
         * 
         * @param newMode 
         * 0: Default, regular functionning
         * 1: Bypassed (always return 0 / released)
         * @return Execution 
         */
        Execution SetMode(unsigned char newMode);
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
        Execution GetMode(unsigned char* currentMode);

        /**
         * @brief Sets the joystick's X axis deadzone.
         * Values are compensated when Get functions
         * are called.
         * @param newDeadZone
         * Deazone value. sign does not matter. It is
         * applied on both signs (positive / negative)
         * @return Execution 
         */
        Execution SetDeadZone_X(signed char newDeadZone);
        /**
         * @brief Sets the joystick's Y axis deadzone.
         * Values are compensated when Get functions
         * are called.
         * @param newDeadZone
         * Deazone value. sign does not matter. It is
         * applied on both signs (positive / negative)
         * @return Execution 
         */
        Execution SetDeadZone_Y(signed char newDeadZone);
        /**
         * @brief Gets the current deadzone set for
         * the X axis. Default value is 0. Value
         * returned is always positive (0-127)
         * 
         * @param currentDeadZone 
         * Deadzone (0-127)
         * @return Execution 
         */
        Execution GetDeadZone_X(signed char* currentDeadZone);
        /**
         * @brief Gets the current deadzone set for
         * the Y axis. Default value is 0. Value
         * returned is always positive (0-127)
         * @param currentDeadZone
         * Deadzone (0-127)
         * @return Execution 
         */
        Execution GetDeadZone_Y(signed char* currentDeadZone);

        /**
         * @brief Set a new trim for the X axis. Trim
         * is applied when Get functions are called.
         * 
         * @param newTrim 
         * value from -127 to 127. Defaults to 0.
         * @return Execution 
         */
        Execution SetTrim_X(signed char newTrim);
        /**
         * @brief Set a new trim for the Y axis. Trim
         * is applied when Get functions are called.
         * 
         * @param newTrim 
         * value from -127 to 127. Defaults to 0.
         * @return Execution 
         */
        Execution SetTrim_Y(signed char newTrim);
        /**
         * @brief Gets the current trim set for
         * the X axis. Default value is 0.
         * 
         * @param currentTrim 
         * Current trim (-127 to 127). Defaults
         * to 0.
         * @return Execution 
         */
        Execution GetTrim_X(signed char* currentTrim);
        /**
         * @brief Gets the current trim set for
         * the Y axis. Default value is 0.
         * 
         * @param currentTrim 
         * Current trim (-127 to 127). Defaults
         * to 0.
         * @return Execution 
         */
        Execution GetTrim_Y(signed char* currentTrim);

        /**
         * @brief Get the current X axis. The value is
         * updated when Update() is called.
         * 
         * @param currentAxis 
         * Value from (-127 to 127) when no deadzone or
         * trim is applied.
         * @return Execution 
         */
        Execution GetCurrentAxis_X(signed char* currentAxis);
        /**
         * @brief Get the current Y axis. The value is
         * updated when Update() is called.
         * 
         * @param currentAxis 
         * Value from (-127 to 127) when no deadzone or
         * trim is applied.
         * @return Execution 
         */
        Execution GetCurrentAxis_Y(signed char* currentAxis);
        /**
         * @brief Get the current state of the joystick's
         * switch. The value is only updated when
         * Update() is called.
         * @param currentSwitchState 
         * @return Execution 
         */
        Execution GetCurrentSwitch(bool* currentSwitchState);

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
        Execution GetEverything(signed char* currentAxisX, signed char* currentAxisY, bool* currentSwitchState);
        //////////////////////////////////////////////

        /**
         * @brief Time base function which needs to be
         * called at a constant interval in order to
         * update the joystick's values.
         * @return Execution 
         */
        Execution Update();
 };

#endif