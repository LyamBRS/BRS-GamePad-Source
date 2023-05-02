/*
    ############    ############     ##########
    ############    ############     ##########
              ##              ##   ## 
    ####    ##      ####    ##     ############
    ####    ##      ####    ##     ############
              ##              ##             ##
    ############    ####      ##   ##########
    ############    ####      ##   ##########

    Title: BFIO.h
    Author: Lyam
*/

#ifndef GATES_H
  #define GATES_H
//=============================================//
//	Includes
//=============================================//
#include "Globals.h"
//=============================================//
//	Global Variables
//=============================================//

//=============================================//
//	Defines
//=============================================//
#define PING_PARAM_COUNT 1
#define PING_PASSENGER_CAPACITY 4
#define PING_PLANE_ID 0

#define STATUS_PARAM_COUNT 1
#define STATUS_PASSENGER_CAPACITY 4
#define STATUS_PLANE_ID 1

#define TYPE_PARAM_COUNT 1
#define TYPE_PASSENGER_CAPACITY 4
#define TYPE_PLANE_ID 4

#define ERRORMESSAGE_PARAM_COUNT 1
#define ERRORMESSAGE_PASSENGER_CAPACITY 22
#define ERRORMESSAGE_PLANE_ID 3

#define ID_PARAM_COUNT 1
#define ID_PASSENGER_CAPACITY 10
#define ID_PLANE_ID 5

#define RESTART_PARAM_COUNT 0
#define RESTART_PASSENGER_CAPACITY 2
#define RESTART_PLANE_ID 6

#define UNIVERSALINFO_PARAM_COUNT 7
//#define UNIVERSALINFO_PASSENGER_CAPACITY 2 + 8 + 8 + 1 + 1 + str + str
#define UNIVERSALINFO_PLANE_ID 7

#define HANDLINGERROR_PARAM_COUNT 1
#define HANDLINGERROR_PASSENGER_CAPACITY 4
#define HANDLINGERROR_PLANE_ID 8
//=============================================//
//	Base Class
//=============================================//

/**
 * @brief class that is herited by departing
 * classes and serves as a foundation that all
 * of the classes that handles function departure
 * have.
 */
class cGateFoundation
 {       
    private:
           
    public:
        bool built = false;
        /////////////////////////////////////////
        /**
         * @brief The current status of the gate.
         * Is set automatically by this class.
         */
        GateStatus status = GateStatus::Initialised;

        /**
         * @brief The amount of parameters it is
         * expected to receive as an answer to the departure.
         * 
         * Defaults to 0
         */
        unsigned char expectedAmountOfParameters = 0;

        /**
         * @brief The BFIO function's ID. Or simplified;
         * the specific callsign planes must have to
         * dock at this gate.
         */
        unsigned char gateID = 0;

        /**
         * @brief Stores the maximum size the
         * plane that docks at this gate can reach.
         */
        unsigned char maxSizeOfPlane = 0;

        /**
         * @brief How long it should take until the plane
         * comes back to the gate with answer passengers
         */
        unsigned int arrivalTimeOutMS = 1000;
        /////////////////////////////////////////
        /**
         * @brief Get the status of this gate.
         * See GateStatus for possible values this can
         * return.
         * 
         * @param currentStatus
         * Pointer to where the status will be placed.
         * @return Execution 
         */
        Execution GetStatus(unsigned char* currentStatus);

        /**
         * @brief Function that verifies the arrival to make
         * sure its the correct plane that docked to the gate.
         * @param arrivedPacket 
         * @return Execution 
         */
        Execution _VerifyArrival(unsigned short* arrivedPacket);

        /**
         * @brief Function that Queues an error answer
         * on the taxiway as an answer to an impossible or
         * failed request
         * @param errorCode
         * Specific BFIO error code associated with what went wrong.
         * @return Execution 
         */
        Execution _SendErrorPlane(unsigned char errorCode);

        /**
         * @brief This function returns Execution::Passed if
         * the plane can leave the gate and taxi on the departure
         * taxiway. Otherwise, Execution::Failed is returned.
         * @return Execution 
         */
        Execution _CanPlaneTaxi();
 };

//=============================================//
//	Departing Classes
//=============================================//
#pragma region -Departing gates-
#pragma region MANDATORY


/**
 * @brief Class used to send a ping to the other device.
 * Call the Request method to initiate a ping request.
 */
class cDeparture_Ping: public cGateFoundation
{
  private:
      bool _ping = false;
  public:
      /// @brief Constructor
      cDeparture_Ping();

      /// @brief Time base handler of the ping class
      /// @return 
      Execution Update();

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
      Execution _GetPlaneContent(unsigned short* departingPlane, int* planeSize);

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
       * @brief The method called to send a ping
       * function to the other device and await
       * the answer.
       * @return Execution::Passed =  ping is sending
       */
      Execution Request(bool pingValue);

      /**
       * @brief The method called to send a ping
       * function to the other device and await
       * the answer.
       * @return Execution::Passed = Reading worked.
       */
      Execution Read(bool* resultedValue);
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