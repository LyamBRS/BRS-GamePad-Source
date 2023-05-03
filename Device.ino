/**
 * @file Device.ino
 * @author Lyam (Lyam@gmail.com)
 * @brief This file contains the core code
 * of the cDevice class.
 * @version 0.1
 * @date 2023-04-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
/////////////////////////////////////////////////////////////////////////////
#include "Globals.h"
/////////////////////////////////////////////////////////////////////////////
cDevice::cDevice()
{
    _status = Status::Booting;
    built = true;
}

Execution cDevice::GetStatus(int* statusPointer)
{
    *statusPointer = _status;

    if(*statusPointer != _status){
        return Execution::Crashed;
    }
    else{
        return Execution::Passed;
    }

  return Execution::Bypassed;
}

Execution cDevice::SetStatus(int newStatus)
{
    switch(newStatus)
    {
        case(Status::Available):
            Rgb.SetColors(255,255,255);
            Rgb.SetMode(2);
            Rgb.SetAnimations(255, 10000, 4);
            return Execution::Passed;
        break;

        case(Status::Booting):
            Rgb.SetColors(255,255,255);
            Rgb.SetMode(0);
            return Execution::Passed;
        break;

        case(Status::Busy):
            Rgb.SetColors(255,255,0);
            Rgb.SetMode(0);
            return Execution::Passed;
        break;

        case(Status::Clueless):
            Rgb.SetColors(255,64,0);
            Rgb.SetMode(0);
            return Execution::Passed;
        break;
    
        case(Status::CommunicationError):
            Rgb.SetColors(255,0,0);
            Rgb.SetErrorMode(2, 200, 5000);
            return Execution::Passed;
        break;

        case(Status::CompatibilityError):
            Rgb.SetColors(255,0,0);
            Rgb.SetErrorMode(3, 200, 5000);
            return Execution::Passed;
        break;

        case(Status::Crashing):
            Rgb.SetColors(255,0,0);
            Rgb.SetMode(1);
            Rgb.SetAnimations(255, 250, 10);
            return Execution::Passed;
        break;
    
        case(Status::Debugging):
            Rgb.SetColors(0,128,255);
            Rgb.SetMode(1);
            Rgb.SetAnimations(255, 10000, 2);
            return Execution::Passed;
        break;

        case(Status::Handshake):
            Rgb.SetColors(255,255,0);
            Rgb.SetMode(1);
            Rgb.SetAnimations(255, 1000, 32);
            return Execution::Passed;
        break;

        case(Status::HardwareError):
            Rgb.SetColors(255,0,0);
            Rgb.SetErrorMode(1, 200, 5000);
            return Execution::Passed;
        break;

        case(Status::NoBattery):
            Rgb.SetColors(255,0,0);
            Rgb.SetMode(1);
            Rgb.SetAnimations(255, 500, 2);
            return Execution::Passed;
        break;

        case(Status::Shutdown):
            Rgb.SetColors(0,0,0);
            Rgb.SetMode(0);
            return Execution::Passed;
        break;

        case(Status::SoftwareError):
            Rgb.SetColors(255,0,0);
            Rgb.SetErrorMode(4, 200, 5000);
            return Execution::Passed;
        break;

        default:
          return Execution::Failed;
        break;
    }
  return Execution::Bypassed;
}

/**
 * @brief Set the Error Message of the device
 * that other BFIO terminals can get access to.
 * 
 * @param NewErrorMessage 
 * @return Execution 
 */
Execution cDevice::SetErrorMessage(std::string NewErrorMessage)
{
  return Execution::Bypassed;
}

/**
 * @brief Set the Error Message of the device
 * that other BFIO terminals can get access to.
 * 
 * @param NewErrorMessage 
 * @return Execution 
 */
Execution cDevice::SetErrorMessage(const char* NewErrorMessage)
{
  return Execution::Bypassed;
}