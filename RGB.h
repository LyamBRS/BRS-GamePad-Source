/*
    ############    ############     ##########
    ############    ############     ##########
              ##              ##   ## 
    ####    ##      ####    ##     ############
    ####    ##      ####    ##     ############
              ##              ##             ##
    ############    ####      ##   ##########
    ############    ####      ##   ##########

    Title: RGB.h
    Author: Lyam
*/

#ifndef RGB_H
  #define RGB_H
//================================================================================================//
//	Include
//================================================================================================//
#include "Globals.h"
//================================================================================================//
//	Define
//================================================================================================//
  
class RGB
 {       
    private:
        /** @brief The status of this class. See status enum for possible values. */

        unsigned int forcedTimer = 0;
        double forcedRed = 0;
        double forcedGreen = 0;
        double forcedBlue = 0;

        /**
         * @brief The color mode that
         * RGB lights will follow.
         * 
         *  - 0: static
         *  - 1: pulsed
         *  - 2: RGB cycle
         *  - 3: Error Bursts
         */
        unsigned char colorMode = 0;

        Execution GetCycledRed(double* pulsedRed);
        Execution GetCycledGreen(double* pulsedGreen);
        Execution GetCycledBlue(double* pulsedBlue);
        Execution UpdateColors();

        double oldRed = 0;
        double oldGreen = 0;
        double oldBlue = 0;

        double currentRed = 0;
        double currentGreen = 0;
        double currentBlue = 0;

        /**
         * @brief the current count of half bursts.
         * When even, the LED should be OFF. When
         * odd it should be ON.
         */
        unsigned int _burstPeriodCount = 0;

        /**
         * @brief Private variable used to store the
         * wanted bursts count needed to display the error message.
         * If the burst count reaches above this value, the LED
         * is kept off until the message is over and thus repeated
         * again.
         */
        unsigned int _wantedBurstCount = 0;

        /**
         * @brief Private variable that is used to store
         * how many milliseconds per burst period is required
         * to display the error message.
         */
        double _burstDuration = 0;

        /**
         * @brief private variable used as a tick counter
         * to count error message burst periods
         */
        double errorTick = 0;

        /**
         * @brief Private variable used as a flag
         * for UpdateColors to device wether the LED
         * should be ON or OFF.
         * 
         * if true, LED should be ON.
         * if false, LED should be OFF.
         */
        bool errorLightState = false;

        /**
         * @brief The current step of the
         * animation. 1 tick corresponds to
         * 1 CLOCK_PERIOD_MS.
         */
        double currentTick = 0;
  
    public:
        /**
         * @brief The time in milliseconds
         * an animation will take to execute a cycle.
         * Defaults to 50 times the program's clock
         * speed in milliseconds.
         */
        unsigned int animationDuration = 500;

        int status = 0;
        bool built = false;

        double wantedRed = 0;
        double wantedGreen = 0;
        double wantedBlue = 0;
        unsigned char intensity = 255;

        unsigned char pulseExponent = 4;
        //////////////////////////////////////////////////////////// - CONSTRUCTOR - 
        RGB(int pinRGB);
        RGB();
        //////////////////////////////////////////////////////////// - Set functions - 
                
        /**
         * @brief Configures the error mode and set itself to it.
         * @attention
         * This will automatically set the RGB mode to 3 (error bursts).
         * @param burstCount
         * How many bursts of red light should there be in each message.
         * @param burstPeriod 
         * How long is a burst (on to off) (milliseconds)
         * @param messageDuration 
         * How long should the error message display before repeating again.
         * @return Execution 
         */
        Execution SetErrorMode(unsigned char burstCount, double burstPeriod, unsigned int messageDuration);
        /**
         * @brief Set the static color for the RGB LED.
         * 
         * @param red 0 to 255
         * @param green 0 to 255
         * @param blue 0 to 255
         * @return Execution 
         */
        Execution SetColors(double red, double green, double blue);
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
        Execution SetAnimations(unsigned char newCycleIntensity, unsigned int newAnimationDuration, unsigned char newSinExponent);
        /**
         * @brief Set the Mode of the RGB animation
         * 
         * @param mode 
         *  - 0: static
         *  - 1: pulsed
         *  - 2: RGB cycle
         * @return Execution 
         */
        Execution SetMode(unsigned char mode);

        /**
         * @brief Timebase function.
         * Needs to be periodically called in a callback.
         * @return Execution 
         */
        Execution Update();
 };

#endif