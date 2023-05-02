/**
 * @file TrafficHandler.h
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

#ifndef TERMINAL_H
  #define TERMINAL_H
//=============================================//
//	Include
//=============================================//
#include "Globals.h"

/**
 * @brief The terminal handler class allows
 * your device to handler its BFIO terminal.
 */
class cTerminal
 {       
    private:
        /**
         * @brief Private variable that stores
         * the current count of the checksum ever
         * since the start packet was received.
         * 
         * Used in the final comparaison for packet
         * integrity.
         */
        unsigned char _currentCheckSum = 0;

        unsigned short _ArrivalBuffer[100];

        /**
         * @brief list of the function's ID
         * that needs to be sent in order of newest to most urgent.
         */
        unsigned char _DepartureIDBuffer[20];

        /**
         * @brief The current mode.
         * 0: regular (default)
         * 1: Rejecting incoming packets (Will not save the chunks other than start and check chunk.)
         */
        unsigned char _currentMode = 0;

    public:
        /// @brief set to true if the class is constructed.
        bool built = false;

        /// @brief Is set to true if a packet is ready for parsing
        bool packetAvailable = false;

        /// @brief Is set to true if the function is currently receiving a packet
        bool receivingPacket = false;

        /// @brief The status of the terminals departure.
        TerminalStatus departureStatus = TerminalStatus::Initialised;

        /// @brief The status of the terminals arrivals.
        TerminalStatus arrivalStatus = TerminalStatus::Initialised;

        /// @brief Holds the ID of the packet that is currently being received. Defaults to 0.
        unsigned char receivingID = 0;
        //////////////////////////////////////////////
        cTerminal();
        //////////////////////////////////////////////

        /**
         * @brief Method that gets incoming chunks
         * and stores them in the arrivals traffic buffer.
         * This calculates the checksum as it goes,
         * identifies when a start was received, compares
         * check chunks and so on.
         * @param newArrival
         * Chunk that just arrived and needs to be queued.
         * @return Execution::Passed chunk queued in buffer
         */
        Execution _HandleChunkArrival(unsigned short newChunkArrival);

        /**
         * @brief Method that gets incoming chunks
         * and stores them in the arrivals traffic buffer.
         * This calculates the checksum as it goes,
         * identifies when a start was received, compares
         * check chunks and so on.
         * @param departingChunk
         * Pointer to where the chunk that will depart is stored. 
         * @return Execution::Passed : A new chunk was set
         * Execution::Unecessary : No chunks to send.
         */
        Execution _HandleChunkDeparture(unsigned short* departingChunk);

        /**
         * @brief Stores the last packet stored in
         * the buffer into an unsigned short packet
         * buffer array. Make sure that your buffer is
         * large enough to store the entire packet.
         * 
         * @attention
         * This will clear the buffer of this packet.
         * 
         * @param packetBuffer
         * Array of chunks where the packet will be stored
         * @param packetBufferSize 
         * Size of the chunk array
         * @return Execution 
         */
        Execution GetLastPacket(unsigned short* packetBuffer, int packetBufferSize);

        /**
         * @brief This method queues a packet to be sent eventually.
         * 
         * @attention this function will verify your packet.
         * 
         * @param planeID 
         * Function ID that needs to be queued in the requests buffer.
         * @return Execution 
         */
        Execution PutPlaneOnTaxiway(unsigned char planeID);

        /**
         * @brief Puts the BFIO function ID of the
         * packet stored in the buffer in a pointer.
         * This is used to identify which function
         * or answer it is identified to.
         * @param idOfLastPacket 
         * Id of the packet (0-255)
         * @return Execution 
         */
        Execution GetLastPacketID(unsigned char* idOfLastPacket);

        /**
         * @brief Resets this class to default value.
         * @attention
         * This will clear any buffers stored in this.
         * @return Execution 
         */
        Execution Reset();

        /**
         * @brief Get the preliminary information of the
         * arriving packet that is currently being handled.
         * 
         * @attention This function will return information
         * on a packet that is currently being dealt with.
         * The packet is not fully received when this function
         * can be called.
         * 
         * @param currentPacketID
         * Pointer to a variable where the current packet ID will be placed.
         * @param currentChunkCount 
         * Pointer to where the current chunk count will be stored
         * @param currentCheckSum 
         * Pointer to where the current check sum will be stored.
         * @return Execution 
         */
        Execution GetCurrentArrivalInfo(unsigned char* currentPacketID, int* currentChunkCount, unsigned char* currentCheckSum);

        /**
         * @brief 
         * Set the mode which the traffic handler is in:
         * @attention
         *  - 0: Regular mode (default)
         *  - 1: Ignore incoming (keeps track of start and check but no bytes or div packets)
         * 
         * @param newMode 
         * @return Execution 
         */
        Execution SetMode(unsigned char newMode);

        /**
         * @brief Gets the current mode which the terminal
         * is in.
         * @attention
         *  - 0: Regular mode (default)
         *  - 1: Ignore incoming (keeps track of start and check but no bytes or div packets)
         * @param currentMode 
         * @return Execution 
         */
        Execution GetMode(unsigned char* currentMode);

        /**
         * @brief Checks if the plane can fit on the taxiway
         * (checks if the buffer has enough space for the request or answer)
         * @param planeSize 
         * @return Execution 
         */
        Execution CanPlaneTaxi(int planeSize);

        /**
         * @brief Method that returns Execution::Passed if the
         * specified plane is already queueing for departure.
         * Otherwise, Execution::Failed is returned.
         * 
         * @param planeID 
         * ID of the plane to check for on the taxiway.
         * @return Execution 
         */
        Execution IsPlaneOnDepartureTaxiway(unsigned char planeID);


 };

#endif