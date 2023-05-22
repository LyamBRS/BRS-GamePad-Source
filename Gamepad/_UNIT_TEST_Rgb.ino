#include "_UNIT_TEST_Rgb.h"

/**
 * @brief Function that tests the integrity
 * of this RGB method. It tests that colors
 * are applied and limits return the correct
 * execution value.
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_SetColors()
{
    TestStart("SetColors");
    Execution result;

    #pragma region SetColors(0,0,0)
    result = Rgb.SetColors(0,0,0);
    TestStepDone();
    if(result == Execution::Passed || result == Execution::Unecessary)
    {
        if(Rgb.wantedBlue != 0){
            TestFailed("Blue color did not update to (0)");
            return Execution::Failed;
        }

        if(Rgb.wantedRed != 0){
            TestFailed("Red color did not update to (0)");
            return Execution::Failed;
        }

        if(Rgb.wantedGreen != 0){
            TestFailed("Green color did not update to (0)");
            return Execution::Failed;
        }
    }
    else
    {
        TestFailed("Incorrect execution returned with values of (0,0,0)");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region SetColors(255,255,255)
    result = Rgb.SetColors(255,255,255);
    TestStepDone();
    if(result == Execution::Passed)
    {
        if(Rgb.wantedBlue != 255){
            TestFailed("Blue color did not update to (255)");
            return Execution::Failed;
        }

        if(Rgb.wantedRed != 255){
            TestFailed("Red color did not update to (255)");
            return Execution::Failed;
        }

        if(Rgb.wantedGreen != 255){
            TestFailed("Green color did not update to (255)");
            return Execution::Failed;
        }
    }
    else
    {
        if(result == Execution::Unecessary)
        {
            TestFailed("Unecessary execution returned despite consecutive calls with different values.");
        }
        else
        {
            TestFailed("Incorrect execution returned with values of (0,0,0)");
        }
        return Execution::Failed;
    }
    #pragma endregion

   #pragma region SetColors(255,255,255)
    result = Rgb.SetColors(255,255,255);
    TestStepDone();
    if(result != Execution::Unecessary)
    {
        TestFailed("Unecessary execution not returned despite consecutive calls with the same values");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region SetColors(500,500,500)
    result = Rgb.SetColors(500,500,500);
    TestStepDone();
    if(result != Execution::Failed)
    {
        TestFailed("Incorrect execution returned when values passed were above 255");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region SetColors(-100,-100,-100)
    result = Rgb.SetColors(-100,-100,-100);
    TestStepDone();
    if(result != Execution::Failed)
    {
        TestFailed("Incorrect execution returned when values passed were below 0");
        return Execution::Failed;
    }
    #pragma endregion

    TestPassed();
    return Execution::Passed;
}
/**
 * @brief Function that tests the integrity
 * of this RGB method. It tests that modes
 * are applied and limits return the correct
 * execution value.
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_SetMode()
{
    TestStart("SetMode");
    Execution result;

    #pragma region SetMode(0)
    result = Rgb.SetMode(0);
    TestStepDone();
    if(result == Execution::Passed || result == Execution::Unecessary)
    {
    }
    else
    {
        TestFailed("Could not set mode to 0");
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region SetMode(1)
    result = Rgb.SetMode(1);
    TestStepDone();
    if(result != Execution::Passed)
    {
        if(result == Execution::Unecessary)
        {
            TestFailed("Unecessary execution returned despite consecutive calls with different values.");        
        }
        else
        {
            TestFailed("Could not set mode to 1");        
        }
        return Execution::Failed;
    }

    #pragma endregion
    #pragma region SetMode(2)
    result = Rgb.SetMode(2);
    TestStepDone();
    if(result != Execution::Passed)
    {
        if(result == Execution::Unecessary)
        {
            TestFailed("Unecessary execution returned despite consecutive calls with different values.");        
        }
        else
        {
            TestFailed("Could not set mode to 2");        
        }
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region SetMode(3)
    result = Rgb.SetMode(3);
    TestStepDone();
    if(result != Execution::Passed)
    {
        if(result == Execution::Unecessary)
        {
            TestFailed("Unecessary execution returned despite consecutive calls with different values.");        
        }
        else
        {
            TestFailed("Could not set mode to 3");        
        }
        return Execution::Failed;
    }
    #pragma endregion
    #pragma region SetMode(3)
    result = Rgb.SetMode(3);
    TestStepDone();
    if(result != Execution::Unecessary)
    {
        TestFailed("Unecessary execution not returned despite multiple calls with the same value.");
    }
    #pragma endregion
    #pragma region SetMode(4)
    result = Rgb.SetMode(4);
    TestStepDone();
    if(result != Execution::Failed)
    {
        TestFailed("Did not return failed execution despite inexisting mode sent (4)");
        return Execution::Failed;
    }
    return Execution::Passed;
    #pragma endregion
}
/**
 * @brief Function that tests the integrity
 * of this RGB method. It tests that animations
 * are applied and limits return the correct
 * execution value.
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_SetAnimations()
{
    TestStart("SetAnimations");
    Execution result;

    #pragma region SetAnimations(128, 4269, 60)
    result = Rgb.SetAnimations(128, 4269, 60);
    TestStepDone();
    if(result == Execution::Failed)
    {
        TestFailed("Could not set Animations to (128, 4269, 60)");
        return Execution::Failed;
    }
    else
    {
        if(Rgb.pulseExponent != 60){
            TestFailed("Pulse intensity did not update to 60");
            return Execution::Failed;
        }

        if(Rgb.animationDuration != 4269){
            TestFailed("Animation duration did not update to 4269");
            return Execution::Failed;
        }

        if(Rgb.intensity != 128){
            TestFailed("Intensity did not update to 128");
            return Execution::Failed;
        }

    }
    #pragma endregion

    #pragma region SetAnimations(128, 4269, 60)
    result = Rgb.SetAnimations(128, 4269, 60);
    TestStepDone();
    if(result != Execution::Unecessary)
    {
        TestFailed("Unecessary execution not returned despite consecutive calls with same parameters.");
        return Execution::Failed;
    }
    #pragma endregion
    TestPassed();
    return Execution::Passed;
}
/**
 * @brief Function that tests the integrity
 * of this RGB method. It tests that errors
 * are applied and limits return the correct
 * execution value.
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_SetErrorMode()
{
    TestStart("SetErrorMode");
    Execution result;

    #pragma region SetMode(0)
    result = Rgb.SetMode(0);
    TestStepDone();
    if(result == Execution::Passed || result == Execution::Unecessary)
    {
    }
    else
    {
        TestFailed("Could not set mode to 0");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region SetErrorMode(0, 200, 4000)
    result = Rgb.SetErrorMode(0, 200, 4000);
    TestStepDone();
    if(result == Execution::Passed || result == Execution::Unecessary)
    {
        if(Rgb.animationDuration != 4000)
        {
            TestFailed("Animation duration did not update to 4000");
            return Execution::Failed;
        }

        TestStepDone();
        if(Rgb.SetMode(3) != Execution::Unecessary)
        {
            TestFailed("Mode did not update to 3 when called.");
            return Execution::Failed;
        }
    }
    else
    {
        TestFailed("Could not set SetErrorMode to (0, 200, 4000)");
        return Execution::Failed;
    }
    #pragma endregion

    TestPassed();
    return Execution::Passed;
}
/**
 * @brief Function that tests the integrity
 * of this RGB method. It tests that the
 * correct value is returned depending on
 * modes and other animation factors
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_GetCycleRed()
{
    TestStart("GetCycleRed");
    return Execution::Bypassed;
}
/**
 * @brief Function that tests the integrity
 * of this RGB method. It tests that the
 * correct value is returned depending on
 * modes and other animation factors
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_GetCycleGreen()
{
    TestStart("GetCycleGreen");
    return Execution::Bypassed;
}
/**
 * @brief Function that tests the integrity
 * of this RGB method. It tests that the
 * correct value is returned depending on
 * modes and other animation factors
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_GetCycleBlue()
{
    TestStart("GetCycleBlue");
    return Execution::Bypassed;
}
/**
 * @brief Function that tests the integrity
 * of this RGB method. It verifies that
 * the colors are updated correctly.
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_UpdateColors()
{
    TestStart("UpdateColors");
    return Execution::Bypassed;
}
/**
 * @brief Function that tests the integrity
 * of this RGB method. It tests that updates
 * occures when it is called multiple times.
 * @return Execution::Passed if successful.
 */
Execution TEST_RGB_Update()
{
    TestStart("Update");
    Execution result;

    #pragma region Red
    result = Rgb.SetColors(255,0,0);
    TestStepDone();
    if(result != Execution::Passed){
        TestFailed("Failed to set color to red");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region Mode
    result = Rgb.SetMode(0);
    TestStepDone();
    if(result != Execution::Passed){
        TestFailed("Failed to set mode to static (0)");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region Update
    result = Rgb.Update();
    TestStepDone();
    if(result != Execution::Passed){
        TestFailed("Update function execution failed.");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region Delay
    for (int i=0; i<100; ++i)
    {
      Rgb.Update();
      delay(1);
    }
    TestStepDone();
    #pragma endregion

    #pragma region Green
    result = Rgb.SetColors(0,255,0);
    TestStepDone();
    if(result != Execution::Passed){
        TestFailed("Failed to set color to green.");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region Update
    result = Rgb.Update();
    TestStepDone();
    if(result != Execution::Passed){
        TestFailed("Update function execution failed.");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region Delay
    for (int i=0; i<100; ++i)
    {
      Rgb.Update();
      delay(1);
    }
    TestStepDone();
    #pragma endregion

    #pragma region Blue
    result = Rgb.SetColors(0,0,255);
    TestStepDone();
    if(result != Execution::Passed){
        TestFailed("Failed to set color to blue.");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region Update
    result = Rgb.Update();
    TestStepDone();
    if(result != Execution::Passed){
        TestFailed("Update function execution failed.");
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region Delay
    for (int i=0; i<100; ++i)
    {
      Rgb.Update();
      delay(1);
    }
    TestStepDone();
    #pragma endregion

    TestPassed();
    return Execution::Passed;
}
/**
 * @brief Unit test function which returns
 * Execution::Passed if RGB works
 * successfully for each methods it has.
 * 
 * It will return Execution::Failed if any
 * function fails to convert data and read
 * back the same exact values.
 * @return Execution 
 */
Execution RGB_LaunchTests()
{
    StartOfUnitTest("RGB class");
    Execution result;

    result = TEST_RGB_SetColors();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_RGB_SetMode();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_RGB_SetErrorMode();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_RGB_SetAnimations();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_RGB_GetCycleRed();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_RGB_GetCycleGreen();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_RGB_GetCycleBlue();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_RGB_Update();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    result = TEST_RGB_UpdateColors();
    if(result == Execution::Failed){
        UnitTestFailed();
        return Execution::Failed;
    }

    UnitTestPassed();
    return Execution::Passed;
}