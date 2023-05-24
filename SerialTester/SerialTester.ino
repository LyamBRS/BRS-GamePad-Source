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
bool receivingPlane = false;
bool receivingLuggage = false;
bool waitingForCheckSum = false;
bool planeReceived = false;
bool handshaken = false;
bool sendControls = false;
int currentPlaneSize = 0;


void clearReceptionBuffer()
{
  currentPlaneSize = 0;
  receivingLuggage = 0;
  waitingForCheckSum = 0;
  for(int index = 0; index<200; index++)
  {
    receivedPassengers[index] = 0;
  }
}

void handlePassengerLuggage(unsigned char passenger)
{
  if(receivingLuggage && receivingPlane)
  {
    receivedPassengers[currentPlaneSize] = passenger;
    currentPlaneSize++;
    receivingLuggage = false;

    if(waitingForCheckSum)
    {
      waitingForCheckSum = false;
      receivingLuggage = false
      receivingPlane = false;
      planeReceived = true;
    }
  }
}

void handlePassengerType(unsigned char passengerType)
{
  if(!receivingLuggage)
  {
    // passenger to come is a pilot 
    if(!receivingPlane && currentByte == 2 && !receivingLuggage)
    {
      receivingPlane = true;
      clearReceptionBuffer();
      receivedPassengers[currentPlaneSize] = 2;
      currentPlaneSize++;
      receivingLuggage = true;
      waitingForCheckSum = true;
      return
    }

    // next passenger is a co-pilot
    if(receivingPlane && currentByte == 3 && !receivingLuggage)
    {
      clearReceptionBuffer();
      receivedPassengers[currentPlaneSize] = 3;
      currentPlaneSize++;
      receivingLuggage = true;
      return
    }

    // next passenger is a passenger
    if(receivingPlane && currentByte == 0 && !receivingLuggage)
    {
      clearReceptionBuffer();
      receivedPassengers[currentPlaneSize] = 0;
      currentPlaneSize++;
      receivingLuggage = true;
      return
    }

    // next passenger is a flight attendant.
    if(receivingPlane && currentByte == 1 && !receivingLuggage)
    {
      clearReceptionBuffer();
      receivedPassengers[currentPlaneSize] = 1;
      currentPlaneSize++;
      receivingLuggage = true;
      return
    }
  }
}

void handleReceivedMasterData()
{
  if (kontrolToGamepad.available())
  {
    unsigned char currentByte = kontrolToGamepad.read();

    if(!receivingPlane || !receivingLuggage)
    {
      handlePassengerType(currentByte);
    }
    else
    {
      handlePassengerLuggage(currentByte);
    }
  }
}

void updateAllControls()
{
  LeftJoystick.Update();
  RightJoystick.Update();
  Button1.Update();
  Button2.Update();
  Button3.Update();
  Button4.Update();
  Button5.Update();
}

bool isCurrentPlaneAnHandshake()
{
  if(planeAvailable)
  {
    if(receivedPassengers[1] == 7)
    {
      handshaken = true;
      return true;
    }
    else
    {
      return false
    }
  }
  return false;
}

void SendUniversalInfo()
{
  for(int index = 0; index < 180; index++)
  {
    kontrolToGamepad.write(UniversalInformationPlane[index]);
  }
}

void DisplayHandshake()
{
  Rgb.SetMode(1);
  Rgb.SetAnimations(255, 1000, 4);
  Rgb.SetColors(255,128,0);
}

void DisplayRegularLights()
{
  Rgb.SetMode(2);
  Rgb.SetColors(0,128,0);
}

bool isPlaneRequestForHardware()
{
  if(planeAvailable)
  {
    planeAvailable = false;
    if(receivedPassengers[1] == 20)
    {
      return true;
    }
    else
    {
      return false
    }
  }
  return false;
}

void loop() 
{
  handleReceivedMasterData();
  if(handshaken)
  {
    DisplayRegularLights();
    if(isPlaneRequestForHardware())
    {

    }
    else
    {
      
    }

  }
  else
  {
    DisplayHandshake();
    if(isCurrentPlaneAnHandshake())
    {
      SendUniversalInfo();
      planeReceived = false;
      handshaken = true;
    }
  }

  Rgb.Update();
}
