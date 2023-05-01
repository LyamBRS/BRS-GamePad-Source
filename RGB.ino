/*
    ############    ############     ##########
    ############    ############     ##########
              ##              ##   ## 
    ####    ##      ####    ##     ############
    ####    ##      ####    ##     ############
              ##              ##             ##
    ############    ####      ##   ##########
    ############    ####      ##   ##########

    Title: RGB.c
    Author: Lyam
*/

#include "Globals.h"
#include <Adafruit_NeoPixel.h>
#include <math.h>

/**
 * @brief Basic lerp function
 * for color changes fades to avoid
 * sudden and abrupt changes in light
 * colors.
 * @param a 
 * @param b 
 * @param t 
 * @return double 
 */
double lerp(double a, double b, double t) {
  double result = a * (1 - t) + b * t;
  result = abs(result);
  return result;
}
/////////////////////////////////////////////////////////////////////////////
/**
 * Empty constructor
*/
RGB::RGB()
{

}

/**
 * @brief Construct a new RGB object
 * 
 * @param pinRGB 
 * GPIO pin that will be used for the LED.
 */
RGB::RGB(int pinRGB)
{
    currentRed = 0;
    currentGreen = 0;
    currentBlue = 0;
    forcedTimer = 0;
    forcedRed = 0;
    forcedGreen = 0;
    forcedBlue = 0;
    currentTick = 0;
    animationDuration = 10000;
    colorMode = 0;
    built = true;
    status = Status::Available;

    // Starting LED indicators
    Serial.println("WS2812.begin();");
    WS2812.begin();
    Serial.println("WS2812.show();");
    WS2812.show();
}
/////////////////////////////////////////////////////////////////////////////
/**
 * @brief Set the static color for the RGB LED.
 * 
 * @param red 0 to 255
 * @param green 0 to 255
 * @param blue 0 to 255
 * @return Execution 
 */
Execution RGB::SetColors(double red, double green, double blue)
{
    if(wantedRed != red ||
        wantedGreen != green ||
        wantedBlue != blue)
        {
          if(red <= 255 && green <= 255 && blue <= 255 && red >= 0 && green >= 0 && blue >= 0)
          {
            wantedRed = red;
            wantedGreen = green;
            wantedBlue = blue;
            // Serial.println("RGB -> SetColors: New colors defined");
            return Execution::Passed;
          }
          else
          {
            return Execution::Failed;
          }
        }
    else
    {
        return Execution::Unecessary;
    }
}
/**
 * @brief Set the Mode of the RGB animation
 * 
 * @param mode 
 *  - 0: static
 *  - 1: pulsed
 *  - 2: RGB cycle
 * @return Execution 
 */
Execution RGB::SetMode(unsigned char mode)
{
    if(colorMode == mode)
    {
        return Execution::Unecessary;
    }
    else
    {
        if(mode < 4)
        {
            // Serial.println("SetMode -> SUCCESS");
            colorMode = mode;
            return Execution::Passed;
        }
        else
        {
            return Execution::Failed;
        }
    }
}
/**
 * @brief Set the animated RGB properties
 * 
 * @param newCycleIntensity 
 * Light intensity applied when the
 * animationMode is cycling through
 * RGB colors. Value ranges from 0 to
 * 255.
 * @param newAnimationDuration
 * The duration in milliseconds of the
 * animations. Note that this impacts
 * lerps in static mode aswell.
 * @param sinExponent
 * The exponent given to the sinwave
 * responsible for cycles and pulses.
 * Keep it a multiplier of 2.
 * The bigger, the shorter the pulses.
 * @return Execution 
 */
Execution RGB::SetAnimations(unsigned char newCycleIntensity, unsigned int newAnimationDuration, unsigned char newSinExponent)
{
    if(newCycleIntensity != intensity ||
      animationDuration != newAnimationDuration ||
      newSinExponent != pulseExponent)
      {
          intensity = newCycleIntensity;
          animationDuration = newAnimationDuration;
          pulseExponent = newSinExponent;
          return Execution::Passed;
      }
      else
      {
        return Execution::Unecessary;
      }
}

Execution RGB::SetErrorMode(unsigned char burstCount, double burstPeriod, unsigned int messageDuration)
{
    animationDuration = messageDuration;
    _wantedBurstCount = burstCount;
    _burstPeriodCount = 0;
    _burstDuration = burstPeriod;

    SetMode(3);
    return Execution::Passed;
}
/////////////////////////////////////////////////////////////////////////////
/**
 * @brief returns the currently animated red color.
 * @param pulsedRed 
 * @return Execution 
 */
Execution RGB::GetCycledRed(double* pulsedRed)
{
    double temporary = 0;
    double ratio = (currentTick)/((double)(animationDuration));
    ratio = ratio * 6.28;

    if(colorMode != 0)
    {
        if(colorMode == 1) // PULSE
        {
            temporary = (sin(ratio));
            temporary = (pow(temporary, ((double)(pulseExponent))) * wantedRed);
        }
        else // CYCLE
        {
            temporary = (sin(ratio));
            temporary = (pow(temporary, ((double)(pulseExponent))) * ((double)(intensity)));
        }

        *pulsedRed = temporary;
        return Execution::Passed;
    }
    else
    {
        return Execution::Bypassed;
    }
}
/**
 * @brief returns the currently animated green color.
 * @param pulsedGreen 
 * @return Execution 
 */
Execution RGB::GetCycledGreen(double* pulsedGreen)
{
    double temporary = 0;
    double ratio = (currentTick)/((double)(animationDuration));
    ratio = ratio * 6.28;

    if(colorMode != 0)
    {
        if(colorMode == 1) // PULSE
        {   
            temporary = (sin(ratio));
            temporary = (pow(temporary, ((double)(pulseExponent))) * wantedGreen);
        }
        else // CYCLE
        {
            temporary = (sin(ratio + 2.09));
            temporary = (pow(temporary, ((double)(pulseExponent))) * ((double)(intensity)));
        }

        *pulsedGreen = temporary;

        return Execution::Passed;
    }
    else
    {
        return Execution::Bypassed;
    }
}
/**
 * @brief returns the currently animated blue color.
 * @param pulsedBlue 
 * @return Execution 
 */
Execution RGB::GetCycledBlue(double* pulsedBlue)
{
    unsigned char newColor = 0;
    double temporary = 0;
    double ratio = (currentTick)/((double)(animationDuration));
    ratio = ratio * 6.28;

    if(colorMode != 0)
    {
        if(colorMode == 1) // PULSE
        {
            temporary = (sin(ratio));
            temporary = (pow(temporary, ((double)(pulseExponent))) * wantedBlue);
        }
        else // CYCLE
        {
            temporary = (sin(ratio - 2.09));
            temporary = (pow(temporary, ((double)(pulseExponent))) * ((double)(intensity)));
        }

        *pulsedBlue = temporary;
        return Execution::Passed;
    }
    else
    {
        return Execution::Bypassed;
    }
}
/////////////////////////////////////////////////////////////////////////////
/**
 * @brief Actually updates the colors.
 * This is a private function. You need to call
 * the update function periodically to set the
 * color of the RGB strip. Use SetColor to define
 * a color. 
 * @attention 
 * Do not attempt to call this function
 * manually.
 * @return Execution 
 */
Execution RGB::UpdateColors()
{

  if(colorMode == 0)
  {
    if(wantedRed != oldRed ||
        wantedGreen != oldGreen ||
        wantedBlue != oldBlue)
    {
        oldRed  = lerp(oldRed,   wantedRed, 0.01);
        oldGreen  = lerp(oldGreen, wantedGreen, 0.01);
        oldBlue  = lerp(oldBlue,  wantedBlue, 0.01);

        // currentRed = oldRed;
        // currentGreen = oldGreen;
        // currentBlue = oldBlue;

        WS2812.setPixelColor(0, WS2812.Color((unsigned char)oldRed, (unsigned char)oldGreen, (unsigned char)oldBlue));
        WS2812.show();

        return Execution::Passed;
    }
    else
    {
        return Execution::Unecessary;
    }
    return Execution::Crashed;
  }
  else if(colorMode < 3)
  {
    if(oldRed != currentRed ||
        oldGreen != currentGreen ||
        oldBlue != currentBlue)
    {
        oldRed  = lerp(oldRed,   currentRed, 0.01);
        oldGreen  = lerp(oldGreen, currentGreen, 0.01);
        oldBlue  = lerp(oldBlue,  currentBlue, 0.01);

        WS2812.setPixelColor(0, WS2812.Color((unsigned char)oldRed, (unsigned char)oldGreen, (unsigned char)oldBlue));
        WS2812.show();
        return Execution::Passed; 
    }
    else
    {
      return Execution::Unecessary;
    }
    return Execution::Crashed;
  }
  else
  {
    if(errorLightState)
    {
        WS2812.setPixelColor(0, WS2812.Color(wantedRed, wantedBlue, wantedGreen));
    }
    else
    {
        WS2812.setPixelColor(0, WS2812.Color(0, 0, 0));
    }
        WS2812.show();
        return Execution::Passed;  
  }

}
/**
 * @brief Timebase function.
 * Needs to be periodically called in a callback.
 * @return Execution 
 */
Execution RGB::Update()
{
    // Increasing tick until speed is reached
    currentTick += CLOCK_PERIOD_MS;
    if(currentTick > ((double)(animationDuration)))
    {
      currentTick = 0;
      _burstPeriodCount = 0;
      errorLightState = false;
      errorTick = 0;
    }

    if(colorMode == 3)
    {
        errorTick++;
        if(errorTick >= _burstDuration)
        {
            errorTick = 0;
            _burstPeriodCount = _burstPeriodCount + 1;

            if(_burstPeriodCount <= (_wantedBurstCount*2))
            {
              errorLightState = !errorLightState;
            }
            else
            {
                errorLightState = false;
            }
        }
    }

    // Handle pulses and cycles + new colors
    switch(colorMode)
    {
        case(0): // STATIC
            return UpdateColors();
            break;
        case(1): // PULSED / Cycled
        case(2):

            GetCycledRed(&currentRed);
            GetCycledGreen(&currentGreen);
            GetCycledBlue(&currentBlue);

            return UpdateColors();
            break;
        case(3):
            return UpdateColors();
    }
    return Execution::Failed;
}
