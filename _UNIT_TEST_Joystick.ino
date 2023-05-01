/**
 * @file _UNIT_TEST_Joystick.h
 * @author Lyam (lyam.brs@gmail.com)
 * @brief This file contains the declaration
 * of the method that allows a quick and
 * simple unit test to the cData class
 * defined in Data.h
 * @version 0.1
 * @date 2023-05-01
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




#include "Globals.h"

#pragma region Functions
/**
 * @brief Unit test function that tests every
 * aspects of CalculateJoystickAxisDeadzone.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_CalculateJoystickAxisDeadzone()
{
  return Execution::Bypassed;
}
/**
 * @brief Unit test function that tests every
 * aspects of CalculateJoystickAxisTrim.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_CalculateJoystickAxisTrim()
{
  return Execution::Bypassed;
}
#pragma endregion

#pragma region Methods
/**
 * @brief Unit test function that tests the
 * Get and the Set methods for the Joystick's
 * modes.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetSetMode()
{
    TestStart("GetSetMode");
    unsigned char resultedMode = 255;
    Execution result;

    #pragma region -GetMode pointer-
    #pragma region LeftJoystick
    result = LeftJoystick.GetMode(&resultedMode);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unepexted execution results when left joystick's GetMode was called.");
        return Execution::Failed;
    }
    if(resultedMode == 255)
    {
        TestFailed("Pointer not set by Leftjoystick.GetMode()");
    }
    resultedMode = 255;
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.GetMode(&resultedMode);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unepexted execution results when RightJoystick's GetMode was called.");
        return Execution::Failed;
    }
    if(resultedMode == 255)
    {
        TestFailed("Pointer not set by RightJoystick.GetMode()");
    }
    resultedMode = 255;
    #pragma endregion
    #pragma endregion

    #pragma region -SetMode then GetMode-
    #pragma region LeftJoystick
    result = LeftJoystick.SetMode(1);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unepexted execution results when LeftJoystick's SetMode was called. (1)");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetMode(1);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unepexted execution results when RightJoystick's SetMode was called. (1)");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    #pragma region -SetMode Unecessary-
    #pragma region LeftJoystick
    result = LeftJoystick.SetMode(1);
    TestStepDone();
    if(result != Execution::Unecessary)
    {
        TestFailed("LeftJoystick did not return unecessary execution when SetMode called multiple times with the same value.");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetMode(1);
    TestStepDone();
    if(result != Execution::Unecessary)
    {
        TestFailed("RightJoystick did not return unecessary execution when SetMode called multiple times with the same value.");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion
    
    #pragma region -Incorrect mode to SetMode-
    #pragma region LeftJoystick
    result = LeftJoystick.SetMode(3);
    TestStepDone();
    if(result != Execution::Failed)
    {
        TestFailed("Unexpected execution results when LeftJoystick's SetMode was called with incorrect values");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetMode(3);
    TestStepDone();
    if(result != Execution::Failed)
    {
        TestFailed("Unexpected execution results when RightJoystick's SetMode was called with incorrect values");        
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Unit test function that tests the
 * Get and the Set methods for the Joystick's
 * DeadZone_X.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetSetDeadZone_X()
{
    TestStart("GetSetDeadZone_X");
    Execution result;
    signed char wantedDeadzone = 0;
    signed char resultedDeadzone = 1;

    #pragma region -Positive values given-
    #pragma region LeftJoystick
    for(wantedDeadzone=1; wantedDeadzone < _JOY_MAX_VAL; wantedDeadzone++)
    {
        result = LeftJoystick.SetDeadZone_X(wantedDeadzone);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result returned by LeftJoystick's SetDeadZone_X when positive values given.");
            return Execution::Failed;
        }

        result = LeftJoystick.GetDeadZone_X(&resultedDeadzone);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result returned by LeftJoystick's GetDeadZone_X.");
            return Execution::Failed;
        }

        if(wantedDeadzone != resultedDeadzone)
        {
            TestFailed("LeftJoystick's Get method did not return what was placed in Set method. (Positives)");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region RightJoystick
    for(wantedDeadzone=1; wantedDeadzone < _JOY_MAX_VAL; wantedDeadzone++)
    {
        result = RightJoystick.SetDeadZone_X(wantedDeadzone);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result returned by RightJoystick's SetDeadZone_X when positive values given.");
            return Execution::Failed;
        }

        result = RightJoystick.GetDeadZone_X(&resultedDeadzone);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result returned by RightJoystick's GetDeadZone_X.");
            return Execution::Failed;
        }

        if(wantedDeadzone != resultedDeadzone)
        {
            TestFailed("RightJoystick's Get method did not return what was placed in Set method. (Positives)");
            return Execution::Failed;
        }
    }
    #pragma endregion
    #pragma endregion

    #pragma region -Negative values given-
    #pragma region LeftJoystick
    for(wantedDeadzone=-126; wantedDeadzone != 0; wantedDeadzone++)
    {
        result = LeftJoystick.SetDeadZone_X(wantedDeadzone);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result returned by LeftJoystick's SetDeadZone_X when positive values given.");
            return Execution::Failed;
        }

        result = LeftJoystick.GetDeadZone_X(&resultedDeadzone);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result returned by LeftJoystick's GetDeadZone_X.");
            return Execution::Failed;
        }

        // Serial.println(std::to_string(wantedDeadzone).c_str());
        // Serial.println(std::to_string(resultedDeadzone).c_str());

        if(wantedDeadzone != -resultedDeadzone)
        {
            TestFailed("LeftJoystick's Get method did not return what was placed in Set method. (Negatives)");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region RightJoystick
    for(wantedDeadzone=-126; wantedDeadzone != 0; wantedDeadzone++)
    {
        result = RightJoystick.SetDeadZone_X(wantedDeadzone);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result returned by RightJoystick's SetDeadZone_X when negative values given.");
            return Execution::Failed;
        }

        result = RightJoystick.GetDeadZone_X(&resultedDeadzone);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result returned by RightJoystick's GetDeadZone_X.");
            return Execution::Failed;
        }

        if(wantedDeadzone != -resultedDeadzone)
        {
            Serial.println(wantedDeadzone);
            Serial.println(resultedDeadzone);
            TestFailed("RightJoystick's Get method did not return what was placed in Set method.(Negatives)");
            return Execution::Failed;
        }
    }
    #pragma endregion
    #pragma endregion
    
    #pragma region -Unecessary returns-

    #pragma region LeftJoystick
    result = LeftJoystick.SetDeadZone_X(0);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned by LeftJoystick's SetDeadZone_X when set to 0");
    }

    result = LeftJoystick.SetDeadZone_X(0);
    TestStepDone();
    if(result != Execution::Unecessary)
    {
        TestFailed("LeftJoystick's SetDeadZone_X did not return Unecessary when called multiple time with the same value");
    }  
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetDeadZone_X(0);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned by RightJoystick's SetDeadZone_X when set to 0");
    }

    result = RightJoystick.SetDeadZone_X(0);
    TestStepDone();
    if(result != Execution::Unecessary)
    {
        TestFailed("RightJoystick's SetDeadZone_X did not return Unecessary when called multiple time with the same value");
    } 
    #pragma endregion

    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Unit test function that tests the
 * Get and the Set methods for the Joystick's
 * DeadZone_Y.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetSetDeadZone_Y()
{
    TestStart("GetSetDeadZone_Y");
    Execution result;
    signed char wantedDeadzone = 0;
    signed char resultedDeadzone = 1;

    #pragma region -Positive values given-
    #pragma region LeftJoystick
    for(wantedDeadzone=1; wantedDeadzone < _JOY_MAX_VAL; wantedDeadzone++)
    {
        result = LeftJoystick.SetDeadZone_Y(wantedDeadzone);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result returned by LeftJoystick's SetDeadZone_Y when positive values given.");
            return Execution::Failed;
        }

        result = LeftJoystick.GetDeadZone_Y(&resultedDeadzone);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result returned by LeftJoystick's GetDeadZone_Y.");
            return Execution::Failed;
        }

        if(wantedDeadzone != resultedDeadzone)
        {
            TestFailed("LeftJoystick's Get method did not return what was placed in Set method.");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region RightJoystick
    for(wantedDeadzone=1; wantedDeadzone < _JOY_MAX_VAL; wantedDeadzone++)
    {
        result = RightJoystick.SetDeadZone_Y(wantedDeadzone);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result returned by RightJoystick's SetDeadZone_Y when positive values given.");
            return Execution::Failed;
        }

        result = RightJoystick.GetDeadZone_Y(&resultedDeadzone);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result returned by RightJoystick's GetDeadZone_Y.");
            return Execution::Failed;
        }

        if(wantedDeadzone != resultedDeadzone)
        {
            TestFailed("RightJoystick's Get method did not return what was placed in Set method.");
            return Execution::Failed;
        }
    }
    #pragma endregion
    #pragma endregion

    #pragma region -Negative values given-
    #pragma region LeftJoystick
    for(wantedDeadzone=0; wantedDeadzone > _JOY_MIN_VAL; wantedDeadzone--)
    {
        result = LeftJoystick.SetDeadZone_Y(wantedDeadzone);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result returned by LeftJoystick's SetDeadZone_Y when positive values given.");
            return Execution::Failed;
        }

        result = LeftJoystick.GetDeadZone_Y(&resultedDeadzone);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result returned by LeftJoystick's GetDeadZone_Y.");
            return Execution::Failed;
        }

        if(wantedDeadzone != -resultedDeadzone)
        {
            TestFailed("LeftJoystick's Get method did not return what was placed in Set method.");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region RightJoystick
    for(wantedDeadzone=0; wantedDeadzone > _JOY_MIN_VAL; wantedDeadzone--)
    {
        result = RightJoystick.SetDeadZone_Y(wantedDeadzone);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result returned by RightJoystick's SetDeadZone_Y when negative values given.");
            return Execution::Failed;
        }

        result = RightJoystick.GetDeadZone_Y(&resultedDeadzone);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result returned by RightJoystick's GetDeadZone_Y.");
            return Execution::Failed;
        }

        if(wantedDeadzone != -resultedDeadzone)
        {
            TestFailed("RightJoystick's Get method did not return what was placed in Set method.");
            return Execution::Failed;
        }
    }
    #pragma endregion
    #pragma endregion
    
    #pragma region -Unecessary returns-

    #pragma region LeftJoystick
    result = LeftJoystick.SetDeadZone_Y(0);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned by LeftJoystick's SetDeadZone_Y when set to 0");
    }

    result = LeftJoystick.SetDeadZone_Y(0);
    TestStepDone();
    if(result != Execution::Unecessary)
    {
        TestFailed("LeftJoystick's SetDeadZone_Y did not return Unecessary when called multiple time with the same value");
    }  
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetDeadZone_Y(0);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned by RightJoystick's SetDeadZone_Y when set to 0");
    }

    result = RightJoystick.SetDeadZone_Y(0);
    TestStepDone();
    if(result != Execution::Unecessary)
    {
        TestFailed("RightJoystick's SetDeadZone_Y did not return Unecessary when called multiple time with the same value");
    } 
    #pragma endregion

    #pragma endregion
    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Unit test function that tests the
 * Get and the Set methods for the Joystick's
 * Trim_X.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetSetTrim_X()
{
    TestStart("GetSetTrim_X");
    Execution result;
    signed char wantedTrim = 0;
    signed char resultedTrim = 1;

    #pragma region -Entire spectrum of values-

    #pragma region LeftJoystick
    for(wantedTrim = _JOY_MIN_VAL; wantedTrim < _JOY_MAX_VAL; wantedTrim++)
    {
        result = LeftJoystick.SetTrim_X(wantedTrim);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result from LeftJoystick.SetTrim_X when testing entire range");
            return Execution::Failed;
        }

        result = LeftJoystick.GetTrim_X(&resultedTrim);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result from LeftJoystick.GetTrim_X when testing entire range");
            return Execution::Failed;
        }

        if(resultedTrim != wantedTrim)
        {
            TestFailed("Values placed in LeftJoystick.SetTrim_X were not the same gotten from LeftJoystick.GetTrim_X");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region RightJoystick
    for(wantedTrim = _JOY_MIN_VAL; wantedTrim < _JOY_MAX_VAL; wantedTrim++)
    {
        result = RightJoystick.SetTrim_X(wantedTrim);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result from RightJoystick.SetTrim_X when testing entire range");
            return Execution::Failed;
        }

        result = RightJoystick.GetTrim_X(&resultedTrim);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result from RightJoystick.GetTrim_X when testing entire range");
            return Execution::Failed;
        }

        if(resultedTrim != wantedTrim)
        {
            TestFailed("Values placed in RightJoystick.SetTrim_X were not the same gotten from RightJoystick.GetTrim_X");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma endregion

    #pragma region -Unecessary returns-

    #pragma region LeftJoystick
    result = LeftJoystick.SetTrim_X(0);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned by LeftJoystick.SetTrim_X when set to 0");
    }

    result = LeftJoystick.SetTrim_X(0);
    TestStepDone();
    if(result != Execution::Unecessary)
    {
        TestFailed("LeftJoystick.SetTrim_X did not return Unecessary when called multiple time with the same value");
    }  
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetTrim_X(0);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned by LeftJoystick.SetTrim_X when set to 0");
    }

    result = RightJoystick.SetTrim_X(0);
    TestStepDone();
    if(result != Execution::Unecessary)
    {
        TestFailed("LeftJoystick.SetTrim_X did not return Unecessary when called multiple time with the same value");
    } 
    #pragma endregion

    #pragma endregion

    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Unit test function that tests the
 * Get and the Set methods for the Joystick's
 * Trim_Y.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetSetTrim_Y()
{
    TestStart("GetSetTrim_Y");
    Execution result;
    signed char wantedTrim = 0;
    signed char resultedTrim = 1;

    #pragma region -Entire spectrum of values-

    #pragma region LeftJoystick
    for(wantedTrim = _JOY_MIN_VAL; wantedTrim < _JOY_MAX_VAL; wantedTrim++)
    {
        result = LeftJoystick.SetTrim_Y(wantedTrim);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result from LeftJoystick.SetTrim_Y when testing entire range");
            return Execution::Failed;
        }

        result = LeftJoystick.GetTrim_Y(&resultedTrim);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result from LeftJoystick.GetTrim_Y when testing entire range");
            return Execution::Failed;
        }

        if(resultedTrim != wantedTrim)
        {
            TestFailed("Values placed in LeftJoystick.SetTrim_Y were not the same gotten from LeftJoystick.GetTrim_Y");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma region RightJoystick
    for(wantedTrim = _JOY_MIN_VAL; wantedTrim < _JOY_MAX_VAL; wantedTrim++)
    {
        result = RightJoystick.SetTrim_Y(wantedTrim);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result from RightJoystick.SetTrim_Y when testing entire range");
            return Execution::Failed;
        }

        result = RightJoystick.GetTrim_Y(&resultedTrim);
        TestStepDone();
        if(result != Execution::Passed)
        {
            TestFailed("Unexpected execution result from RightJoystick.GetTrim_Y when testing entire range");
            return Execution::Failed;
        }

        if(resultedTrim != wantedTrim)
        {
            TestFailed("Values placed in RightJoystick.SetTrim_Y were not the same gotten from RightJoystick.GetTrim_Y");
            return Execution::Failed;
        }
    }
    #pragma endregion

    #pragma endregion

    #pragma region -Unecessary returns-

    #pragma region LeftJoystick
    result = LeftJoystick.SetTrim_Y(0);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned by LeftJoystick.SetTrim_Y when set to 0");
    }

    result = LeftJoystick.SetTrim_Y(0);
    TestStepDone();
    if(result != Execution::Unecessary)
    {
        TestFailed("LeftJoystick.SetTrim_Y did not return Unecessary when called multiple time with the same value");
    }  
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetTrim_Y(0);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned by LeftJoystick.SetTrim_Y when set to 0");
    }

    result = RightJoystick.SetTrim_Y(0);
    TestStepDone();
    if(result != Execution::Unecessary)
    {
        TestFailed("LeftJoystick.SetTrim_Y did not return Unecessary when called multiple time with the same value");
    } 
    #pragma endregion

    #pragma endregion

    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Unit test function that tests the
 * Get methods for the Joystick's
 * CurrentAxis_X.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetCurrentAxis_X()
{
    TestStart("GetCurrentAxis_X");
    Execution result;
    signed char resultedAxis = 1;

    #pragma region -Setting modes to 0-
    #pragma region LeftJoystick
    result = LeftJoystick.SetMode(0);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling LeftJoystick.SetMode(0);");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetMode(0);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling RightJoystick.SetMode(0);");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    #pragma region -Reading default axis value-
    #pragma region LeftJoystick
    result = LeftJoystick.GetCurrentAxis_X(&resultedAxis);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned when calling: LeftJoystick.GetCurrentAxis_X(&resultedAxis)");
        return Execution::Failed;
    }
    if(resultedAxis != 0)
    {
        TestFailed("Unexpected default value returned when calling: LeftJoystick.GetCurrentAxis_X(&resultedAxis). Value is not 0");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.GetCurrentAxis_X(&resultedAxis);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned when calling: RightJoystick.GetCurrentAxis_X(&resultedAxis)");
        return Execution::Failed;
    }
    if(resultedAxis != 0)
    {
        TestFailed("Unexpected default value returned when calling: RightJoystick.GetCurrentAxis_X(&resultedAxis). Value is not 0");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    #pragma region -Setting modes to 1-
    #pragma region LeftJoystick
    result = LeftJoystick.SetMode(1);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling LeftJoystick.SetMode(1);");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetMode(1);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling RightJoystick.SetMode(1);");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    #pragma region -Reading mode 1 axis value-
    #pragma region LeftJoystick
    result = LeftJoystick.GetCurrentAxis_X(&resultedAxis);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned when calling: LeftJoystick.GetCurrentAxis_X(&resultedAxis)");
        return Execution::Failed;
    }
    if(resultedAxis != 0)
    {
        TestFailed("Unexpected default value returned when calling: LeftJoystick.GetCurrentAxis_X(&resultedAxis). Value is not 0");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.GetCurrentAxis_X(&resultedAxis);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned when calling: RightJoystick.GetCurrentAxis_X(&resultedAxis)");
        return Execution::Failed;
    }
    if(resultedAxis != 0)
    {
        TestFailed("Unexpected default value returned when calling: RightJoystick.GetCurrentAxis_X(&resultedAxis). Value is not 0");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    #pragma region -Setting modes to 0-
    #pragma region LeftJoystick
    result = LeftJoystick.SetMode(0);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling LeftJoystick.SetMode(0);");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetMode(0);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling RightJoystick.SetMode(0);");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Unit test function that tests the
 * Get methods for the Joystick's
 * CurrentAxis_Y.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetCurrentAxis_Y()
{
    TestStart("GetCurrentAxis_Y");
    Execution result;
    signed char resultedAxis = 1;

    #pragma region -Setting modes to 0-
    #pragma region LeftJoystick
    result = LeftJoystick.SetMode(0);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling LeftJoystick.SetMode(0);");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetMode(0);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling RightJoystick.SetMode(0);");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    #pragma region -Reading default axis value-
    #pragma region LeftJoystick
    result = LeftJoystick.GetCurrentAxis_Y(&resultedAxis);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned when calling: LeftJoystick.GetCurrentAxis_Y(&resultedAxis)");
        return Execution::Failed;
    }
    if(resultedAxis != 0)
    {
        TestFailed("Unexpected default value returned when calling: LeftJoystick.GetCurrentAxis_Y(&resultedAxis). Value is not 0");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.GetCurrentAxis_Y(&resultedAxis);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned when calling: RightJoystick.GetCurrentAxis_Y(&resultedAxis)");
        return Execution::Failed;
    }
    if(resultedAxis != 0)
    {
        TestFailed("Unexpected default value returned when calling: RightJoystick.GetCurrentAxis_Y(&resultedAxis). Value is not 0");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    #pragma region -Setting modes to 1-
    #pragma region LeftJoystick
    result = LeftJoystick.SetMode(1);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling LeftJoystick.SetMode(1);");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetMode(1);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling RightJoystick.SetMode(1);");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    #pragma region -Reading mode 1 axis value-
    #pragma region LeftJoystick
    result = LeftJoystick.GetCurrentAxis_Y(&resultedAxis);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned when calling: LeftJoystick.GetCurrentAxis_Y(&resultedAxis)");
        return Execution::Failed;
    }
    if(resultedAxis != 0)
    {
        TestFailed("Unexpected default value returned when calling: LeftJoystick.GetCurrentAxis_Y(&resultedAxis). Value is not 0");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.GetCurrentAxis_Y(&resultedAxis);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned when calling: RightJoystick.GetCurrentAxis_Y(&resultedAxis)");
        return Execution::Failed;
    }
    if(resultedAxis != 0)
    {
        TestFailed("Unexpected default value returned when calling: RightJoystick.GetCurrentAxis_Y(&resultedAxis). Value is not 0");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    #pragma region -Setting modes to 0-
    #pragma region LeftJoystick
    result = LeftJoystick.SetMode(0);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling LeftJoystick.SetMode(0);");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetMode(0);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling RightJoystick.SetMode(0);");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Unit test function that tests the
 * Get method of the Joystick's CurrentSwitch.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetCurrentSwitch()
{
    TestStart("GetCurrentSwitch");
    Execution result;
    bool resultedButton = 1;

    #pragma region -Setting modes to 0-
    #pragma region LeftJoystick
    result = LeftJoystick.SetMode(0);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling LeftJoystick.SetMode(0);");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetMode(0);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling RightJoystick.SetMode(0);");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    #pragma region -Reading default button value-
    #pragma region LeftJoystick
    result = LeftJoystick.GetCurrentSwitch(&resultedButton);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned when calling: LeftJoystick.GetCurrentSwitch(&resultedButton)");
        return Execution::Failed;
    }
    if(resultedButton != 0)
    {
        TestFailed("Unexpected default value returned when calling: LeftJoystick.GetCurrentSwitch(&resultedButton). Value is not 0");
        return Execution::Failed;
    }
    resultedButton = 1;
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.GetCurrentSwitch(&resultedButton);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned when calling: RightJoystick.GetCurrentSwitch(&resultedButton)");
        return Execution::Failed;
    }
    if(resultedButton != 0)
    {
        TestFailed("Unexpected default value returned when calling: RightJoystick.GetCurrentSwitch(&resultedButton). Value is not 0");
        return Execution::Failed;
    }
    resultedButton = 1;
    #pragma endregion
    #pragma endregion

    #pragma region -Setting modes to 1-
    #pragma region LeftJoystick
    result = LeftJoystick.SetMode(1);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling LeftJoystick.SetMode(1);");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetMode(1);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling RightJoystick.SetMode(1);");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    #pragma region -Reading mode 1 button value-
    #pragma region LeftJoystick
    result = LeftJoystick.GetCurrentSwitch(&resultedButton);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned when calling: LeftJoystick.GetCurrentSwitch(&resultedButton)");
        return Execution::Failed;
    }
    if(resultedButton != 0)
    {
        TestFailed("Unexpected default value returned when calling: LeftJoystick.GetCurrentSwitch(&resultedButton). Value is not 0");
        return Execution::Failed;
    }
    resultedButton = 1;
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.GetCurrentSwitch(&resultedButton);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned when calling: RightJoystick.GetCurrentSwitch(&resultedAxis)");
        return Execution::Failed;
    }
    if(resultedButton != 0)
    {
        TestFailed("Unexpected default value returned when calling: RightJoystick.GetCurrentSwitch(&resultedAxis). Value is not 0");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    #pragma region -Setting modes to 0-
    #pragma region LeftJoystick
    result = LeftJoystick.SetMode(0);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling LeftJoystick.SetMode(0);");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetMode(0);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling RightJoystick.SetMode(0);");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion


    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Unit test function that tests the
 * Get method of the Joystick's Everything.
 * This function is expected to behave like
 * GetCurrentSwitch and GetCurrentAxis
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * @return Execution 
 */
Execution TEST_JOYSTICK_GetEverything()
{
    TestStart("GetEverything");
    Execution result;
    signed char resultAxisX = 1;
    signed char resultAxisY = 1;
    bool resultButton = 1;

    #pragma region -Reading default values-

    #pragma region LeftJoystick
    result = LeftJoystick.GetEverything(&resultAxisX, &resultAxisY, &resultButton);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned from LeftJoystick.GetEverything");
        return Execution::Failed;
    }

    if(resultAxisX != 0)
    {
        TestFailed("resultAxisX was not set to default value by LeftJoystick.GetEverything");
        return Execution::Failed;
    }

    if(resultAxisY != 0)
    {
        TestFailed("resultAxisY was not set to default value by LeftJoystick.GetEverything");
        return Execution::Failed;
    }

    if(resultButton != 0)
    {
        TestFailed("resultButton was not set to default value by LeftJoystick.GetEverything");
        return Execution::Failed;
    }
    #pragma endregion

    resultAxisX = 1;
    resultAxisY = 1;
    resultButton = 1;

    #pragma region RightJoystick
    result = RightJoystick.GetEverything(&resultAxisX, &resultAxisY, &resultButton);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned from RightJoystick.GetEverything");
        return Execution::Failed;
    }

    if(resultAxisX != 0)
    {
        TestFailed("resultAxisX was not set to default value by RightJoystick.GetEverything");
        return Execution::Failed;
    }

    if(resultAxisY != 0)
    {
        TestFailed("resultAxisY was not set to default value by RightJoystick.GetEverything");
        return Execution::Failed;
    }

    if(resultButton != 0)
    {
        TestFailed("resultButton was not set to default value by RightJoystick.GetEverything");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma endregion

    TestPassed();
    return Execution::Passed;
}

/**
 * @brief Unit test function that tests the
 * Update method of the Joystick's class.
 * 
 * It Tests if returned executions are what's
 * expected. It also tests that the correct
 * values are set in the pointers.
 * 
 * @attention
 * YOU MUST NOT TOUCH THE JOYSTICKS DURING
 * UNIT TESTS.
 * 
 * @return Execution 
 */
Execution TEST_JOYSTICK_Update()
{
    TestStart("Update");
    Execution result;

    signed char leftXAxis = 0;
    signed char leftYAxis = 0;
    signed char rightXAxis = 0;
    signed char rightYAxis = 0; 
    bool leftButton = 0;
    bool rightButton = 0;

    #pragma region -Setting modes to 0-
    #pragma region LeftJoystick
    result = LeftJoystick.SetMode(0);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling LeftJoystick.SetMode(0);");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetMode(0);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Failed returned when calling RightJoystick.SetMode(0);");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    #pragma region -Set Deadzone to 10-
    #pragma region LeftJoystick
    result = LeftJoystick.SetDeadZone_X(10);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution result from LeftJoystick.SetDeadzone_X");
    }

    result = LeftJoystick.SetDeadZone_Y(10);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution result from LeftJoystick.SetDeadzone_Y");
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.SetDeadZone_X(10);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution result from RightJoystick.SetDeadzone_X");
    }

    result = RightJoystick.SetDeadZone_Y(10);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution result from RightJoystick.SetDeadzone_Y");
    }
    #pragma endregion
    #pragma endregion

    #pragma region -Updating-
    #pragma region LeftJoystick
    result = LeftJoystick.Update();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected result returned from calling LeftJoystick.Update()");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.Update();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected result returned from calling RightJoystick.Update()");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma endregion

    #pragma region -GetEverything-
    #pragma region LeftJoystick
    result = LeftJoystick.GetEverything(&leftXAxis, &leftYAxis, &leftButton);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned from LeftJoystick.GetEverything");
    }
    #pragma endregion

    #pragma region RightJoystick
    result = RightJoystick.GetEverything(&rightXAxis, &rightYAxis, &rightButton);
    TestStepDone();
    if(result != Execution::Passed)
    {
        TestFailed("Unexpected execution returned from RightJoystick.GetEverything");
    }
    #pragma endregion
    #pragma endregion

    #pragma region -Compare Everything-
    #pragma region LeftJoystick
    if(leftXAxis != 0)
    {
        TestFailed("LeftJoystick's X axis returned value higher than 0");
        Serial.println(leftXAxis);
    }

    if(leftYAxis != 0)
    {
        TestFailed("LeftJoystick's Y axis returned value higher than 0");
        Serial.println(leftYAxis);
    }

    if(leftButton != 0)
    {
        TestFailed("LeftJoystick's button returned value higher than 0");
        Serial.println(leftButton);
    }
    #pragma endregion

    #pragma region RightJoystick
    if(rightXAxis != 0)
    {
        TestFailed("RightJoystick's X axis returned value higher than 0");
        Serial.println(rightXAxis);
    }

    if(rightYAxis != 0)
    {
        TestFailed("RightJoystick's Y axis returned value higher than 0");
        Serial.println(rightYAxis);
    }

    if(rightButton != 0)
    {
        TestFailed("RightJoystick's button returned value higher than 0");
        Serial.println(rightButton);
    }
    #pragma endregion
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}
#pragma endregion

/**
 * @brief Unit test function which returns
 * Execution::Passed if cJoystick can 
 * successfully be used to read and analyze
 * joysticks beahaviours
 * 
 * It will return Execution::Failed if any
 * function fails.
 * @return Execution 
 */
Execution cJoystick_LaunchTests()
{
    StartOfUnitTest("cJoystick");
    Execution result;

    result = TEST_JOYSTICK_GetSetMode();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_JOYSTICK_GetSetDeadZone_X();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_JOYSTICK_GetSetDeadZone_Y();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_JOYSTICK_GetSetTrim_X();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_JOYSTICK_GetSetTrim_Y();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_JOYSTICK_GetCurrentAxis_X();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_JOYSTICK_GetCurrentAxis_Y();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_JOYSTICK_GetCurrentSwitch();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_JOYSTICK_GetEverything();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_JOYSTICK_Update();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    UnitTestPassed();
    return Execution::Passed;
}
