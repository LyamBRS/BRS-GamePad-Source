/**
 * @file Defines.h
 * @author Lyam (Lyam.BRS@gmail.com)
 * @brief This file contains all the global defines
 * used through out this whole application.
 * Any define which isnt reserved for specific
 * applications should be placed in this file.
 * @version 0.1
 * @date 2023-04-27
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

#ifndef DEFINES_H
  #define DEFINES_H


  #define TIMEOUT_DURATION_MS 1000

  #pragma region RGB_ErrorCodes
    // Error CODE:
    // Amount of pulse to do, pulse period in milliseconds, total length of error code in milliseconds
    // Error COLORS:
    // red,green,blue

    #pragma region UNIT_TESTS
        // UT stands for Unit Test. They are defines specific to rgb codes for unit tests
        #define UT_ERROR_COLOR 255,255,0
        #define UT_PASSED_COLOR 0,255,0

        #define UT_PASSED_CODE 1,500,1000

        ///@brief Error code given when cRgb fails its unit test.
        #define UT_CRGB_ERROR_CODE 1,200,5000
        ///@brief Error code given when cData fails its unit test.
        #define UT_CDATA_ERROR_CODE 2,200,5000
        ///@brief Error code given when cDevice fails its unit test.
        #define UT_CDEVICE_ERROR_CODE 3,200,5000
        ///@brief Error code given when cChunk fails its unit test.
        #define UT_CCHUNK_ERROR_CODE 4,200,5000
        ///@brief Error code given when cJoystick fails its unit test.
        #define UT_CJOYSTICK_ERROR_CODE 5,200,5000
        ///@brief Error code given when cSwitch fails its unit test.
        #define UT_CSWITCH_ERROR_CODE 6,200,5000
        ///@brief Error code given when cBFIO fails its unit test.
        #define UT_CBFIO_ERROR_CODE 7,200,5000
        ///@brief Error code given when cBFIO fails its unit test.
        #define UT_CPACKET_ERROR_CODE 8,200,5000
    #pragma endregion
  #pragma endregion

  #pragma region ErrorMessages

    #define FATAL_BFIO_ERROR_CHUNK_HANDLING "Fatal error occured during chunk arrival handling"
    #define INCORRECT_CHUNK_RECEIVED        "Some of the chunks received were incorrect."
    #define INCORRECT_PACKET_RECEIVED       "Some received packets were incorrect"
    #define UNSUPPORTED_FUNCTIONS           "Failed to parse incomming packets due to undefined behaviours."
    #define STRAY_CHUNK_RECEIVED            "Some stray chunks were received."

    #define DIV_COUNTING                    "Error when counting Div Chunks"
    #define FREE_BYTES_IN_PACKET            "Detected free bytes in packet"

    #define INTERNAL_BUFFER_SIZE_ERROR      "INTERNAL BUFFER SIZE ERROR"
    #define INTERNAL_CHUNK_CONVERTION_FAIL  "INTERNAL CHUNK CONVERTION FAIL"
    #define INTERNAL_BYTE_CONVERTION_FAIL   "INTERNAL BYTE CONVERTION FAIL"
    #define INTERNAL_PACKET_BUILDING_FAIL   "INTERNAL PACKET BUILDING FAIL"

  #pragma endregion

  #pragma region ErrorCodes
  #pragma endregion

#endif