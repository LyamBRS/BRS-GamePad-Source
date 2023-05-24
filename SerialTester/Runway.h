/**
 * @file Runway.h
 * @author Lyam (Lyam.brs@gmail.com)
 * @brief This file contains the runway
 * class which directly handles plane
 * takeoffs and landings.
 * @version 0.1
 * @date 2023-05-05
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

#ifndef RUNWAY_H
  #define RUNWAY_H
//=============================================//
//	Include
//=============================================//
#include "Globals.h"

/**
 * @brief Class that builds a runway
 * that handles plane departures.
 */
class cDepartureRunway
 {       
    private:

        Stream *_streamRef;
        /**
         * @brief The runway space available for a plane
         * to take off.
         */
        unsigned short _runway[SIZE_OF_ARRIVAL_PLANE];

        /**
         * @brief The current mode.
         * 0: regular (default)
         * 1: Rejecting incoming packets (Will not save the chunks other than start and check chunk.)
         */
        unsigned char _currentMode = 0;

        /**
         * @brief 
         * Checksum currently being calculated
         * as the plane is landing on the arrival
         * runway.
         */
        unsigned char _calculatedChecksum = 0;

        /**
         * @brief Indicates where we are in the sending of the plane's chunks.
         * Defaults to 0.
         */
        unsigned char currentPlaneChunk = 0;

    public:
        /// @brief set to true if the class is constructed.
        bool built = false;

        /// @brief Is set to true if a packet is ready to transfer
        bool planeAvailable = false;

        /// @brief Is set to true if the function is currently receiving a packet
        bool sendingPlane = false;

        /// @brief The status of the terminals departure. defaults to closed.
        HighwayStatus status = HighwayStatus::Closed;

        //////////////////////////////////////////////
        cDepartureRunway();

        cDepartureRunway(Stream *streamObject);
        //////////////////////////////////////////////

        /**
         * @brief Time base function executed
         * periodically. This handles chunks departure.
         * 
         * @return Execution 
         */
        Execution _Handle();

        /**
         * @brief Sets a plane for takeoff on this runway.
         * This function will get the plane from the gate,
         * build it, verify it, and queue it on the runway
         * if everything goes well.
         * @param planeID 
         * The plane's function ID.
         * @return Execution 
         */
        Execution SetPlaneForTakeOff(unsigned char planeID);
 };

#endif