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
    Execution execution = 0;

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

}


/**
 * @brief This function returns Execution::Passed if
 * the plane can leave the gate and taxi on the departure
 * taxiway. Otherwise, Execution::Failed is returned.
 * @return Execution 
 */
Execution cGateFoundation::_CanPlaneTaxi()
{
    Execution execution = 0;

    if(status == GateStatus::ReadyForDeparture)
    {
        // Is the terminal available for planes?
        execution _AskMasterTerminalForDeparture(maxSizeOfPlane);
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
//=============================================//
//	Departing Classes
//=============================================//
#pragma region -Departing gates-
#pragma region MANDATORY

cDeparture_Ping::cDeparture_Ping()
{
    expectedAmountOfParameters = PING_PARAM_COUNT;
    status = GateStatus::ReadyForDeparture;
    gateID = PING_PLANE_ID;
    maxSizeOfPlane = PING_PASSENGER_CAPACITY;
    built = true;
    _ping = false;
}

/// @brief Time base handler of the ping class
/// @return 
Execution cDeparture_Ping::Update()
{
    if(status == GateStatus::AwaitingArrival)
    {
        // - CALCULATE TIMEOUT HERE - //
    }
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
Execution cDeparture_Ping::_GetPlaneContent(unsigned short* departingPlane, int* planeSize)
{
    Execution execution;
    unsigned char convertedVariable = {0};
    unsigned short temporaryBuffer[4];

    if(status != GateStatus::JustLeft)
    {
        Device.SetErrorMessage("Tried to get inexisting plane");
        return Execution::Unecessary;
    }

    // Convert variable to chunks
    execution = Data.ToBytes(_ping, convertedVariable, 1);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage(INTERNAL_BYTE_CONVERTION_FAIL);
        return Execution::Crashed;
    }

    execution = Packet.GetParameterSegmentFromBytes(convertedVariable, temporaryBuffer, 1, 1);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage(INTERNAL_PACKET_BUILDING_FAIL);
        return Execution::Crashed;
    }

    execution = Packet.CreateFromSegments(gateID, temporaryBuffer, 4, departingPlane, 4);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage(INTERNAL_PACKET_BUILDING_FAIL);
        return Execution::Crashed;
    }

    *planeSize = 4;
    status = GateStatus::AwaitingArrival;
    return Execution::Passed;
}

/**
 * @brief Attempt to dock a plane to this gate.
 * 
 * @param planeID
 * The ID of the plane to dock.
 * 
 * @param planeToDock
 * Array of chunks.
 * @param planeSize 
 * Size of the plane (how big is the array of chunks)
 * @return Execution 
 */
Execution cDeparture_Ping::_DockPlane(unsigned char planeID, unsigned short* planeToDock, int planeSize)
{
    Execution execution;

    // Basic arrival verifications. We don't want imposter planes.
    execution = _VerifyArrival(planeID, planeToDock, planeSize);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("Failed to verify plane arrival");
        return execution;
    }

    unsigned char valuesArray = {0};
    execution = Packet.GetParametersFromPacket(planeToDock, planeSize, valuesArray, 1);
    if(execution != Execution::Passed)
    {
        // Failed :(
        return Execution::Failed;
    }

    // Get the boolean passenger out of the plane
    bool result;
    execution = Data.ToData(&result, valuesArray, 1);
    if(execution != Execution::Passed)
    {
        Device.SetErrorMessage("Could not convert to boolean.");
        return Execution::Crashed;
    }

    // Holy shit data should be good here riiight?
    _ping = result;
    status = GateStatus::AvailableArrival;
    return Execution::Passed;
}

/**
 * @brief The method called to send a ping
 * function to the other device and await
 * the answer.
 * @return Execution::Passed = ping is on taxiway
 */
Execution cDeparture_Ping::Request(bool pingToSend)
{
    Execution execution;

    execution = _CanPlaneTaxi();
    if(execution != Execution::Passed)
    {
        //Plane could not taxi on the departure taxiway
        return execution;
    }

    // Plane successfully started taxxing up to the runway!
    _ping = pingToSend;
    status = GateStatus::JustLeft;
}

/**
 * @brief The method called to send a ping
 * function to the other device and await
 * the answer.
 * @return Execution::Passed = Reading worked.
 */
Execution cDeparture_Ping::Read(bool* resultedValue)
{
    if(status != GateStatus::AvailableArrival)
    {
        // There is no plane to get passengers from.
        return Execution::Bypassed;
    }

    // A plane is docked and passengers already went through the TSA
    if(status == GateStatus::AvailableArrival)
    {
        *resultedValue = _receivedPing;
        status = GateStatus::ReadyForDeparture;
        return Execution::Passed;
    }

    return Execution::Crashed;
}

/**
 * @brief Class used to get the status of the other device.
 * and update their saved status of your device aswell.
 * Call the Request method to initiate a ping request.
 */
class cDeparture_StatusUpdate: public cGateFoundation
{
  private:
      unsigned char _receivedStatus = false;
  public:
      /// @brief Constructor
      cDeparture_StatusUpdate();

      /// @brief Time base handler of the class
      /// @return 
      Execution Update();

      /**
       * @brief Attempt to dock a plane to this gate.
       * 
       * @param planeToDock
       * Array of chunks.
       * @param planeSize 
       * Size of the plane (how big is the array of chunks)
       * @return Execution 
       */
      Execution _DockPlane(unsigned short* planeToDock, int planeSize);

      /**
       * @brief The method called to send a
       * function to the other device and await
       * the answer.
       * 
       * @attention
       * This sends Device.Status
       * @return Execution::Passed =  ping is sending
       */
      Execution Request();

      /**
       * @brief The method called to read the other
       * device's answer to the function that was requested
       * the answer.
       * @return Execution::Passed = Reading worked.
       */
      Execution Read(unsigned char* resultedStatus);
}

/**
 * @brief Class used to update the error message
 * saved on other devices aswell as get theirs.
 * Call the Request method to initiate an error
 * message update request.
 */
class cDeparture_ErrorMessageUpdate: public cGateFoundation
{
  private:
      std::string _receivedMessage = false;
  public:
      /// @brief Constructor
      cDeparture_ErrorMessageUpdate();

      /// @brief Time base handler of the class
      /// @return 
      Execution Update();

      /**
       * @brief Attempt to dock a plane to this gate.
       * 
       * @param planeToDock
       * Array of chunks.
       * @param planeSize 
       * Size of the plane (how big is the array of chunks)
       * @return Execution 
       */
      Execution _DockPlane(unsigned short* planeToDock, int planeSize);

      /**
       * @brief The method called to send a
       * function to the other device and await
       * the answer.
       * 
       * @attention
       * This sends Device.errormessage automatically
       * @return Execution::Passed = plane is now on taxiway
       */
      Execution Request();

      /**
       * @brief The method called to read the other
       * device's answer to the function that was requested
       * the answer.
       * @return Execution::Passed = Reading worked.
       */
      Execution Read(std::string& resultedStatus);
}

/**
 * @brief Class used to update the type
 * saved on other devices aswell as get theirs.
 * Call the Request method to initiate a type
 * update request.
 */
class cDeparture_TypeUpdate: public cGateFoundation
{
  private:
      unsigned char _receivedType = 0;
  public:
      /// @brief Constructor
      cDeparture_TypeUpdate();

      /// @brief Time base handler of the class
      /// @return 
      Execution Update();

      /**
       * @brief Attempt to dock a plane to this gate.
       * 
       * @param planeToDock
       * Array of chunks.
       * @param planeSize 
       * Size of the plane (how big is the array of chunks)
       * @return Execution 
       */
      Execution _DockPlane(unsigned short* planeToDock, int planeSize);

      /**
       * @brief The method called to send a
       * function to the other device and await
       * the answer.
       * 
       * @attention
       * This sends Device.type automatically
       * @return Execution::Passed = plane is now on taxiway
       */
      Execution Request();

      /**
       * @brief The method called to read the other
       * device's answer to the function that was requested
       * the answer.
       * @return Execution::Passed = Reading worked.
       */
      Execution Read(unsigned char* resultedType);
}

/**
 * @brief Class used to update the ID
 * saved on other devices aswell as get theirs.
 * Call the Request method to initiate an ID
 * update request.
 */
class cDeparture_IDUpdate: public cGateFoundation
{
  private:
      unsigned long long _receivedID = 0;
  public:
      /// @brief Constructor
      cDeparture_IDUpdate();

      /// @brief Time base handler of the class
      /// @return 
      Execution Update();

      /**
       * @brief Attempt to dock a plane to this gate.
       * 
       * @param planeToDock
       * Array of chunks.
       * @param planeSize 
       * Size of the plane (how big is the array of chunks)
       * @return Execution 
       */
      Execution _DockPlane(unsigned short* planeToDock, int planeSize);

      /**
       * @brief The method called to send a
       * function to the other device and await
       * the answer.
       * 
       * @attention
       * This sends Device.type automatically
       * @return Execution::Passed = plane is now on taxiway
       */
      Execution Request();

      /**
       * @brief The method called to read the other
       * device's answer to the function that was requested
       * the answer.
       * @return Execution::Passed = Reading worked.
       */
      Execution Read(unsigned long long* resultedID);
}

/**
 * @brief Class used to request a reset of 
 * the other device's protocol functions as well
 * as saved parameters
 */
class cDeparture_RestartProtocol: public cGateFoundation
{
  private:
      bool _acknowledged = 0;
  public:
      /// @brief Constructor
      cDeparture_RestartProtocol();

      /// @brief Time base handler of the class
      /// @return 
      Execution Update();

      /**
       * @brief Attempt to dock a plane to this gate.
       * 
       * @param planeToDock
       * Array of chunks.
       * @param planeSize 
       * Size of the plane (how big is the array of chunks)
       * @return Execution 
       */
      Execution _DockPlane(unsigned short* planeToDock, int planeSize);

      /**
       * @brief The method called to send a
       * function to the other device and await
       * the answer.
       * 
       * @attention
       * This sends Device.type automatically
       * @return Execution::Passed = plane is now on taxiway
       */
      Execution Request();

      /**
       * @brief The method called to read the other
       * device's answer to the function that was requested
       * the answer.
       * @return Execution::Passed = Reading worked.
       */
      Execution Read(bool* acknowledgment);
}

/**
 * @brief Class used to request an update of 
 * the other device's saved universal information as well
 * update your device's saved information about that device.
 */
class cDeparture_UniversalInfosUpdate: public cGateFoundation
{
  private:
      unsigned long long* _receivedID = 0;
      unsigned long long* _receivedBFIOVersion = 0;
      unsigned char* _receivedType = 0;
      unsigned char* _receivedStatus = 0;
      std::string _receivedGitRepository = "";
      std::string _receivedDeviceName = "";
      std::string _receivedDeviceVersion = "";
  public:
      /// @brief Constructor
      cDeparture_UniversalInfosUpdate();

      /// @brief Time base handler of the class
      /// @return 
      Execution Update();

      /**
       * @brief Attempt to dock a plane to this gate.
       * 
       * @param planeToDock
       * Array of chunks.
       * @param planeSize 
       * Size of the plane (how big is the array of chunks)
       * @return Execution 
       */
      Execution _DockPlane(unsigned short* planeToDock, int planeSize);

      /**
       * @brief The method called to send a
       * function to the other device and await
       * the answer.
       * 
       * @attention
       * This sends informations automatically.
       * @return Execution::Passed = plane is now on taxiway
       */
      Execution Request();

      /**
       * @brief The method called to read the other
       * device's answer to the function that was requested
       * the answer.
       * @return Execution::Passed = Reading worked.
       */
      Execution Read(unsigned long long* receivedID, unsigned long long* receivedBFIOVersion, unsigned char* receivedType, unsigned char* receivedStatus, std::string& receivedGitRepository, std::string& receivedDeviceName, std::string& receivedDeviceVersion);
}
#pragma endregion
#pragma endregion
//=============================================//
//	Arrival Classes
//=============================================//
#pragma region -Arrival Gates-
#pragma endregion

#endif