/**
 * @file Gates.ino
 * @author Lyam (Lyam@gmail.com)
 * @brief This file contains the core code of every gates.
 * @version 0.1
 * @date 2023-04-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

 #include "Globals.h"

/// @brief Local function that checks if the Master terminal's departures can be used with your plane
/// @param planeSize 
/// @return 
Execution _AskMasterTerminalForDeparture(int planeSize)
{
    Execution result;

    if(MasterTerminal.departureStatus != TerminalStatus::DepartureAvailable)
    {
        // Terminal cannot accept planes on its taxiway at the moment
        return Execution::Failed;
    }

    result = MasterTerminal.CanPlaneTaxi(planeSize);
    if(result != Execution::Passed)
    {
        // The plane cannot taxi on this terminal's departure taxiway at the moment.
        if(result == Execution::NoConnection)
        {
            // PLANES DONT HAVE DESTINATIONS (No end device connection detected)
            return result;
        }

        return Execution::Failed;
    }

    // The plane can use the Master's terminal departure taxiway
    return Execution::Passed;
}

/// @brief Local function that checks if the Slave terminal's departures can be used with your plane
/// @param planeSize 
/// @return 
Execution _AskSlaveTerminalForDeparture(int planeSize)
{
    Execution result;

    if(SlaveTerminal.departureStatus != TerminalStatus::DepartureAvailable)
    {
        // Terminal cannot accept planes on its taxiway at the moment
        return Execution::Failed;
    }

    result = SlaveTerminal.CanPlaneTaxi(planeSize);
    if(result != Execution::Passed)
    {
        // The plane cannot taxi on this terminal's departure taxiway at the moment.
        if(result == Execution::NoConnection)
        {
            // PLANES DONT HAVE DESTINATIONS (No end device connection detected)
            return result;
        }

        return Execution::Failed;
    }

    // The plane can use the Master's terminal departure taxiway
    return Execution::Passed;
}
/////////////////////////////////////////////////////////////////////////////
#include "Gates.h"
/////////////////////////////////////////////////////////////////////////////
/**
 * @brief Get the status of this gate.
 * See GateStatus for possible values this can
 * return.
 * 
 * @param currentStatus
 * Pointer to where the status will be placed.
 * @return Execution 
 */
Execution cGateFoundation::GetStatus(unsigned char* currentStatus)
{
    *currentStatus = status;
    return Execution::Passed;
}

/**
 * @brief Function that verifies the arrival to make
 * sure its the correct plane that docked to the gate.
 * @param arrivedPacket 
 * @return Execution 
 */
Execution cGateFoundation::_VerifyArrival(unsigned char planeID, unsigned short* arrivedPlane, int planeSize)
{
    Execution execution;

    if(planeSize > maxSizeOfPlane)
    {
        Device.SetErrorMessage("Packet exceed a gates capacity");
        return Execution::Failed;
    }

    // Do the plane ID and gate ID match?
    if(gateID != planeID)
    {
        Device.SetErrorMessage("Plane docking at wrong gate.");
        return Execution::Failed; 
    }

    // Parse plane.
    unsigned char amountOfParameters = 0;
    execution = Packet.GetAmountOfParameters(arrivedPlane, planeSize, &amountOfParameters);
    if(execution != Execution::Passed)
    {
        // Failed to get amount of parameters from docking plane.
        return Execution::Crashed;
    }

    if(amountOfParameters != expectedAmountOfParameters)
    {
        Device.SetErrorMessage("A plane had too many classes.");
        return Execution::Incompatibility;
    }

    return Execution::Passed;
}

/**
 * @brief Function that Queues an error answer
 * on the taxiway as an answer to an impossible or
 * failed request
 * @param errorCode
 * Specific BFIO error code associated with what went wrong.
 * @return Execution 
 */
Execution cGateFoundation::_SendErrorPlane(unsigned char errorCode)
{
    return Execution::Bypassed;
}


/**
 * @brief This function returns Execution::Passed if
 * the plane can leave the gate and taxi on the departure
 * taxiway. Otherwise, Execution::Failed is returned.
 * @return Execution 
 */
Execution cGateFoundation::_CanPlaneTaxiOnMaster()
{
    Execution execution;

    if(status == GateStatus::ReadyForDeparture)
    {
        // Is the terminal available for planes?
        execution = _AskMasterTerminalForDeparture(maxSizeOfPlane);
        if(execution != Execution::Passed)
        {
            // The gate cant allow planes to queue in on the Master terminal's taxiway
            return Execution::Bypassed;
        }
    
        // Is there already a similar plane on the taxiway?
        execution = MasterTerminal.IsPlaneOnDepartureTaxiway(gateID);
        if(execution != Execution::Failed)
        {
            // Plane is already in queue for departure on the taxiway.
            status = GateStatus::JustLeft;
            return Execution::Unecessary;
        }
    
        // Queue plane in taxiway
        execution = MasterTerminal.PutPlaneOnTaxiway(gateID);
        if(execution != Execution::Passed)
        {
            return Execution::Failed;
        }
    
        status = GateStatus::JustLeft;
        return Execution::Passed;
    }
    else
    {
        // Gate is not ready for a plane departure
        return Execution::Bypassed;
    }
}

/**
 * @brief This function returns Execution::Passed if
 * the plane can leave the gate and taxi on the departure
 * taxiway. Otherwise, Execution::Failed is returned.
 * @return Execution 
 */
Execution cGateFoundation::_CanPlaneTaxiOnSlave()
{
    Execution execution;

    // Is the terminal available for planes?
    execution = _AskSlaveTerminalForDeparture(maxSizeOfPlane);
    if(execution != Execution::Passed)
    {
        // The gate cant allow planes to queue in on the Slave terminal's taxiway
        return Execution::Bypassed;
    }

    // Is there already a similar plane on the taxiway?
    execution = SlaveTerminal.IsPlaneOnDepartureTaxiway(gateID);
    if(execution != Execution::Failed)
    {
        return Execution::Unecessary;
    }

    // Queue plane in taxiway
    execution = SlaveTerminal.PutPlaneOnTaxiway(gateID);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    return Execution::Passed;

}
//=============================================//
//	Departing Classes
//=============================================//
#pragma region -Departing gates-
#pragma region MANDATORY

#pragma region --- PING
cGate_Ping::cGate_Ping()
{
    expectedAmountOfParameters = PING_PARAM_COUNT;
    status = GateStatus::ReadyForDeparture;
    gateID = PING_PLANE_ID;
    maxSizeOfPlane = PING_PASSENGER_CAPACITY;
    built = true;
    _ping = false;
}
/// @brief Time base handler of the object.
/// @return 
Execution cGate_Ping::Update()
{
    // - Gate is waiting for the plane to come back - //
    if(status == GateStatus::AwaitingArrival)
    {
        timeLeftForArrival--;
        if(timeLeftForArrival == 0)
        {
            Device.SetErrorMessage("283:Gate -> PING FAILED       ");
            Device.SetStatus(Status::CommunicationError);
            return Execution::Failed;
        }
    }
    return Execution::Bypassed;
}
/**
 * @brief This method places the departing of a plane
 * into a departing buffer to be sent on the runway.
 * This function is called when the plane is taking off
 * and finished taxiing.
 * 
 * @param departingPlane 
 * Array of chunks where the packet will be placed
 * @param planeSize 
 * The size of the packet to send.
 * @return Execution 
 */
Execution cGate_Ping::_GetDepartingMasterPlane(unsigned short* departingPlane, int* planeSize)
{
    Execution execution;
    unsigned char convertedVariable[4];
    unsigned short temporaryBuffer[4];

    if(status != GateStatus::JustLeft)
    {
        Device.SetErrorMessage("207:Gates Inexisting plane    ");
        return Execution::Unecessary;
    }

    // Convert variable to passengers
    execution = Data.ToBytes(_ping, convertedVariable, 1);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("215:Gate -> Data.ToBytes      ");
        return Execution::Crashed;
    }

    // Convert passengers into seated passengers
    execution = Packet.GetParameterSegmentFromBytes(convertedVariable, temporaryBuffer, 1, 2);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("222:Gate -> Packet.GetParamSeg");
        return Execution::Crashed;
    }

    // Put the seated passengers in a plane.
    int resultedPacketSize = 4;
    execution = Packet.CreateFromSegments(gateID, temporaryBuffer, 4, departingPlane, resultedPacketSize);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("230:Gate -> Packet.CreateFromS");
        return Execution::Crashed;
    }

    *planeSize = 4;
    status = GateStatus::AwaitingArrival;
    timeLeftForArrival = TIMEOUT_DURATION_MS;
    return Execution::Passed;
}
/**
 * @brief Attempt to dock a plane
 * carrying the answer to the request
 * sent through the Request function.
 * 
 * @param planeID
 * The ID of the plane attempting to dock
 * @param planeToDock
 * Array of chunks.
 * @param planeSize 
 * Size of the plane (how big is the array of chunks)
 * @return Execution 
 */
Execution cGate_Ping::_DockSlavePlaneArrival(unsigned char planeID, unsigned short* planeToDock, int planeSize)
{
    Execution execution;
    unsigned char valuesArray[4];

    // Get the whole plane through TSA
    execution = _VerifyArrival(planeID, planeToDock, planeSize);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("262:Gate -> _VerifyArrival    ");
        return execution;
    }

    // Extract the passengers from the plane
    execution = Packet.GetBytes(planeToDock, planeSize, 1, valuesArray, 1);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("269:Gate -> Packet.GetBytes   ");
        return Execution::Failed;
    }

    // Get the variable from the passengers
    bool result;
    execution = Data.ToData(&result, valuesArray, 1);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("278:Gate -> Data.ToData       ");
        return Execution::Crashed;
    }

    // Holy shit data should be good here riiight?
    _ping = result;
    status = GateStatus::AvailableArrival;



    return Execution::Passed;   
}
/**
 * @brief Attempt to dock a function
 * request to this gate.
 * 
 * @param planeID
 * The ID of the plane attempting to dock
 * @param planeToDock
 * Array of chunks.
 * @param planeSize 
 * Size of the plane (how big is the array of chunks)
 * @return Execution 
 */
Execution cGate_Ping::_DockMasterPlaneArrival(unsigned char planeID, unsigned short* planeToDock, int planeSize)
{
    Execution execution;
    unsigned char valuesArray[4];

    // Get the whole plane through TSA
    execution = _VerifyArrival(planeID, planeToDock, planeSize);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("316:Gate -> _VerifyArrival    ");
        return execution;
    }

    // Extract the passengers from the plane
    execution = Packet.GetBytes(planeToDock, planeSize, 1, valuesArray, 1);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("324:Gate -> Packet.GetBytes   ");
        return Execution::Failed;
    }

    // Get the variable from the passengers
    bool result;
    execution = Data.ToData(&result, valuesArray, 1);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("333:Gate -> Data.ToData       ");
        return Execution::Crashed;
    }

    // Holy shit data should be good here riiight?
    _receivedPing = result;
    status = GateStatus::AvailableArrival;

    // Can the plane taxi on the slave's runway?
    execution = _CanPlaneTaxiOnSlave();
    if(execution != Execution::Passed)
    {
        //Plane could not taxi on the departure taxiway :(
        return execution;
    }

    // Plane successfully started taxxing up to the runway!
    _ping = _pingToReply;
    return Execution::Passed;   
}
/**
 * @brief The method called to send a ping
 * function to the other device and await
 * the answer.
 * @return Execution::Passed =  ping is sending
 */
Execution cGate_Ping::Request(bool pingValue)
{
    Execution execution;

    // Can the plane taxi on da runway?
    execution = _CanPlaneTaxiOnMaster();
    if(execution != Execution::Passed)
    {
        //Plane could not taxi on the departure taxiway :(
        return execution;
    }

    // Plane successfully started taxxing up to the runway!
    _ping = _pingToReply;
    status = GateStatus::JustLeft;
    return Execution::Passed;
}
/**
 * @brief This reads if any passengers just
 * finished unloading from the plane.
 * @return Execution::Passed = Reading worked | Execution::Bypassed = Nothing to read.
 */
Execution cGate_Ping::Read(bool* resultedValue)
{
    if(status != GateStatus::AvailableArrival)
    {
        // There is no plane to get passengers from.
        return Execution::Bypassed;
    }

    // A plane is docked and passengers already went through TSA
    if(status == GateStatus::AvailableArrival)
    {
        *resultedValue = _receivedPing;
        status = GateStatus::ReadyForDeparture;
        return Execution::Passed;
    }

    // Literally impossible to reach but funny to leave
    return Execution::Crashed;
}
#pragma endregion

#pragma region --- Status
/// @brief Constructor
cGate_Status::cGate_Status()
{
    expectedAmountOfParameters = STATUS_PARAM_COUNT;
    status = GateStatus::ReadyForDeparture;
    gateID = STATUS_PLANE_ID;
    maxSizeOfPlane = STATUS_PASSENGER_CAPACITY;
    built = true;
    /*
    _status = Device.GetStatus();
    */
}
/// @brief Time base handler of the object.
/// @return 
Execution cGate_Status::Update()
{
    // - Gate is waiting for the plane to come back - //
    if(status == GateStatus::AwaitingArrival)
    {
        timeLeftForArrival--;
        if(timeLeftForArrival == 0)
        {
            Device.SetErrorMessage("502:Gate -> STATUS FAILED     ");
            Device.SetStatus(Status::CommunicationError);
            return Execution::Failed;
        }
    }
    return Execution::Bypassed;  
}
/**
 * @brief This method places the departing of a plane
 * into a departing buffer to be sent on the runway.
 * This function is called when the plane is taking off
 * and finished taxiing.
 * 
 * @param departingPlane 
 * Array of chunks where the packet will be placed
 * @param planeSize 
 * The size of the packet to send.
 * @return Execution 
 */
Execution cGate_Status::_GetDepartingMasterPlane(unsigned short* departingPlane, int* planeSize)
{
    Execution execution;
    unsigned char convertedVariable[4];
    unsigned short temporaryBuffer[5];

    if(status != GateStatus::JustLeft)
    {
        Device.SetErrorMessage("529:Gates Inexisting plane    ");
        return Execution::Unecessary;
    }

    // Convert variable to passengers
    execution = Data.ToBytes(_status, convertedVariable, 4);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("537:Gate -> Data.ToBytes      ");
        return Execution::Crashed;
    }

    // Convert passengers into seated passengers
    execution = Packet.GetParameterSegmentFromBytes(convertedVariable, temporaryBuffer, 4, 5);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("222:Gate -> Packet.GetParamSeg");
        return Execution::Crashed;
    }

    // Put the seated passengers in a plane.
    int resultedPacketSize = 7;
    execution = Packet.CreateFromSegments(gateID, temporaryBuffer, 5, departingPlane, resultedPacketSize);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("554:Gate -> Packet.CreateFromS");
        return Execution::Crashed;
    }

    *planeSize = 4;
    status = GateStatus::AwaitingArrival;
    timeLeftForArrival = TIMEOUT_DURATION_MS;
    return Execution::Passed;
}
/**
 * @brief Attempt to dock a plane
 * carrying the answer to the request
 * sent through the Request function.
 * 
 * @param planeID
 * The ID of the plane attempting to dock
 * @param planeToDock
 * Array of chunks.
 * @param planeSize 
 * Size of the plane (how big is the array of chunks)
 * @return Execution 
 */
Execution cGate_Status::_DockSlavePlaneArrival(unsigned char planeID, unsigned short* planeToDock, int planeSize)
{
    Execution execution;
    unsigned char valuesArray[4];

    // Get the whole plane through TSA
    execution = _VerifyArrival(planeID, planeToDock, planeSize);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("585:Gate -> _VerifyArrival    ");
        return execution;
    }

    // Extract the passengers from the plane
    execution = Packet.GetBytes(planeToDock, planeSize, 1, valuesArray, 4);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("593:Gate -> Packet.GetBytes   ");
        return Execution::Failed;
    }

    // Get the variable from the passengers
    int result;
    execution = Data.ToData(&result, valuesArray, 4);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("602:Gate -> Data.ToData       ");
        return Execution::Crashed;
    }

    // Holy shit data should be good here riiight?
    _receivedStatus = result;
    status = GateStatus::AvailableArrival;

    return Execution::Passed;   
}
/**
 * @brief Attempt to dock a function
 * request to this gate.
 * 
 * @param planeID
 * The ID of the plane attempting to dock
 * @param planeToDock
 * Array of chunks.
 * @param planeSize 
 * Size of the plane (how big is the array of chunks)
 * @return Execution 
 */
Execution cGate_Status::_DockMasterPlaneArrival(unsigned char planeID, unsigned short* planeToDock, int planeSize)
{
    Execution execution;
    unsigned char valuesArray[4];

    // Get the whole plane through TSA
    execution = _VerifyArrival(planeID, planeToDock, planeSize);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("634:Gate -> _VerifyArrival    ");
        return execution;
    }

    // Extract the passengers from the plane
    execution = Packet.GetBytes(planeToDock, planeSize, 1, valuesArray, 4);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("642:Gate -> Packet.GetBytes   ");
        return Execution::Failed;
    }

    // Get the variable from the passengers
    bool result;
    execution = Data.ToData(&result, valuesArray, 4);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("651:Gate -> Data.ToData       ");
        return Execution::Crashed;
    }

    // Holy shit data should be good here riiight?
    _receivedStatus = result;
    status = GateStatus::AvailableArrival;

    // Can the plane taxi on the slave's runway?
    execution = _CanPlaneTaxiOnSlave();
    if(execution != Execution::Passed)
    {
        //Plane could not taxi on the departure taxiway :(
        return execution;
    }

    // Plane successfully started taxxing up to the runway!
    return Execution::Passed;   
}
/**
 * @brief The method called to send a status
 * function to the other device and await
 * the answer.
 * @return Execution::Passed = status is sending
 */
Execution cGate_Status::Request()
{
    Execution execution;

    // Can the plane taxi on da runway?
    execution = _CanPlaneTaxiOnMaster();
    if(execution != Execution::Passed)
    {
        //Plane could not taxi on the departure taxiway :(
        return execution;
    }

    // Plane successfully started taxxing up to the runway!
    Device.GetStatus(&_status);
    status = GateStatus::JustLeft;
    return Execution::Passed;
}
/**
 * @brief This reads if any passengers just
 * finished unloading from the plane.
 * @return Execution::Passed = Reading worked | Execution::Bypassed = Nothing to read.
 */
Execution cGate_Status::Read(int* resultedValue)
{
    if(status != GateStatus::AvailableArrival)
    {
        // There is no plane to get passengers from.
        return Execution::Bypassed;
    }

    // A plane is docked and passengers already went through TSA
    if(status == GateStatus::AvailableArrival)
    {
        *resultedValue = _receivedStatus;
        status = GateStatus::ReadyForDeparture;
        return Execution::Passed;
    }

    // Literally impossible to reach but funny to leave
    return Execution::Crashed;
}
#pragma endregion

#pragma region --- ID
/// @brief Constructor
cGate_ID::cGate_ID()
{
    expectedAmountOfParameters = ID_PARAM_COUNT;
    status = GateStatus::ReadyForDeparture;
    gateID = ID_PLANE_ID;
    maxSizeOfPlane = ID_PASSENGER_CAPACITY;
    built = true;
    /*
    _status = Device.GetStatus();
    */
}
/// @brief Time base handler of the object.
/// @return 
Execution cGate_ID::Update()
{
    // - Gate is waiting for the plane to come back - //
    if(status == GateStatus::AwaitingArrival)
    {
        timeLeftForArrival--;
        if(timeLeftForArrival == 0)
        {
            Device.SetErrorMessage("727:Gate -> ID FAILED         ");
            Device.SetStatus(Status::CommunicationError);
            return Execution::Failed;
        }
    }
    return Execution::Bypassed;  
}
/**
 * @brief This method places the departing of a plane
 * into a departing buffer to be sent on the runway.
 * This function is called when the plane is taking off
 * and finished taxiing.
 * 
 * @param departingPlane 
 * Array of chunks where the packet will be placed
 * @param planeSize 
 * The size of the packet to send.
 * @return Execution 
 */
Execution cGate_ID::_GetDepartingMasterPlane(unsigned short* departingPlane, int* planeSize)
{
    Execution execution;
    unsigned char convertedVariable[8];
    unsigned short temporaryBuffer[9];

    if(status != GateStatus::JustLeft)
    {
        Device.SetErrorMessage("754:Gates Inexisting plane    ");
        return Execution::Unecessary;
    }

    // Convert variable to passengers
    execution = Data.ToBytes(_ID, convertedVariable, 8);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("762:Gate -> Data.ToBytes      ");
        return Execution::Crashed;
    }

    // Convert passengers into seated passengers
    execution = Packet.GetParameterSegmentFromBytes(convertedVariable, temporaryBuffer, 8, 9);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("770:Gate -> Packet.GetParamSeg");
        return Execution::Crashed;
    }

    // Put the seated passengers in a plane.
    int resultedPacketSize = 9;
    execution = Packet.CreateFromSegments(gateID, temporaryBuffer, 9, departingPlane, resultedPacketSize);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("779:Gate -> Packet.CreateFromS");
        return Execution::Crashed;
    }

    *planeSize = 11;
    status = GateStatus::AwaitingArrival;
    timeLeftForArrival = TIMEOUT_DURATION_MS;
    return Execution::Passed;
}
/**
 * @brief Attempt to dock a plane
 * carrying the answer to the request
 * sent through the Request function.
 * 
 * @param planeID
 * The ID of the plane attempting to dock
 * @param planeToDock
 * Array of chunks.
 * @param planeSize 
 * Size of the plane (how big is the array of chunks)
 * @return Execution 
 */
Execution cGate_ID::_DockSlavePlaneArrival(unsigned char planeID, unsigned short* planeToDock, int planeSize)
{
    Execution execution;
    unsigned char valuesArray[8];

    // Get the whole plane through TSA
    execution = _VerifyArrival(planeID, planeToDock, planeSize);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("585:Gate -> _VerifyArrival    ");
        return execution;
    }

    // Extract the passengers from the plane
    execution = Packet.GetBytes(planeToDock, planeSize, 1, valuesArray, 8);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("818:Gate -> Packet.GetBytes   ");
        return Execution::Failed;
    }

    // Get the variable from the passengers
    int result;
    execution = Data.ToData(&result, valuesArray, 8);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("827:Gate -> Data.ToData       ");
        return Execution::Crashed;
    }

    // Holy shit data should be good here riiight?
    _receivedID = result;
    status = GateStatus::AvailableArrival;

    return Execution::Passed;   
}
/**
 * @brief Attempt to dock a function
 * request to this gate.
 * 
 * @param planeID
 * The ID of the plane attempting to dock
 * @param planeToDock
 * Array of chunks.
 * @param planeSize 
 * Size of the plane (how big is the array of chunks)
 * @return Execution 
 */
Execution cGate_ID::_DockMasterPlaneArrival(unsigned char planeID, unsigned short* planeToDock, int planeSize)
{
    Execution execution;
    unsigned char valuesArray[8];

    // Get the whole plane through TSA
    execution = _VerifyArrival(planeID, planeToDock, planeSize);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("858:Gate -> _VerifyArrival    ");
        return execution;
    }

    // Extract the passengers from the plane
    execution = Packet.GetBytes(planeToDock, planeSize, 1, valuesArray, 8);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("866:Gate -> Packet.GetBytes   ");
        return Execution::Failed;
    }

    // Get the variable from the passengers
    bool result;
    execution = Data.ToData(&result, valuesArray, 8);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("875:Gate -> Data.ToData       ");
        return Execution::Crashed;
    }

    // Holy shit data should be good here riiight?
    _receivedID = result;
    status = GateStatus::AvailableArrival;

    // Can the plane taxi on the slave's runway?
    execution = _CanPlaneTaxiOnSlave();
    if(execution != Execution::Passed)
    {
        //Plane could not taxi on the departure taxiway :(
        return execution;
    }

    // Plane successfully started taxxing up to the runway!
    return Execution::Passed;   
}
/**
 * @brief The method called to send a status
 * function to the other device and await
 * the answer.
 * @return Execution::Passed = status is sending
 */
Execution cGate_ID::Request()
{
    Execution execution;

    // Can the plane taxi on da runway?
    execution = _CanPlaneTaxiOnMaster();
    if(execution != Execution::Passed)
    {
        //Plane could not taxi on the departure taxiway :(
        return execution;
    }

    // Plane successfully started taxxing up to the runway!
    /*
    Device.GetStatus(&_status);
    */
    status = GateStatus::JustLeft;
    return Execution::Passed;
}
/**
 * @brief This reads if any passengers just
 * finished unloading from the plane.
 * @return Execution::Passed = Reading worked | Execution::Bypassed = Nothing to read.
 */
Execution cGate_ID::Read(int* resultedValue)
{
    if(status != GateStatus::AvailableArrival)
    {
        // There is no plane to get passengers from.
        return Execution::Bypassed;
    }

    // A plane is docked and passengers already went through TSA
    if(status == GateStatus::AvailableArrival)
    {
        *resultedValue = _receivedID;
        status = GateStatus::ReadyForDeparture;
        return Execution::Passed;
    }

    // Literally impossible to reach but funny to leave
    return Execution::Crashed;
}
#pragma endregion

#pragma region --- UNIVERSAL INFO
/// @brief Constructor
cGate_UniversalInfo::cGate_UniversalInfo()
{
    expectedAmountOfParameters = UNIVERSALINFO_PARAM_COUNT;
    status = GateStatus::ReadyForDeparture;
    gateID = UNIVERSALINFO_PLANE_ID;
    maxSizeOfPlane = 100;
    built = true;
    /*
    Device.GetStatus(&_status);
    */
}
/// @brief Time base handler of the object.
/// @return 
Execution cGate_UniversalInfo::Update()
{
    // - Gate is waiting for the plane to come back - //
    if(status == GateStatus::AwaitingArrival)
    {
        timeLeftForArrival--;
        if(timeLeftForArrival == 0)
        {
            Device.SetErrorMessage("727:Gate -> ID FAILED         ");
            Device.SetStatus(Status::CommunicationError);
            return Execution::Failed;
        }
    }
    return Execution::Bypassed;  
}
/**
 * @brief This method places the departing of a plane
 * into a departing buffer to be sent on the runway.
 * This function is called when the plane is taking off
 * and finished taxiing.
 * 
 * @param departingPlane 
 * Array of chunks where the packet will be placed
 * @param planeSize 
 * The size of the packet to send.
 * @return Execution 
 */
Execution cGate_UniversalInfo::_GetDepartingMasterPlane(unsigned short* departingPlane, int* planeSize)
{
    Execution execution;
    unsigned char convertedVariable[8];
    unsigned short temporaryBuffer[9];

    if(status != GateStatus::JustLeft)
    {
        Device.SetErrorMessage("754:Gates Inexisting plane    ");
        return Execution::Unecessary;
    }

    // Convert variable to passengers
    execution = Data.ToBytes(_ID, convertedVariable, 8);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("762:Gate -> Data.ToBytes      ");
        return Execution::Crashed;
    }

    // Convert passengers into seated passengers
    execution = Packet.GetParameterSegmentFromBytes(convertedVariable, temporaryBuffer, 8, 9);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("770:Gate -> Packet.GetParamSeg");
        return Execution::Crashed;
    }

    // Put the seated passengers in a plane.
    int resultedPacketSize = 9;
    execution = Packet.CreateFromSegments(gateID, temporaryBuffer, 9, departingPlane, resultedPacketSize);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("779:Gate -> Packet.CreateFromS");
        return Execution::Crashed;
    }

    *planeSize = 11;
    status = GateStatus::AwaitingArrival;
    timeLeftForArrival = TIMEOUT_DURATION_MS;
    return Execution::Passed;
}
/**
 * @brief Attempt to dock a plane
 * carrying the answer to the request
 * sent through the Request function.
 * 
 * @param planeID
 * The ID of the plane attempting to dock
 * @param planeToDock
 * Array of chunks.
 * @param planeSize 
 * Size of the plane (how big is the array of chunks)
 * @return Execution 
 */
Execution cGate_UniversalInfo::_DockSlavePlaneArrival(unsigned char planeID, unsigned short* planeToDock, int planeSize)
{
    Execution execution;
    unsigned char valuesArray[8];

    // Get the whole plane through TSA
    execution = _VerifyArrival(planeID, planeToDock, planeSize);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("585:Gate -> _VerifyArrival    ");
        return execution;
    }

    // Extract the passengers from the plane
    execution = Packet.GetBytes(planeToDock, planeSize, 1, valuesArray, 8);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("818:Gate -> Packet.GetBytes   ");
        return Execution::Failed;
    }

    // Get the variable from the passengers
    int result;
    execution = Data.ToData(&result, valuesArray, 8);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("827:Gate -> Data.ToData       ");
        return Execution::Crashed;
    }

    // Holy shit data should be good here riiight?
    _receivedID = result;
    status = GateStatus::AvailableArrival;

    return Execution::Passed;   
}
/**
 * @brief Attempt to dock a function
 * request to this gate.
 * 
 * @param planeID
 * The ID of the plane attempting to dock
 * @param planeToDock
 * Array of chunks.
 * @param planeSize 
 * Size of the plane (how big is the array of chunks)
 * @return Execution 
 */
Execution cGate_UniversalInfo::_DockMasterPlaneArrival(unsigned char planeID, unsigned short* planeToDock, int planeSize)
{
    Execution execution;
    unsigned char valuesArray[8];

    // Get the whole plane through TSA
    execution = _VerifyArrival(planeID, planeToDock, planeSize);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("858:Gate -> _VerifyArrival    ");
        return execution;
    }

    // Extract the passengers from the plane
    execution = Packet.GetBytes(planeToDock, planeSize, 1, valuesArray, 8);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("866:Gate -> Packet.GetBytes   ");
        return Execution::Failed;
    }

    // Get the variable from the passengers
    bool result;
    execution = Data.ToData(&result, valuesArray, 8);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("875:Gate -> Data.ToData       ");
        return Execution::Crashed;
    }

    // Holy shit data should be good here riiight?
    _receivedID = result;
    status = GateStatus::AvailableArrival;

    // Can the plane taxi on the slave's runway?
    execution = _CanPlaneTaxiOnSlave();
    if(execution != Execution::Passed)
    {
        //Plane could not taxi on the departure taxiway :(
        return execution;
    }

    // Plane successfully started taxxing up to the runway!
    return Execution::Passed;   
}
/**
 * @brief The method called to send a status
 * function to the other device and await
 * the answer.
 * @return Execution::Passed = status is sending
 */
Execution cGate_UniversalInfo::Request()
{
  /*
    Execution execution;

    // Can the plane taxi on da runway?
    execution = _CanPlaneTaxiOnMaster();
    if(execution != Execution::Passed)
    {
        //Plane could not taxi on the departure taxiway :(
        return execution;
    }

    // Plane successfully started taxxing up to the runway!
    Device.GetStatus(&_status);
    status = GateStatus::JustLeft;
    */
    return Execution::Passed;
}
/**
 * @brief This reads if any passengers just
 * finished unloading from the plane.
 * @return Execution::Passed = Reading worked | Execution::Bypassed = Nothing to read.
 */
Execution cGate_UniversalInfo::Read()
{
  /*
    if(status != GateStatus::AvailableArrival)
    {
        // There is no plane to get passengers from.
        return Execution::Bypassed;
    }

    // A plane is docked and passengers already went through TSA
    if(status == GateStatus::AvailableArrival)
    {
        *resultedValue = _receivedID;
        status = GateStatus::ReadyForDeparture;
        return Execution::Passed;
    }

    // Literally impossible to reach but funny to leave
    */
    return Execution::Crashed;
}
#pragma endregion

#pragma endregion
#pragma endregion