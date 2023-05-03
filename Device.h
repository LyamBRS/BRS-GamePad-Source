/**
 * @file Device.h
 * @author Lyam (LyamBRS@gmail.com)
 * @brief This file contains the declaration
 * of the global class: "Device".
 * See Device.ino for the insides of that
 * class.
 * @version 0.1
 * @date 2023-04-25
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

#ifndef DEVICE_H
  #define DEVICE_H
//================================================================================================//
//	Include
//================================================================================================//
#include "Globals.h"
//================================================================================================//
//	Define
//================================================================================================//
  
/**
 * @brief The Device class is a class that
 * holds various information specific to the
 * device such as functions and members useful
 * to interface the program as a device.
 */
class cDevice
 {       
    private:
        int _status = Status::Booting;   
  
    public:
        /// @brief set to true if the class is constructed.
        bool built = false;
        //////////////////////////////////////////////
        cDevice();
        //////////////////////////////////////////////

        /**
         * @brief Get the status of the BRS device.
         * List of status are explained in the Status
         * enum.
         * @param statusPointer 
         * pointer to the variable that will contain
         * the device's status
         * @return Execution 
         */
        Execution GetStatus(int* statusPointer);

        /**
         * @brief Sets the status of the device.
         * Potential statuses are explained in the
         * status enum.
         * @param newStatus
         * new Status to set the device as. 
         * @return Execution 
         */
        Execution SetStatus(int newStatus);
        //////////////////////////////////////////////

        /**
         * @brief Set the Error Message of the device
         * that other BFIO terminals can get access to.
         * 
         * @param NewErrorMessage 
         * @return Execution 
         */
        Execution SetErrorMessage(std::string NewErrorMessage);

        /**
         * @brief Set the Error Message of the device
         * that other BFIO terminals can get access to.
         * 
         * @param NewErrorMessage 
         * @return Execution 
         */
        Execution SetErrorMessage(const char* NewErrorMessage);
 };

#endif