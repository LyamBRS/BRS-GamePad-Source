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
         * @brief Puts the total size of a packet
         * in a pointer. Returns Execution::Passed if
         * its successful.
         * @param packet 
         * @param resultedPacketsize 
         * @return Execution::Passed = size found | Execution::Crashed = No end found | Execution::Incompatibility = Did not start with a start chunk
         */
        Execution GetTotalSize(unsigned short* packet, int* resultedPacketsize);

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
         * @brief Gets a specific segment from a
         * given packet/plane in bytes.
         * A segment is an array of unsigned char
         * @param packet
         * An array of segment or parameter segment or validated packet to get an array of bytes from.
         * @param packetSize 
         * The size of the array to extract bytes from.
         * @param resultParameter 
         * Array of bytes where the parameter will be stored.
         * @param segmentNumber
         * Which segment of the array to extract bytes from. STARTS AT 1.
         * @param sizeOfResultParameter 
         * How much space is available to store that array.
         * @return Execution 
         */
        Execution GetBytes(unsigned short* packet, int packetSize, int segmentNumber, unsigned char* resultParameter, int sizeOfResultParameter);
        /**
         * @brief Get the array of unsigned char values from
         * a plane's valid segment. the segment must start with
         * a Div Chunk.
         * 
         * @param paramSegment
         * The segment to extract bytes from 
         * @param sizeOfParameterSegment 
         * How many chunks total is in the segment?
         * @param resultedBytes 
         * Array where the extracted bytes from the segment will be placed.
         * @param sizeOfResultedBytes 
         * The extracted bytes array must be at least 1 less than the size
         * of the parameter segment.
         * @return Execution::Passed = Worked | Execution::Failed = Parameter segment is wrong | Execution::Crashed = Internal functions could not execute.
         */
        Execution GetBytesFromParameterSegment(unsigned short* paramSegment, int sizeOfParameterSegment, unsigned char* resultedBytes, int sizeOfResultedBytes);

        /**
         * @brief Function that fully analyzes a
         * given packet of any size.
         * 
         * @param packetToAnalyze
         * The unkown packet that needs to be analyzed
         * @param resultedPacketsize 
         * The total size of the packet including start and check chunks.
         * @param amountOfParameters 
         * How many parameters were found in that pakcet.
         * @param packetID 
         * The extracted ID from the packet.
         * @return Execution::Passed = size found | Execution::Crashed = fatal analisis error | Execution::Incompatibility = Not in BFIO ids | Execution::Failed Something went wrong
         */
        Execution FullyAnalyze(unsigned short* packetToAnalyze, int* resultedPacketsize, int* amountOfParameters, unsigned char* packetID);
};
#pragma endregion

#endif
  