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
  Execution execution;
  Serial.begin(9600);
  Rgb.SetColors(255, 255, 255);
  execution = Rgb.Update();
  if(execution != Execution::Passed)
  {
    Serial.println("29");
  }

  // Serial.println(Rgb.currentRed);
  // Serial.println(Rgb.currentGreen);
  // Serial.println(Rgb.currentBlue);
  InitializeProject();
  Device.SetStatus(Status::Booting);
  for(int i=0; i<1000; ++i)
  {
    execution = Rgb.Update();
    if(execution != Execution::Passed)
    {
      Serial.println("42");
    }
    delay(1);
  }

  execution = TestInitialization();
  if(execution == Execution::Passed)
  {
    Device.SetStatus(Status::Clueless);
  }
  else
  {
    Device.SetStatus(Status::SoftwareError);
  }

  for(int i=0; i<5000; ++i)
  {
    execution = Rgb.Update();
    if(execution != Execution::Passed)
    {
      Serial.println("62");
    }
    delay(1);
  }

  execution = TestAllUnits();
  if(execution != Execution::Passed)
  {
    Device.SetStatus(Status::SoftwareError);
  }

  LeftJoystick.SetDeadZone_X(60);
  LeftJoystick.SetDeadZone_Y(60);
  RightJoystick.SetDeadZone_X(60);
  RightJoystick.SetDeadZone_Y(60);
}

unsigned int milliseconds = 0;
int previousStatus = Status::Available;

void loop() {

  Rgb.Update();
  LeftJoystick.Update();
  RightJoystick.Update();

  Button1.Update();
  Button2.Update();
  Button3.Update();
  Button4.Update();
  Button5.Update();

  int right_x = 0;
  int left_x = 0;
  int left_y = 0;
  int right_y = 0;
  bool left_button = 0;
  bool right_button = 0;

  bool button1 = false;
  bool button2 = false;
  bool button3 = false;
  bool button4 = false;
  bool button5 = false;

  Button1.GetLatestValue(&button1);
  Button2.GetLatestValue(&button2);
  Button3.GetLatestValue(&button3);
  Button4.GetLatestValue(&button4);
  Button5.GetLatestValue(&button5);

  LeftJoystick.GetCurrentAxis_X(&left_x);
  LeftJoystick.GetCurrentAxis_Y(&left_y);
  RightJoystick.GetCurrentAxis_X(&right_x);
  RightJoystick.GetCurrentAxis_Y(&right_y);
  LeftJoystick.GetCurrentSwitch(&left_button);
  RightJoystick.GetCurrentSwitch(&right_button);

  LeftJoystick.SetMode(0);
  RightJoystick.SetMode(0);

  LeftJoystick.SetTrim_X(0);
  LeftJoystick.SetTrim_Y(0);
  RightJoystick.SetTrim_X(0);
  RightJoystick.SetTrim_Y(0);

  LeftJoystick.GetCurrentAxis_X(&left_x);
  LeftJoystick.GetCurrentAxis_Y(&left_y);

  RightJoystick.GetCurrentAxis_X(&right_x);
  RightJoystick.GetCurrentAxis_Y(&right_y);

  LeftJoystick.GetCurrentSwitch(&left_button);
  RightJoystick.GetCurrentSwitch(&right_button);

  Serial.print("RX: ");
  Serial.println(right_x);
  Serial.print("RY: ");
  Serial.println(right_y);
// 
  // Serial.print("LX: ");
  // Serial.println(left_x);
  // Serial.print("LY: ");
  // Serial.println(left_y);
  // Serial.print("RB: ");
  // Serial.println(right_button);
  // Serial.print("LB: ");
  // Serial.println(left_button);
  // Serial.print("\n");
// 
  // Serial.print("1: ");
  // Serial.println(button1);
  // Serial.print("2: ");
  // Serial.println(button2);
  // Serial.print("3: ");
  // Serial.println(button3);
  // Serial.print("4: ");
  // Serial.println(button4);
  // Serial.print("5: ");
  // Serial.println(button5);
  // Serial.print("\n");

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
  delay(1);
}
