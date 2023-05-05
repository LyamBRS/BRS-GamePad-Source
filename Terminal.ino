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
cTerminal::cTerminal()
{
    built = true;
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
Execution cTerminal::_HandlePlaneArrival(unsigned short newChunkArrival)
{
    Execution execution;
    int chunkType;
    unsigned char receivedByte;

    #pragma region -Chunk analysis-

    // Get the chunk type.
    execution = Chunk.ToType(newChunkArrival, &chunkType);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("60:Terminal -> Chunk.ToType ");
        Device.SetStatus(Status::CommunicationError);
        return execution;
    }

    // Get the chunk's byte data.
    execution = Chunk.ToByte(newChunkArrival, &receivedByte);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("69:Terminal -> Chunk.ToByte ");
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
            Device.SetErrorMessage("82:Terminal -> Multiple Starts");
            Device.SetStatus(Status::CommunicationError);
            return Execution::Failed;
        }

        // End of packet received
        if(chunkType == ChunkType::Check)
        {
            receivingPacket = false;

            // - Checksum not matching - //
            if(_calculatedChecksum != receivedByte)
            {
                Device.SetErrorMessage("95:Terminal -> Check Mismatch.");
                Device.SetStatus(Status::CommunicationError);
                return Execution::Failed;
            }
            else
            {
                // - PLANE IS OK FOR ARRIVAL - //
            }
        }

        // - STORE CHUNK - //
    }
    else
    {
        if(chunkType == ChunkType::Start)
        {
            #pragma region -Start of Arrival handling-
            _calculatedChecksum = 0;
            #pragma endregion
        }
        else
        {
            Device.SetErrorMessage(STRAY_CHUNK_RECEIVED);   
        }
    }
  return Execution::Bypassed;
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
Execution cTerminal::_HandlePlaneDeparture(unsigned short* departingChunk)
{
    return Execution::Failed;
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
Execution cTerminal::GetLastArrival(unsigned short* packetBuffer, int packetBufferSize)
{
    return Execution::Failed;
}

/**
 * @brief This method attempts to queue a plane to 
 * be sent eventually on the taxiway.
 * 
 * @attention this function will not verify your plane.
 * nor if the ID is available in the buffer list.
 * 
 * @param planeID 
 * The function ID corresponding to the plane request
 * that will try to enter the taxiway.
 * @return Execution::Unecessary = Plane already taxiing | Execution::Passed = Plane is now taxiing | Execution::Failed terminal status does not allow departures | Execution::Bypassed = Departure buffer is overflowing.
 */
Execution cTerminal::PutPlaneOnTaxiway(unsigned char planeID)
{
    if(departureStatus == TerminalStatus::DepartureAvailable)
    {
        for(int index = 0; index < SIZE_OF_DEPARTURE_TAXIWAY; index++)
        {
            unsigned char planeInTaxiway = _DepartureIDBuffer[index];
    
            if(planeID == planeInTaxiway)
            {
                // Plane is already taxiing.
                return Execution::Unecessary;
            }

            if(index == _amountOfPlanesTaxiing)
            {
                _amountOfPlanesTaxiing++;
                _DepartureIDBuffer[index] = planeID;
                return Execution::Passed;

                // Plane is now taxiing.
            }
        }
        departureStatus = TerminalStatus::NotEnoughSpace;
        return Execution::Bypassed;
    }
    else
    {
        if(departureStatus == TerminalStatus::NotEnoughSpace)
        {
            return Execution::Bypassed;
        }

        return Execution::Failed;
    }
    // Plane can taxi.

    return Execution::Failed;
}

/**
 * @brief This function returns a which plane ID
 * is next to the runway and is awaiting for
 * takeoff.
 * @attention
 * this function will remove the plane from the
 * taxiway. If you do not handle the plane, it's
 * like it'll go to the backroom and the gate will
 * forever be waiting for its return.
 * @param idOfNextPlane 
 * The Id of the function to get the departing plane from.
 * @return Execution::Unecessary = No plane departing |
 */
Execution cTerminal::GetNextDepartingPlaneID(unsigned char* idOfNextPlane)
{
    if(_amountOfPlanesTaxiing > 0)
    {
        // Copy the ID of the plane thats next to the runway.
        unsigned char departingPlaneID = _DepartureIDBuffer[_amountOfPlanesTaxiing-1];

        // All the planes go forward just like traffic do
        for(int index = 0; index < SIZE_OF_DEPARTURE_TAXIWAY-1; index++)
        {
            _DepartureIDBuffer[index] = _DepartureIDBuffer[index+1];
        }

        // If the terminal previously had not enough space, its no longer the case
        if(departureStatus == TerminalStatus::NotEnoughSpace)
        {
           departureStatus == TerminalStatus::DepartureAvailable; 
        }

        // There is 1 less plane that is taxiing.
        _amountOfPlanesTaxiing--;
    }
    else
    {
        return Execution::Unecessary;
    }
    return Execution::Failed;
}

/**
 * @brief Resets this class to default value.
 * @attention
 * This will clear any buffers stored in this.
 * @return Execution 
 */
Execution cTerminal::Reset()
{
    departureStatus = TerminalStatus::Initialised;
    arrivalStatus = TerminalStatus::Initialised;
    _amountOfPlanesTaxiing = 0;

    return Execution::Passed;
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