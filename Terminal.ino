/**
 * @file Joystick.ino
 * @author Lyam (Lyam.brs@gmail.com)
 * @brief Declarations of cJoystick's methods.
 * Each method is written here for you to
 * see how they work inside of them.
 * 
 * See Joystick.h for definitions of the cJoystick class.
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
    ############    ####      ##   ##########   */
/////////////////////////////////////////////////////////////////////////////
#include "Terminal.h"
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief Construct a new c Traffic Handler::c Traffic Handler object
 * Default constructor. Does not set the class to "Built".
 */
cTrafficHandler::cTrafficHandler()
{
    built = false;
}
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
Execution cTerminal::_HandleChunkArrival(unsigned short newChunkArrival)
{
    ChunkType chunkType;
    Execution execution
    unsigned char receivedByte;

    #pragma region -Chunk analysis-

    // Get the chunk type.
    execution = Chunk.ToType(newChunkArrival, &chunkType);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage(FATAL_BFIO_ERROR_CHUNK_HANDLING);
        Device.SetStatus(Status::CommunicationError);
        return execution;
    }

    // Get the chunk's byte data.
    execution = Chunk.ToByte(newChunkArrival, &receivedByte);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage(FATAL_BFIO_ERROR_CHUNK_HANDLING);
        Device.SetStatus(Status::CommunicationError);
        return execution;    
    }
    #pragma endregion
    
    // Executed if we are already receiving packets.
    if(receivingPacket)
    {
        // If a start chunk is sent before end chunks, there is an issue.
        if(chunkType ==  ChunkType::Start)
        {
            // The packet that we were receiving suddently got cut off by another.
            Device.SetErrorMessage(FATAL_BFIO_ERROR_CHUNK_HANDLING);
            Device.SetStatus(Status::CommunicationError);
            return Execution::Failed;
        }

        // End of packet received
        if(chunkType == ChunkType::Check)
        {
            receivingPacket = false;

            // - CALCULATE CHECKSUM - //
        }

        // - STORE CHUNK - //
    }
    else
    {
        if(chunkType == ChunkType::Start)
        {
            #pragma region -Start of Arrival handling-
            _currentCheckSum = 0;
            #pragma endregion
        }
        else
        {
            Device.SetErrorMessage(STRAY_CHUNK_RECEIVED);   
        }
    }

}

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
Execution cTerminal::_HandleChunkDeparture(unsigned short* departingChunk)
{

}

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
Execution cTerminal::GetLastPacket(unsigned short* packetBuffer, int packetBufferSize)
{

}

/**
 * @brief This method queues a packet to be sent eventually.
 * 
 * @attention this function will verify your packet.
 * 
 * @param packetBuffer 
 * array of chunk which corresponds to the packet to queue
 * @param packetBufferSize 
 * Amount of chunks in the array including the start and check chunk.
 * @return Execution 
 */
Execution cTerminal::QueueNewPacket(unsigned short* packetBuffer, int packetBufferSize)
{

}

/**
 * @brief Puts the BFIO function ID of the
 * packet stored in the buffer in a pointer.
 * This is used to identify which function
 * or answer it is identified to.
 * @param idOfLastPacket 
 * Id of the packet (0-255)
 * @return Execution 
 */
Execution cTerminal::GetLastPacketID(unsigned char* idOfLastPacket)
{

}

/**
 * @brief Resets this class to default value.
 * @attention
 * This will clear any buffers stored in this.
 * @return Execution 
 */
Execution cTerminal::Reset()
{

}

/**
 * @brief 
 * Set the mode which the traffic handler is in:
 * @attention
 *  - 0: Regular mode (default)
 *  - 1: Ignore incoming 
 * 
 * @param newMode 
 * @return Execution 
 */
Execution cTerminal::SetMode(unsigned char newMode)
{
    if(newMode != _currentMode)
    {
        if(newMode < 2)
        {
            _currentMode = newMode;
            return Execution::Passed;
        }
        else
        {
            return Execution::Failed;
        }
    }
    else
    {
        return Execution::Unecessary;
    }
}

/**
 * @brief Gets the current mode which the terminal
 * is in.
 * @attention
 *  - 0: Regular mode (default)
 *  - 1: Ignore incoming 
 * @param currentMode 
 * @return Execution 
 */
Execution cTerminal::GetMode(unsigned char* currentMode)
{
    *currentMode = _currentMode;
    return Execution::Passed;
}