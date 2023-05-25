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

void HandleReceivedMasterData()
{
  if (kontrolToGamepad.available())
  {
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
void SendUniversalInfo()
{
  for(int index = 0; index < 170; index++)
  {
    kontrolToGamepad.write(UniversalInformationPlane[index]);
  }
}

#pragma region ------------------------- RGB handlers
void ShowHandshakingRGB()
{
  Rgb.SetMode(1);
  Rgb.SetAnimations(255, 1000, 4);
  Rgb.SetColors(255,128,0);
}

void ShowRegularRGB()
{
  Rgb.SetMode(2);
  Rgb.SetColors(0,128,0);
}
#pragma endregion

#pragma region ------------------------- Hardware plane building
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

void ConvertVariablesToLuggage()
{
  ConvertLeftJoystickToLuggages();
  ConvertRightJoystickToLuggages();
  ConvertSwitchesToLuggage();
}
#pragma endregion

#pragma region ------------------------- Passenger classes convertions
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

void AssignLuggagesToPassengers()
{
  AssignLeftJoystickLuggageToPassengers();
  AssignRightJoystickLuggageToPassengers();
  AssignSwitchesLuggageToPassengers();
}
#pragma endregion

#pragma region ------------------------- Board classes in plane
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
void BuildHardwarePlane()
{
  ExtractVariablesFromHardware();
  ConvertVariablesToLuggage();
  AssignLuggagesToPassengers();
  BoardPassengersInThePlane();
  GetPlaneReadyForTakeOff();
}

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

void loop() 
{
  SendUniversalInfo();
  delay(1000);
  //HandleReceivedMasterData();
  //if(handshaken)
  //{
  //  ShowRegularRGB();
  //  if(PlaneIsAnHardwareRequest())
  //  {
  //    // We received a plane asking us to send a plane containing all our hardware data.
  //    HandleAnswerToHardwareRequest();
  //  }
  //  else
  //  {
  //    if(PlaneIsAnHandshake())
  //    {
  //      SendUniversalInfo();
  //      ClearRunway();
  //      planeLanded = false;
  //      handshaken = true;
  //    }
  //  }
  //}
  //else
  //{
  //  Device.SetStatus(Status::Handshake);
  //  ShowHandshakingRGB();
  //  if(PlaneIsAnHandshake())
  //  {
  //    SendUniversalInfo();
  //    ClearRunway();
  //    planeLanded = false;
  //    handshaken = true;
  //  }
  //}

  Rgb.Update();
}
