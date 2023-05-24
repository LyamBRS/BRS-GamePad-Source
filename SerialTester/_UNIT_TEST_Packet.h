/**
 * @file _UNIT_TEST_Packet.h
 * @author Lyam (lyam.brs@gmail.com)
 * @brief This file contains the various
 * definitions of unit test functions used
 * to verify that the Packet class functions
 * as intended.
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




#include "Globals.h"

#ifndef PACKET_UNIT_TEST_H
  #define PACKET_UNIT_TEST_H


/**
 * @brief Tests if the packet class
 * can successfully gather the ID
 * of valid predetermined packets / planes
 * 
 * @return Execution 
 */
Execution TEST_PACKET_GetID();

/**
 * @brief Test to check the packet
 * class can successfully verify a
 * given checksum with a checksum from
 * valid predetermined packets.
 * 
 * @return Execution 
 */
Execution TEST_PACKET_VerifyCheckSum();

/**
 * @brief Function that checks if the
 * packet class can successfully
 * identify valid predetermined packets
 * based on the list of IDs in BFIO.h
 * 
 * @return Execution 
 */
Execution TEST_PACKET_VerifyID();

/**
 * @brief Function that checks if the
 * packet class can successfully get
 * how many parameters valid predetermined
 * packets have.
 * 
 * @return Execution 
 */
Execution TEST_PACKET_GetAmountOfParameters();

/**
 * @brief Function that verifies that the
 * packet class can successfully build a
 * segment from an array of bytes.
 * Array of bytes are built using the cData
 * class.
 * 
 * @return Execution 
 */
Execution TEST_PACKET_GetParameterSegmentFromBytes();

/**
 * @brief Function that verifies that the
 * packet class can successfully merge 2
 * segments of chunks togheter into one
 * large segment.
 * 
 * @return Execution 
 */
Execution TEST_PACKET_AppendSegments();

/**
 * @brief Function that verifies that
 * the packet class can successfully
 * build a packet form a bunch of segments
 * 
 * @return Execution 
 */
Execution TEST_PACKET_CreateFromSegments();

/**
 * @brief Test function that verifies that the
 * packet class can successfully extract every
 * parameter segments from valid predetermined
 * packets.
 * 
 * @return Execution 
 */
Execution TEST_PACKET_GetParametersFromPacket();

Execution TEST_PACKET_EntireProcess();

/**
 * @brief Unit test function which returns
 * Execution::Passed if packet works
 * successfully for each methods it has.
 * 
 * It will return Execution::Failed if any
 * function fails
 * @return Execution 
 */
Execution cPacket_LaunchTests();


#endif