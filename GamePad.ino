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
#include "Globals.h"
#include "_UNIT_TEST.h"
#pragma endregion
//================================================================================================//

void setup() {
  Serial.begin(9600);
  //Rgb.SetColors(255, 255, 255);
  //Rgb.Update();

  //Serial.println(Rgb.currentRed);
  //Serial.println(Rgb.currentGreen);
  //Serial.println(Rgb.currentBlue);
  InitializeProject();
  Device.SetStatus(Status::Booting);
  for(int i=0; i<1000; ++i)
  {
    Rgb.Update();
    delay(1);
  }

  Execution result = TestInitialization();
  if(result == Execution::Passed)
  {
    Device.SetStatus(Status::Clueless);
  }
  else
  {
    Device.SetStatus(Status::SoftwareError);
  }

  for(int i=0; i<1000; ++i)
  {
    Rgb.Update();
    delay(1);
  }

  result = TestAllUnits();
}

unsigned int milliseconds = 0;
int previousStatus = Status::Available;

void loop() {

  Rgb.Update();
  // LeftJoystick.Update();
// 
            // unsigned char red = analogRead(8);
            // unsigned char blue = analogRead(5);
            // unsigned char green = (digitalRead(15)*255);
// 
            // Rgb.SetMode(0);
            // Rgb.SetColors((double)(red), (double)green, (double)(blue));
// 
            // Serial.println(std::to_string(red).c_str());
            // Serial.println(std::to_string(blue).c_str());
            // Serial.println(std::to_string(green).c_str());
            // Serial.println("");
  // milliseconds++;

  // if(milliseconds >= 10000)
  // {
    // milliseconds = 0;
  // 
    // switch(previousStatus)
    // {
        // case(Status::Available):
            // Serial.println("New status -> Booting");
            // Device.SetStatus(Status::Booting);
            // previousStatus = Status::Booting;
            // break;
  // 
        // case(Status::Booting):
            // Serial.println("New status -> Busy");
            // Device.SetStatus(Status::Busy);
            // previousStatus = Status::Busy;
            // break;
  // 
        // case(Status::Busy):
            // Serial.println("New status -> Clueless");
            // Device.SetStatus(Status::Clueless);
            // previousStatus = Status::Clueless;
            // break;
  // 
        // case(Status::Clueless):
            // Serial.println("New status -> CommunicationError");
            // Device.SetStatus(Status::CommunicationError);
            // previousStatus = Status::CommunicationError;
            // break;
    // 
        // case(Status::CommunicationError):
            // Serial.println("New status -> CompatibilityError");
            // Device.SetStatus(Status::CompatibilityError);
            // previousStatus = Status::CompatibilityError;
            // break;
  // 
        // case(Status::CompatibilityError):
            // Serial.println("New status -> Crashing");
            // Device.SetStatus(Status::Crashing);
            // previousStatus = Status::Crashing;
            // break;
  // 
        // case(Status::Crashing):
            // Serial.println("New status -> Debugging");
            // Device.SetStatus(Status::Debugging);
            // previousStatus = Status::Debugging;
            // break;
    // 
        // case(Status::Debugging):
            // Serial.println("New status -> Handshake");
            // Device.SetStatus(Status::Handshake);
            // previousStatus = Status::Handshake;
            // break;
  // 
        // case(Status::Handshake):
            // Serial.println("New status -> HardwareError");
            // Device.SetStatus(Status::HardwareError);
            // previousStatus = Status::HardwareError;
            // break;
  // 
        // case(Status::HardwareError):
            // Serial.println("New status -> NoBattery");
            // Device.SetStatus(Status::NoBattery);
            // previousStatus = Status::NoBattery;
            // break;
  // 
        // case(Status::NoBattery):
            // Serial.println("New status -> Shutdown");
            // Device.SetStatus(Status::Shutdown);
            // previousStatus = Status::Shutdown;
            // break;
  // 
        // case(Status::Shutdown):
            // Serial.println("New status -> SoftwareError");
            // Device.SetStatus(Status::SoftwareError);
            // previousStatus = Status::SoftwareError;
            // break;
  // 
        // case(Status::SoftwareError):
            // Serial.println("New status -> Available");
            // Device.SetStatus(Status::Available);
            // previousStatus = Status::Available;
            // break;
  // 
        // default:
        // break;
    // }
  //}


  Rgb.Update();
  delay(1);
}
