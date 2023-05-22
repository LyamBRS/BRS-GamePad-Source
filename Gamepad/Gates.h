/*
    ############    ############     ##########
    ############    ############     ##########
              ##              ##   ## 
    ####    ##      ####    ##     ############
    ####    ##      ####    ##     ############
              ##              ##             ##
    ############    ####      ##   ##########
    ############    ####      ##   ##########

    Title: Gates.h
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
        GateStatus status = GateStatus::Cleaned;

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
        unsigned int timeLeftForArrival = 1000;
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
        Execution _VerifyArrival(unsigned char planeID, unsigned short* arrivedPlane, int planeSize);

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
        Execution _CanPlaneTaxiOnMaster();

        /**
         * @brief This function returns Execution::Passed if
         * the plane can leave the gate and taxi on the departure
         * taxiway. Otherwise, Execution::Failed is returned.
         * @return Execution 
         */
        Execution _CanPlaneTaxiOnSlave();
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
class cGate_Ping: public cGateFoundation
{
  private:
        /// @brief The ping to send in requests
        bool _ping = false;
        /// @brief The ping received from any terminals
        bool _receivedPing = false;
        /// @brief The ping to reply to the other airport's master terminal.
        bool _pingToReply = true;
  public:
    bool built = false;
    /// @brief Constructor
    cGate_Ping();
    /// @brief Time base handler of the object.
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
    Execution _GetDepartingMasterPlane(unsigned short* departingPlane, int* planeSize);
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
    Execution _DockSlavePlaneArrival(unsigned char planeID, unsigned short* planeToDock, int planeSize);

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
    Execution _DockMasterPlaneArrival(unsigned char planeID, unsigned short* planeToDock, int planeSize);

    /**
     * @brief The method called to send a ping
     * function to the other device and await
     * the answer.
     * @return Execution::Passed =  ping is sending
     */
    Execution Request(bool pingValue);
    /**
     * @brief This reads if any passengers just
     * finished unloading from the plane.
     * @return Execution::Passed = Reading worked | Execution::Bypassed = Nothing to read.
     */
    Execution Read(bool* resultedValue);
};
/**
 * @brief Class used to send a status to the other device.
 * Call the Request method to initiate a status request.
 */
class cGate_Status: public cGateFoundation
{
  private:
        /// @brief The status to send in requests
        int _status = 0;
        /// @brief The status received from any terminals
        int _receivedStatus = 0;
        /// @brief The status to reply to the other airport's master terminal.
        int _statusToReply = 0;
  public:
    bool built = false;
    /// @brief Constructor
    cGate_Status();
    /// @brief Time base handler of the object.
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
    Execution _GetDepartingMasterPlane(unsigned short* departingPlane, int* planeSize);
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
    Execution _DockSlavePlaneArrival(unsigned char planeID, unsigned short* planeToDock, int planeSize);

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
    Execution _DockMasterPlaneArrival(unsigned char planeID, unsigned short* planeToDock, int planeSize);

    /**
     * @brief The method called to send a status
     * function to the other device and await
     * the answer.
     * @return Execution::Passed = status is sending
     */
    Execution Request();
    /**
     * @brief This reads if any passengers just
     * finished unloading from the plane.
     * @return Execution::Passed = Reading worked | Execution::Bypassed = Nothing to read.
     */
    Execution Read(int* resultedValue);
};

/**
 * @brief Class used to send an ID to the other device.
 * Call the Request method to initiate a status request.
 */
class cGate_ID: public cGateFoundation
{
  private:
        /// @brief The status to send in requests
        unsigned long long _ID = 2023050910180001;
        /// @brief The status received from any terminals
        unsigned long long _receivedID = 0;
        /// @brief The status to reply to the other airport's master terminal.
        unsigned long long _IDToSend = 0;
  public:
    bool built = false;
    /// @brief Constructor
    cGate_ID();
    /// @brief Time base handler of the object.
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
    Execution _GetDepartingMasterPlane(unsigned short* departingPlane, int* planeSize);
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
    Execution _DockSlavePlaneArrival(unsigned char planeID, unsigned short* planeToDock, int planeSize);

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
    Execution _DockMasterPlaneArrival(unsigned char planeID, unsigned short* planeToDock, int planeSize);

    /**
     * @brief The method called to send a status
     * function to the other device and await
     * the answer.
     * @return Execution::Passed = status is sending
     */
    Execution Request();
    /**
     * @brief This reads if any passengers just
     * finished unloading from the plane.
     * @return Execution::Passed = Reading worked | Execution::Bypassed = Nothing to read.
     */
    Execution Read(int* resultedValue);
};
/**
 * @brief Class used to send an universal to the other device.
 * Call the Request method to initiate a status request.
 */
class cGate_UniversalInfo: public cGateFoundation
{
  private:
        /// @brief The status to send in requests
        unsigned long long _ID = 2023050910180001;
        /// @brief The status received from any terminals
        unsigned long long _receivedID = 0;
        /// @brief The status to reply to the other airport's master terminal.
        unsigned long long _IDToSend = 2023050910180001;

        /// @brief The status to send in requests
        unsigned long long _BFIOID = BFIO_VERSION_ID;
        /// @brief The status received from any terminals
        unsigned long long _receivedBFIO = 0;
        /// @brief The status to reply to the other airport's master terminal.
        unsigned long long _BFIOToSend = 0;

        /// @brief The status to send in requests
        unsigned char _type = 0;
        /// @brief The status received from any terminals
        unsigned char _receivedType = 0;
        /// @brief The status to reply to the other airport's master terminal.
        unsigned char _typeToSend = 0;

        /// @brief The status to send in requests
        unsigned char _status = 0;
        /// @brief The status received from any terminals
        unsigned char _receivedStatus = 0;
        /// @brief The status to reply to the other airport's master terminal.
        unsigned char _statusToSend = 0;

        /// @brief The status to send in requests
        std::string _gitRepository = "";//BFIO_GIT_REPOSITORY;
        /// @brief The status received from any terminals
        std::string _receivedGitRepository = 0;
        /// @brief The status to reply to the other airport's master terminal.
        std::string _repositoryToSend = "";//BFIO_GIT_REPOSITORY;

        /// @brief The status to send in requests
        std::string _nameOfDevice = "";//EVICE_NAME;
        /// @brief The status received from any terminals
        std::string _receivedDeviceName = 0;
        /// @brief The status to reply to the other airport's master terminal.
        std::string _deviceNameToSend = "";//DEVICE_NAME;
  public:
    bool built = false;
    /// @brief Constructor
    cGate_UniversalInfo();
    /// @brief Time base handler of the object.
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
    Execution _GetDepartingMasterPlane(unsigned short* departingPlane, int* planeSize);
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
    Execution _DockSlavePlaneArrival(unsigned char planeID, unsigned short* planeToDock, int planeSize);

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
    Execution _DockMasterPlaneArrival(unsigned char planeID, unsigned short* planeToDock, int planeSize);

    /**
     * @brief The method called to send a status
     * function to the other device and await
     * the answer.
     * @return Execution::Passed = status is sending
     */
    Execution Request();
    /**
     * @brief This reads if any passengers just
     * finished unloading from the plane.
     * @return Execution::Passed = Reading worked | Execution::Bypassed = Nothing to read.
     */
    Execution Read();
};

#pragma endregion
#pragma endregion
#endif