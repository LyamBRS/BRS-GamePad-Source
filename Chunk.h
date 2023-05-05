/**
 * @file Chunk.h
 * @author Lyam (lyam.brs@gmail.com)
 * @brief This file contains the declaration
 * of the global chunk class commony used
 * throughout this application.
 * See the chunk class definition for more
 * information regarding its members and
 * methods aswell as generic purpose.
 * @version 0.1
 * @date 2023-04-26
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

#ifndef CHUNK_H
  #define CHUNK_H

#pragma region  Include
#include "Globals.h"
#pragma endregion

#pragma region Class
/**
 * @brief The Chunk class is a class
 * that allows low level interfacing
 * and handling of BFIO chunks. The
 * BFIO datasheet explains in greater
 * details what is a chunk and how it
 * is used in the BFIO protocol.
 */
class cChunk
{       
    private:
        int _status = Status::Booting;   
  
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
        ///@brief Construct a new cChunk object
        cChunk();
        /////////////////////////////////////////

        /**
         * @brief Function that returns, through
         * a pointer the ChunkType of the chunk
         * specified. Useful to figure out the
         * purpose of a chunk when decoding
         * packets and segments on the highway.
         * @param chunkToConvert 
         * The chunk to analyze for its ChunkType.
         * @param resultedType 
         * A pointer where the chunk type will be
         * placed.
         * @return Execution: How the function's
         * execution went. If successful,
         * Execution::Passed.
         */
        Execution ToType(unsigned short chunkToConvert, int* resultedType);
        /**
         * @brief Function that converts a chunk
         * to an unsigned char single byte.
         * This function is used to extract the
         * useful data from an encoded chunk.
         * It is important to keep in memory the
         * chunk's type.
         * @param chunkToConvert
         * The chunk to analyze and get the
         * data from.
         * @param resultedByte 
         * A pointer where the chunk's byte will
         * be placed.
         * @return Execution 
         */
        Execution ToByte(unsigned short chunkToConvert, unsigned char* resultedByte);
        /**
         * @brief A function used to convert a
         * byte to a valid BFIO chunk. You need
         * to specify the wanted ChunkType as
         * well.
         * 
         * @param byteToConvert
         * The unsigned char to convert to a
         * unsigned short chunk.
         * @param resultedChunk 
         * A pointer where the resulted
         * unsigned short chunk will be placed.
         * @param typeToApply 
         * The ChunkType applied to the resulted
         * chunk.
         * @return Execution 
         */
        Execution ToChunk(unsigned char byteToConvert, unsigned short* resultedChunk, int typeToApply);

        /**
         * @brief This annoying ass function is the result of the UART protocol
         * working only with bytes. This means that the 10 bits to send actually
         * need to be a whole ass 16 bits.
         * 
         * @param resulted2bytes 
         * 0: First to send, 1: second to send.
         * @return Execution 
         */
        Execution ToUART(unsigned short chunkToSend, unsigned char* resulted2bytes);
};
#pragma endregion

#endif
  