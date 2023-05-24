/**
 * @file _UNIT_TEST_Chunk.h
 * @author Lyam (lyam.brs@gmail.com)
 * @brief This file contains the various
 * definitions of unit test functions used
 * to verify that the Chunk class functions
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

#ifndef CHUNK_UNIT_TEST_H
  #define CHUNK_UNIT_TEST_H

/**
 * @brief Function that returns
 * execution::passed if every aspects
 * of ToType from the cChunk class
 * behaves as espected.
 * 
 * @return Execution 
 */
Execution TEST_CHUNK_ToType();
/**
 * @brief Function that returns
 * execution::passed if every aspects
 * of ToByte from the cChunk class
 * behaves as espected.
 * 
 * @return Execution 
 */
Execution TEST_CHUNK_ToByte();
/**
 * @brief Function that returns
 * execution::passed if every aspects
 * of ToChunk from the cChunk class
 * behaves as espected.
 * 
 * @return Execution 
 */
Execution TEST_CHUNK_ToChunk();

/**
 * @brief Unit test function which returns
 * Execution::Passed if chunk works
 * successfully for each methods it has.
 * 
 * It will return Execution::Failed if any
 * function fails to convert data and read
 * back the same exact values.
 * @return Execution 
 */
Execution cChunk_LaunchTests();


#endif