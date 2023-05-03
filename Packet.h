/**
 * @file Packet.h
 * @author Lyam (Lyam.brs@gmail.com)
 * @brief This file contains the definition of
 * the packet class. The packet class is used to
 * store methods used to decypher packets as a whole.
 * @version 0.1
 * @date 2023-05-02
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

#ifndef PACKET_H
  #define PACKET_H

#pragma region  Include
#include "Globals.h"
#pragma endregion

#pragma region Class
/**
 * @brief The packet class is used to
 * store methods used to decypher packets as a whole.
 */
class cPacket
{       
    private:
        int _status = Status::Booting;   
        /** @brief The size of the data byte array */
    public:
        /////////////////////////////////////////
        /**
         * @brief Variable which holds the 
         * object's initialization status.
         * If set to true, the object was 
         * successfully initialized and thus 
         * can be used without potential errors. 
         * Otherwise, it is set to false by 
         * default.
         */
        bool built = false;
        /////////////////////////////////////////
        ///@brief Construct a new cPacket object
        cPacket();
        ////////////////////////////////////////////////////////////

        /**
         * @brief Get the function ID from a given packet.
         * @param packetID 
         * @return Execution 
         */
        Execution GetID(unsigned short* packet, int packetSize, unsigned char* packetID);

        /**
         * @brief Check if a given checksum corresponds
         * to a given packet's checksum.
         * 
         * @param packet 
         * @param packetSize
         * @param checkSumToverify 
         * @return Execution 
         */
        Execution VerifyCheckSum(unsigned short* packet, int packetSize, unsigned char checkSumToverify);

        /**
         * @brief Check if the ID of a given packet
         * corresponds to the list of supported IDs of
         * your device.
         * @param packet 
         * @param packetSize 
         * @return Execution 
         */
        Execution VerifyID(unsigned short* packet, int packetSize);

        /**
         * @brief Gets the amount of parameters inside
         * a packet.
         * @param packet 
         * @param packetSize 
         * @param resultedParamCount 
         * @return Execution 
         */
        Execution GetAmountOfParameters(unsigned short* packet, int packetSize, unsigned char* resultedParamCount);

        /**
         * @brief Transform a variable converted to bytes
         * into a valid packet segment.
         * @param bytesToConvert 
         * @param resultedSegment 
         * @param byteCount 
         * @param resultedSegmentSize 
         * @return Execution 
         */
        Execution GetParameterSegmentFromBytes(unsigned char* bytesToConvert, unsigned short* resultedSegment, int byteCount, int resultedSegmentSize);

        /**
         * @brief Combine 2 segments togheter into 1 array of chunks.
         * This is used to slowly build your packet using all the
         * different segments created from variables
         * @param FirstSegment 
         * @param sizeOfFirstSegment 
         * @param secondSegment 
         * @param sizeOfSecondSegment 
         * @param appendResult 
         * @param sizeOfResult 
         * @return Execution 
         */
        Execution AppendSegments(unsigned short* FirstSegment, int sizeOfFirstSegment, unsigned short* secondSegment, int sizeOfSecondSegment, unsigned short* appendResult, int* sizeOfResult);

        /**
         * @brief Transform an array of segments into
         * a valid packet. This creates the start chunk
         * and the check chunk automatically.
         * @param functionID
         * The ID to give to the start chunk of the packet
         * @param paramSegments 
         * The array of parameter segments created from AppendSegments
         * @param sizeOfParamSegments 
         * The size of the paramSegments array.
         * @param resultedPacket 
         * Pointer to where the resulted packet will be stored
         * @param sizeOfResultedPacket 
         * Available size needed to store the resulted packet.
         * @return Execution 
         */
        Execution CreateFromSegments(unsigned char functionID, unsigned short* paramSegments, int sizeOfParamSegments, unsigned short* resultedPacket, int sizeOfResultedPacket);

        /**
         * @brief Get a segment from a packet with only 1 segment.
         * A segment is an array of unsigned char
         * @param packet 
         * @param packetSize 
         * @param resultParameter 
         * @param sizeOfResultParameter 
         * @return Execution 
         */
        Execution GetParametersFromPacket(unsigned short* packet, int packetSize, unsigned char* resultParameter, int sizeOfResultParameter);
};
#pragma endregion

#endif
  