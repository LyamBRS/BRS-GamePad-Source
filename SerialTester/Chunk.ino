/**
 * @file Chunk.ino
 * @author Lyam (lyam.brs@gmail.com)
 * @brief This file contains the core
 * methods of the Chunk class as declared
 * in Chunk.h
 * @version 0.1
 * @date 2023-04-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
/////////////////////////////////////////////////////////////////////////////
#include "Globals.h"
/////////////////////////////////////////////////////////////////////////////

///@brief Construct a new cChunk object
cChunk::cChunk()
{
    built = true;
}

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
Execution cChunk::ToType(unsigned short chunkToConvert, int* resultedType)
{
    chunkToConvert = chunkToConvert & 0xFF00;
    
    switch(chunkToConvert)
    {
        case(ChunkType::Byte):
        case(ChunkType::Check):
        case(ChunkType::Div):
        case(ChunkType::Start):
            *resultedType = chunkToConvert;
            return Execution::Passed;
        break;        
    }

    // Incorrect Chunk type given.
    // This function does not set any error status by itself.
    return Execution::Failed;
}

/**
 * @brief This annoying ass function is the result of the UART protocol
 * working only with bytes. This means that the 10 bits to send actually
 * need to be a whole ass 16 bits.
 * 
 * @param resulted2bytes 
 * 0: First to send, 1: second to send.
 * @return Execution 
 */
Execution cChunk::ToUART(unsigned short chunkToSend, unsigned char* resulted2bytes)
{
    return (Data.ToBytes(chunkToSend, resulted2bytes, 2));
}

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
Execution cChunk::ToByte(unsigned short chunkToConvert, unsigned char* resultedByte)
{
    if(chunkToConvert > 1023)
    {
        Device.SetErrorMessage("77:Chunk -> Chunk above 1203  ");
        Serial.println(chunkToConvert);
        return Execution::Failed;
    }
    else
    {
        chunkToConvert = chunkToConvert & 0x00FF;
        unsigned char result = (unsigned char) chunkToConvert;
        *resultedByte = result;
        return Execution::Passed;
    }
}

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
Execution cChunk::ToChunk(unsigned char byteToConvert, unsigned short* resultedChunk, int typeToApply)
{
    // - Verifying passed chunk type
    switch(typeToApply)
    {
        case(ChunkType::Byte):
        case(ChunkType::Check):
        case(ChunkType::Div):
        case(ChunkType::Start):
            break;
        
        default:
            return Execution::Failed;
    }

    unsigned short result = 0;
    result = byteToConvert;
    result = result + typeToApply;
    *resultedChunk = result;
    return Execution::Passed;

}
