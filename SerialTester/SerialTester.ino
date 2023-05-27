/*
    ############    ############     ##########
    ############    ############     ##########
              ##              ##   ## 
    ####    ##      ####    ##     ############
    ####    ##      ####    ##     ############
              ##              ##             ##
    ############    ####      ##   ##########
    ############    ####      ##   ##########

    Title: main.c
    Author: Lyam
*/

//================================================================================================//
#pragma region Includes
#include <SoftwareSerial.h>
#include "Globals.h"
#include "_UNIT_TEST.h"
#pragma endregion
//================================================================================================//

// Define the GPIO pins for each Serial port

#define SERIAL1_TX_PIN 18   // GPIO47 for Serial1 TX
#define SERIAL1_RX_PIN 17   // GPIO48 for Serial1 RX
#define MAX_PLANE_SIZE 40

EspSoftwareSerial::UART kontrolToGamepad;

void setup() {

  InitializeProject();

  Rgb.SetColors(255,255,255);
  for (unsigned int timeSpent = 0; timeSpent < 1000; timeSpent++)
  {
    Rgb.Update();
    delay(0.01);
  }

  Rgb.SetColors(0,0,0);
  for (unsigned int timeSpent = 0; timeSpent < 1000; timeSpent++)
  {
    Rgb.Update();
    delay(0.01);
  }
  
  // Start Serial communication on Serial1
  kontrolToGamepad.begin(9600, SWSERIAL_8N1, SERIAL1_RX_PIN, SERIAL1_TX_PIN, false);
  if (!kontrolToGamepad) { // If the object did not initialize, then its configuration is invalid
    Rgb.SetColors(255,0,255);
    Rgb.SetErrorMode(2,100,500);
    // Serial.println("Invalid EspSoftwareSerial pin configuration, check config"); 
    while (1) { // Don't continue with invalid configuration
      delay (0.01);
      Rgb.Update();
    }
  }  
}



unsigned char UniversalInformationPlane[180] = {2,7,1,0,0,121,0,49,0,64,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0,104,0,116,0,116,0,112,0,115,0,58,0,47,0,47,0,103,0,105,0,116,0,104,0,117,0,98,0,46,0,99,0,111,0,109,0,47,0,76,0,121,0,97,0,109,0,66,0,82,0,83,0,47,0,66,0,114,0,83,0,112,0,97,0,110,0,100,0,95,0,71,0,97,0,109,0,101,0,80,0,97,0,100,0,46,0,103,0,105,0,116,1,0,0,71,0,97,0,109,0,101,0,80,0,97,0,100,1,0,0,82,0,101,0,118,0,32,0,65,3,173};
unsigned char receivedPassengers[200];
unsigned char uartBytesToSend[100];
unsigned short hardwarePlane[37];
bool planeLanding = false;
bool receivingLuggage = false;
bool waitingForCheckSum = false;
bool planeLanded = false;
bool handshaken = false;
bool sendControls = false;
int currentPlaneSize = 0;

unsigned short leftJoystickXaxisPassengers[5];   // Buffer of 1 flight attendant and 4 passenger
unsigned short leftJoystickYaxisPassengers[5];   // Buffer of 1 flight attendant and 4 passenger
unsigned short leftJoystickButtonPassengers[2];  // Buffer of 1 flight attendant and 1 passenger

unsigned short rightJoystickXaxisPassengers[5];
unsigned short rightJoystickYaxisPassengers[5];
unsigned short rightJoystickButtonPassengers[2];

unsigned short switch1Passengers[2];
unsigned short switch2Passengers[2];
unsigned short switch3Passengers[2];
unsigned short switch4Passengers[2];
unsigned short switch5Passengers[2];

unsigned char leftJoystickXaxisLuggage[4];
unsigned char leftJoystickYaxisLuggage[4];
unsigned char leftJoystickButtonLuggage[1];

unsigned char rightJoystickXaxisLuggage[4];
unsigned char rightJoystickYaxisLuggage[4];
unsigned char rightJoystickButtonLuggage[1];

unsigned char switch1Luggage[1];
unsigned char switch2Luggage[1];
unsigned char switch3Luggage[1];
unsigned char switch4Luggage[1];
unsigned char switch5Luggage[1];

unsigned short temporaryBufferA[37]; // Used to append passengers segments toghether
unsigned short temporaryBufferB[37]; // used to append passengers segments toghether
unsigned short boardedPassengers[34]; // Used to put all the passengers before boarding the pilot and co-pilot

int leftJoystickXaxis = 0;
int leftJoystickYaxis = 0;

int rightJoystickXaxis = 0;
int rightJoystickYaxis = 0;

bool leftJoystickButton = false;
bool rightJoystickButton = false;

bool switch1 = false;
bool switch2 = false;
bool switch3 = false;
bool switch4 = false;
bool switch5 = false;

/**
 * @brief Interface that clears the runway
 * of anything saved.
 */
void ClearRunway()
{
  currentPlaneSize = 0;
  receivingLuggage = 0;
  waitingForCheckSum = 0;
  for(int index = 0; index<200; index++)
  {
    receivedPassengers[index] = 0;
  }
}

/**
 * @brief Interface that handles data received when
 * the data is a passenger.
 * @param passenger 
 */
void HandlePassengerLuggage(unsigned char passenger)
{
  if(receivingLuggage && planeLanding)
  {
    receivedPassengers[currentPlaneSize] = passenger;
    currentPlaneSize++;
    receivingLuggage = false;

    if(waitingForCheckSum)
    {
      waitingForCheckSum = false;
      receivingLuggage = false;
      planeLanding = false;
      planeLanded = true;
    }
  }
}

/**
 * @brief Interface that handles data received
 * when the current data is a passenger type.
 * @param passengerType 
 */
void HandlePassengerType(unsigned char passengerType)
{
  if(!receivingLuggage)
  {
    // passenger to come is a pilot 
    if(!planeLanding && passengerType == 2 && !receivingLuggage)
    {
      planeLanding = true;
      ClearRunway();
      receivedPassengers[currentPlaneSize] = 2;
      currentPlaneSize++;
      receivingLuggage = true;
      waitingForCheckSum = true;
      return;
    }

    // next passenger is a co-pilot
    if(planeLanding && passengerType == 3 && !receivingLuggage)
    {
      ClearRunway();
      receivedPassengers[currentPlaneSize] = 3;
      currentPlaneSize++;
      receivingLuggage = true;
      return;
    }

    // next passenger is a passenger
    if(planeLanding && passengerType == 0 && !receivingLuggage)
    {
      ClearRunway();
      receivedPassengers[currentPlaneSize] = 0;
      currentPlaneSize++;
      receivingLuggage = true;
      return;
    }

    // next passenger is a flight attendant.
    if(planeLanding && passengerType == 1 && !receivingLuggage)
    {
      ClearRunway();
      receivedPassengers[currentPlaneSize] = 1;
      currentPlaneSize++;
      receivingLuggage = true;
      return;
    }
  }
}

/**
 * @brief Interface that surounds the hardware pilot
 */
void HandleReceivedMasterData()
{
  if (kontrolToGamepad.available())
  {
    Device.SetStatus(Status::Busy);
    unsigned char currentByte = kontrolToGamepad.read();

    if(!planeLanding || !receivingLuggage)
    {
      HandlePassengerType(currentByte);
    }
    else
    {
      HandlePassengerLuggage(currentByte);
    }
  }
}

/**
 * @brief Interface that calls the update
 * methods of hardware objects to get
 * their latests values.
 */
void UpdateAllControls()
{
  LeftJoystick.Update();
  RightJoystick.Update();
  Button1.Update();
  Button2.Update();
  Button3.Update();
  Button4.Update();
  Button5.Update();
}
#pragma region ------------------------- Plane callsign identification
/**
 * @brief Interface that analyze the plane saved
 * and returns values depending on its callsign.
 * @return true = The plane is an handshake request.
 * @return false = The plane is not an handshake request.
 */
bool PlaneIsAnHandshake()
{
  if(planeLanded)
  {
    planeLanded = false;
    if(receivedPassengers[1] == 7)
    {
      handshaken = true;
      return true;
    }
    else
    {
      return false;
    }
  }
  return false;
}

/**
 * @brief Interface that analyze the plane saved
 * and returns values depending on its callsign.
 * @return true = The plane is an hardware request.
 * @return false = The plane is not an hardware request.
 */
bool PlaneIsAnHardwareRequest()
{
  if(planeLanded)
  {
    planeLanded = false;
    if(receivedPassengers[1] == 20)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  return false;
}
#pragma endregion
/**
 * @brief Interface that calls the UART pilot
 * and sends the universal information buffer.
 */
void SendUniversalInfo()
{
  for(int index = 0; index < 170; index++)
  {
    kontrolToGamepad.write(UniversalInformationPlane[index]);
  }
}

#pragma region ------------------------- RGB handlers
/**
 * @brief Interface that handles the
 * RGB light colors to show a pulsating
 * orange light when we're handshaking.
 */
void ShowHandshakingRGB()
{
  Rgb.SetMode(1);
  Rgb.SetAnimations(255, 1000, 4);
  Rgb.SetColors(255,128,0);
}

/**
 * @brief Interface that displays
 * regular RGB lights colors
 */
void ShowRegularRGB()
{
  Rgb.SetMode(2);
  Rgb.SetColors(0,128,0);
}
#pragma endregion

#pragma region ------------------------- Hardware plane building
/**
 * @brief Pilot that directly extracts values from
 * the hardware objects.
 */
void ExtractVariablesFromHardware()
{
  Execution result;
  ////////////////////////////////////
  result = LeftJoystick.GetEverything(&leftJoystickXaxis, &leftJoystickYaxis, &leftJoystickButton);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("268: LeftJoystick");
    Device.SetStatus(Status::CommunicationError);
  }
  ////////////////////////////////////
  result = RightJoystick.GetEverything(&rightJoystickXaxis, &rightJoystickYaxis, &rightJoystickButton);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("275: RightJoystick");
    Device.SetStatus(Status::CommunicationError);
  }
  ////////////////////////////////////
  result = Button1.GetLatestValue(&switch1);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("282: Button1");
    Device.SetStatus(Status::CommunicationError);
  }
  ////////////////////////////////////
  result = Button2.GetLatestValue(&switch2);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("289: Button2");
    Device.SetStatus(Status::CommunicationError);
  }
  ////////////////////////////////////
  result = Button3.GetLatestValue(&switch3);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("296: Button3");
    Device.SetStatus(Status::CommunicationError);
  }
  ////////////////////////////////////
  result = Button4.GetLatestValue(&switch4);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("303: Button4");
    Device.SetStatus(Status::CommunicationError);
  }
  ////////////////////////////////////
  result = Button5.GetLatestValue(&switch5);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("310: Button5");
    Device.SetStatus(Status::CommunicationError);
  }
}

#pragma region ------------------------- Luggage convertions
void ConvertLeftJoystickToLuggages()
{
  Execution result;
  //////////////////////////////
  result = Data.ToBytes(&leftJoystickXaxis, leftJoystickXaxisLuggage, 4);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("323: Data.ToBytes");
    Device.SetStatus(Status::CommunicationError);
  }
  //////////////////////////////
  result = Data.ToBytes(&leftJoystickYaxis, leftJoystickYaxisLuggage, 4);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("330: Data.ToBytes");
    Device.SetStatus(Status::CommunicationError);
  }
  //////////////////////////////
  result = Data.ToBytes(&leftJoystickButton, leftJoystickButtonLuggage, 1);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("337: Data.ToBytes");
    Device.SetStatus(Status::CommunicationError);
  }
}

void ConvertRightJoystickToLuggages()
{
  Execution result;
  //////////////////////////////
  result = Data.ToBytes(&rightJoystickXaxis, rightJoystickXaxisLuggage, 4);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("349: Data.ToBytes");
    Device.SetStatus(Status::CommunicationError);
  }
  //////////////////////////////
  result = Data.ToBytes(&rightJoystickYaxis, rightJoystickYaxisLuggage, 4);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("356: Data.ToBytes");
    Device.SetStatus(Status::CommunicationError);
  }
  //////////////////////////////
  result = Data.ToBytes(&rightJoystickButton, rightJoystickButtonLuggage, 1);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("363: Data.ToBytes");
    Device.SetStatus(Status::CommunicationError);
  }
}

void ConvertSwitchesToLuggage()
{
  Execution result;
  //////////////////////////////
  result = Data.ToBytes(&switch1, switch1Luggage, 1);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("375: Data.ToBytes");
    Device.SetStatus(Status::CommunicationError);
  }
  //////////////////////////////
  result = Data.ToBytes(&switch2, switch2Luggage, 1);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("382: Data.ToBytes");
    Device.SetStatus(Status::CommunicationError);
  }
  //////////////////////////////
  result = Data.ToBytes(&switch3, switch3Luggage, 1);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("389: Data.ToBytes");
    Device.SetStatus(Status::CommunicationError);
  }
  //////////////////////////////
  result = Data.ToBytes(&switch4, switch4Luggage, 1);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("396: Data.ToBytes");
    Device.SetStatus(Status::CommunicationError);
  }
  //////////////////////////////
  result = Data.ToBytes(&switch5, switch5Luggage, 1);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("403: Data.ToBytes");
    Device.SetStatus(Status::CommunicationError);
  }
}

/**
 * @brief Interface that converts hardware to
 * luggages to be later assigned to passengers.
 */
void ConvertVariablesToLuggage()
{
  ConvertLeftJoystickToLuggages();
  ConvertRightJoystickToLuggages();
  ConvertSwitchesToLuggage();
}
#pragma endregion

#pragma region ------------------------- Passenger classes convertions
/**
 * @brief Function that generates segments 
 * from the left joystick values
 */
void AssignLeftJoystickLuggageToPassengers()
{
  Execution result;
  //////////////////////////////////////////
  result = Packet.GetParameterSegmentFromBytes(leftJoystickXaxisLuggage, leftJoystickXaxisPassengers, 4, 5);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("439: Packet.GetParameterSegmentFromBytes");
    Device.SetStatus(Status::CommunicationError);
  }
  //////////////////////////////////////////
  result = Packet.GetParameterSegmentFromBytes(leftJoystickYaxisLuggage, leftJoystickYaxisPassengers, 4, 5);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("446: Packet.GetParameterSegmentFromBytes");
    Device.SetStatus(Status::CommunicationError);
  }
  //////////////////////////////////////////
  result = Packet.GetParameterSegmentFromBytes(leftJoystickButtonLuggage, leftJoystickButtonPassengers, 1, 2);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("453: Packet.GetParameterSegmentFromBytes");
    Device.SetStatus(Status::CommunicationError);
  }
}
/**
 * @brief Function that generates segments 
 * from the right joystick values
 */
void AssignRightJoystickLuggageToPassengers()
{
  Execution result;
  //////////////////////////////////////////
  result = Packet.GetParameterSegmentFromBytes(rightJoystickXaxisLuggage, rightJoystickXaxisPassengers, 4, 5);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("465: Packet.GetParameterSegmentFromBytes");
    Device.SetStatus(Status::CommunicationError);
  }
  //////////////////////////////////////////
  result = Packet.GetParameterSegmentFromBytes(rightJoystickYaxisLuggage, rightJoystickYaxisPassengers, 4, 5);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("472: Packet.GetParameterSegmentFromBytes");
    Device.SetStatus(Status::CommunicationError);
  }
  //////////////////////////////////////////
  result = Packet.GetParameterSegmentFromBytes(rightJoystickButtonLuggage, rightJoystickButtonPassengers, 1, 2);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("479: Packet.GetParameterSegmentFromBytes");
    Device.SetStatus(Status::CommunicationError);
  }
}
/**
 * @brief Function that generates segments 
 * from the switches values
 */
void AssignSwitchesLuggageToPassengers()
{
  Execution result;
  //////////////////////////////////////////
  result = Packet.GetParameterSegmentFromBytes(switch1Luggage, switch1Passengers, 1, 2);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("491: Packet.GetParameterSegmentFromBytes");
    Device.SetStatus(Status::CommunicationError);
  }
  //////////////////////////////////////////
  result = Packet.GetParameterSegmentFromBytes(switch2Luggage, switch2Passengers, 1, 2);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("498: Packet.GetParameterSegmentFromBytes");
    Device.SetStatus(Status::CommunicationError);
  }
  //////////////////////////////////////////
  result = Packet.GetParameterSegmentFromBytes(switch3Luggage, switch3Passengers, 1, 2);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("505: Packet.GetParameterSegmentFromBytes");
    Device.SetStatus(Status::CommunicationError);
  }
  //////////////////////////////////////////
  result = Packet.GetParameterSegmentFromBytes(switch4Luggage, switch4Passengers, 1, 2);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("512: Packet.GetParameterSegmentFromBytes");
    Device.SetStatus(Status::CommunicationError);
  }
  //////////////////////////////////////////
  result = Packet.GetParameterSegmentFromBytes(switch5Luggage, switch5Passengers, 1, 2);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("519: Packet.GetParameterSegmentFromBytes");
    Device.SetStatus(Status::CommunicationError);
  }
}

/**
 * @brief Interface that assigns luggages
 * to passengers.
 */
void AssignLuggagesToPassengers()
{
  AssignLeftJoystickLuggageToPassengers();
  AssignRightJoystickLuggageToPassengers();
  AssignSwitchesLuggageToPassengers();
}
#pragma endregion

#pragma region ------------------------- Board classes in plane
/**
 * @brief Function that generates segments
 * to build a plane later.
 */
void BoardPassengersInThePlane()
{
  Execution result;
  int temporarySegmentSize = 10;
  /////////////////////////////////////// LX + LY
  result = Packet.AppendSegments(leftJoystickXaxisPassengers, 5, leftJoystickYaxisPassengers, 5, temporaryBufferA, &temporarySegmentSize);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("545: Packet.AppendSegments");
    Device.SetStatus(Status::CommunicationError);
  }
  /////////////////////////////////////// LX,LY + LB
  temporarySegmentSize = 12;
  result = Packet.AppendSegments(temporaryBufferA, 10, leftJoystickButtonPassengers, 2, temporaryBufferB, &temporarySegmentSize);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("556: Packet.AppendSegments");
    Device.SetStatus(Status::CommunicationError);
  }
  /////////////////////////////////////// LX,LY,LB + RX
  temporarySegmentSize = 17;
  result = Packet.AppendSegments(temporaryBufferB, 12, rightJoystickXaxisPassengers, 5, temporaryBufferA, &temporarySegmentSize);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("564: Packet.AppendSegments");
    Device.SetStatus(Status::CommunicationError);
  }
  /////////////////////////////////////// LX,LY,LB,RX + RY
  temporarySegmentSize = 22;
  result = Packet.AppendSegments(temporaryBufferA, 17, rightJoystickYaxisPassengers, 5, temporaryBufferB, &temporarySegmentSize);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("572: Packet.AppendSegments");
    Device.SetStatus(Status::CommunicationError);
  }
  /////////////////////////////////////// LX,LY,LB,RX,RY + RB
  temporarySegmentSize = 24;
  result = Packet.AppendSegments(temporaryBufferB, 22, rightJoystickButtonPassengers, 2, temporaryBufferA, &temporarySegmentSize);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("580: Packet.AppendSegments");
    Device.SetStatus(Status::CommunicationError);
  }

  /////////////////////////////////////// LX,LY,LB,RX,RY,RB + S1
  temporarySegmentSize = 26;
  result = Packet.AppendSegments(temporaryBufferA, 24, switch1Passengers, 2, temporaryBufferB, &temporarySegmentSize);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("589: Packet.AppendSegments");
    Device.SetStatus(Status::CommunicationError);
  }
  /////////////////////////////////////// LX,LY,LB,RX,RY,RB,S1 + S2
  temporarySegmentSize = 28;
  result = Packet.AppendSegments(temporaryBufferB, 26, switch2Passengers, 2, temporaryBufferA, &temporarySegmentSize);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("597: Packet.AppendSegments");
    Device.SetStatus(Status::CommunicationError);
  }
  /////////////////////////////////////// LX,LY,LB,RX,RY,RB,S1,S2 + S3
  temporarySegmentSize = 30;
  result = Packet.AppendSegments(temporaryBufferA, 28, switch3Passengers, 2, temporaryBufferB, &temporarySegmentSize);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("605: Packet.AppendSegments");
    Device.SetStatus(Status::CommunicationError);
  }
  /////////////////////////////////////// LX,LY,LB,RX,RY,RB,S1,S2,S3 + S4
  temporarySegmentSize = 32;
  result = Packet.AppendSegments(temporaryBufferB, 30, switch4Passengers, 2, temporaryBufferA, &temporarySegmentSize);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("613: Packet.AppendSegments");
    Device.SetStatus(Status::CommunicationError);
  }
  /////////////////////////////////////// LX,LY,LB,RX,RY,RB,S1,S2,S3,S4 + S5
  temporarySegmentSize = 34;
  result = Packet.AppendSegments(temporaryBufferA, 32, switch5Passengers, 2, boardedPassengers, &temporarySegmentSize);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("621: Packet.AppendSegments");
    Device.SetStatus(Status::CommunicationError);
  }
}
#pragma endregion

#pragma region ------------------------- Get plane ready for take off
/**
 * @brief Interface that puts a place on the runway pilot
 */
void GetPlaneReadyForTakeOff()
{
  Execution result;
  /////////////////
  result = Packet.CreateFromSegments(20, boardedPassengers, 34, hardwarePlane, 36);
  if(result != Execution::Passed)
  {
    Device.SetErrorMessage("636: Plane building failure");
    Device.SetStatus(Status::CommunicationError);
  }
}
#pragma endregion
/**
 * @brief Interface that builds an hardware plane.
 */
void BuildHardwarePlane()
{
  ExtractVariablesFromHardware();
  ConvertVariablesToLuggage();
  AssignLuggagesToPassengers();
  BoardPassengersInThePlane();
  GetPlaneReadyForTakeOff();
}

/**
 * @brief Interface that handles the generation
 * of answers to hardware output requests.
 */
void HandleAnswerToHardwareRequest()
{
  Device.SetStatus(Status::Busy);
  BuildHardwarePlane();
  PlaneTakeOff(hardwarePlane, 37);
  ClearRunway();
  planeLanded = false;
  Device.SetStatus(Status::Available);
}
#pragma endregion

/**
 * @brief Pilot that sends passengers on a runway.
 * @param planePassengers 
 * @param sizeOfPlane 
 */
void PlaneTakeOff(unsigned short* planePassengers, int sizeOfPlane)
{
  Execution result;
  unsigned char uartPassenger[2];

  // Convert passengers to uart bytes.
  for (unsigned char passengerIndex = 0; passengerIndex < sizeOfPlane; passengerIndex++)
  {
    unsigned short passenger = planePassengers[passengerIndex];

    result = Chunk.ToUART(passenger, uartPassenger);
    if(result != Execution::Passed)
    {
      Device.SetErrorMessage("664: UART Convertion failure");
      Device.SetStatus(Status::CommunicationError);
    }
    kontrolToGamepad.write(uartPassenger[0]);
    kontrolToGamepad.write(uartPassenger[1]);
  }
}

#pragma region ------------------------- Data interfaces
/**
 * @brief Interface that handles
 * the regular data sending portion of the
 * communication.
 */
void HandleHandshaken()
{
  if(handshaken)
  {
   ShowRegularRGB();
   if(PlaneIsAnHardwareRequest())
   {
     // We received a plane asking us to send a plane containing all our hardware data.
     HandleAnswerToHardwareRequest();
   }
   else
   {
     if(PlaneIsAnHandshake())
     {
       SendUniversalInfo();
       ClearRunway();
       planeLanded = false;
       handshaken = true;
     }
   }
  }  
}

/**
 * @brief Interface that handles the handshaking
 * portion of the communication.
 */
void HandleHandshaking()
{
  if(!handshaken)
  {
    Device.SetStatus(Status::Handshake);
    ShowHandshakingRGB();
    if(PlaneIsAnHandshake())
    {
      SendUniversalInfo();
      ClearRunway();
      planeLanded = false;
      handshaken = true;
    } 
  }
}
#pragma endregion

#pragma region ------------------------- Processes
/**
 * @brief Process that handles
 * all communication proceedures
 * of Gamepad including data
 * parsing and sending.
 */
void HandleCommunications()
{
  HandleReceivedMasterData();
  HandleHandshaking();
  HandleHandshaken(); 
}

/**
 * @brief Process that handles
 * the hardware inputs of
 * Gamepad. This excludes RGB
 * because RGB is an output.
 */
void HandleHardware()
{
  UpdateAllControls();
}

/**
 * @brief Function that handles
 * the RGB process. It mainly calls
 * the update function of the RGB object.
 * to update its light and handle animations.
 */
void HandleRGB()
{
  Rgb.Update();
}
#pragma endregion

void loop()
{
  // SendUniversalInfo();
  // delay(1000);

  HandleHardware();
  HandleCommunications();
  HandleRGB();
}
