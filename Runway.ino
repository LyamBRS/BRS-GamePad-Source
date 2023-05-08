/**
 * @file Runway.ino
 * @author Lyam (Lyam.brs@gmail.com)
 * @brief The code methods of the
 * runways classes.
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
    ############    ####      ##   ##########   */
/////////////////////////////////////////////////////////////////////////////
#include "Runway.h"
/////////////////////////////////////////////////////////////////////////////
cDepartureRunway::cDepartureRunway()
{
    built = false;
    status = HighwayStatus::Closed;
}

cDepartureRunway::cDepartureRunway(Stream *streamObject)
{
      _streamRef = streamObject;
      built = true;
      status = HighwayStatus::Empty;
}

/**
 * @brief Time base function executed
 * periodically. This handles chunks departure.
 * 
 * @return Execution 
 */
Execution cDepartureRunway::_Handle()
{
    Execution execution;

    if(planeAvailable)
    {
        // A new plane is ready for takeoff!
        currentPlaneChunk = 0;
        planeAvailable = false;             // No planes are available for takeoff anymore
        sendingPlane = true;                // There is currently a plane on the runway.
        status = HighwayStatus::Traffic;    // There is traffic on the runway.
    }

    // - Plane is taking off on this runway - //
    if(sendingPlane)
    {
        // Step 1 is to convert the BFIO chunk into an UART 2 bytes chunk.
        unsigned char UART_ChunksToSend[2];
        unsigned short chunkToSend = _runway[currentPlaneChunk];

        execution = Chunk.ToUART(chunkToSend, UART_ChunksToSend);
        if(execution != Execution::Passed)
        {
            Device.SetErrorMessage("65:Runway -> Chunk.ToUART     ");
            Device.SetStatus(Status::CommunicationError);
            return Execution::Crashed;
        }

        // - Sending the UART Chunks - //
        _streamRef->print(UART_ChunksToSend[0]);
        _streamRef->print(UART_ChunksToSend[1]);
        currentPlaneChunk++;
    }

    return Execution::Passed;
}

/**
 * @brief Sets a plane for takeoff on this runway.
 * This function will get the plane from the gate,
 * build it, verify it, and queue it on the runway
 * if everything goes well.
 * @param planeID 
 * The plane's function ID.
 * @return Execution 
 */
Execution cDepartureRunway::SetPlaneForTakeOff(unsigned char planeID)
{
    return Execution::Bypassed;
}