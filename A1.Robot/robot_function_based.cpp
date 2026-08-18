// A line-following robot (function-based version)
//
// This program models a robot that follows a line. Each cycle the robot reads
// its line sensor, works out how hard to steer, and sets its two drive motors.
// The robot also has a battery which loses charge every cycle. If the battery
// charge falls below 80, the forward speed is reduced.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <stdio.h>

//--Consts---------------------------------------------------------------------
const int NumCycles = 4;
const double BaseSpeed = 0.5;
const double ReducedSpeed = 0.25;
const int BatteryLossPerCycle = 10;

//---SLineSensor---------------------------------------------------------------
struct SLineSensor
{
  int cycle;
};

//---SController---------------------------------------------------------------
struct SController
{
  double lastError;
};

//---SMotor--------------------------------------------------------------------
struct SMotor
{
  const char* pName;
  double speed;
};

//---SBattery------------------------------------------------------------------
struct SBattery
{
  int charge;
};

//---Function declarations-----------------------------------------------------
void InitLineSensor( SLineSensor* apSensor );
void InitController( SController* apController );
void InitMotor( SMotor* apMotor, const char* aName );
void InitBattery( SBattery* apBattery );

int ReadLineSensor( SLineSensor* apSensor );
double ComputeSteering( SController* apController, int aError );
void SetMotorSpeed( SMotor* apMotor, double aSpeed );
void UseBattery( SBattery* apBattery );
bool IsBatteryLow( SBattery* apBattery );

void UpdateRobot( SLineSensor* apSensor,
                  SController* apController,
                  SMotor* apLeftMotor,
                  SMotor* apRightMotor,
                  SBattery* apBattery );

void ReportRobot( SMotor* apLeftMotor,
                  SMotor* apRightMotor,
                  SBattery* apBattery );

//---main----------------------------------------------------------------------
int main()
{
  SLineSensor sensor;
  SController controller;
  SMotor leftMotor;
  SMotor rightMotor;
  SBattery battery;

  InitLineSensor( &sensor );
  InitController( &controller );
  InitMotor( &leftMotor, "Left" );
  InitMotor( &rightMotor, "Right" );
  InitBattery( &battery );

  for( int i = 0; i < NumCycles; ++i )
  {
    UpdateRobot( &sensor, &controller,
                 &leftMotor, &rightMotor,
                 &battery );

    ReportRobot( &leftMotor, &rightMotor, &battery );
  }

  return 0;
}

//---InitLineSensor------------------------------------------------------------
void InitLineSensor( SLineSensor* apSensor )
{
  apSensor->cycle = 0;
}

//---InitController------------------------------------------------------------
void InitController( SController* apController )
{
  apController->lastError = 0.0;
}

//---InitMotor-----------------------------------------------------------------
void InitMotor( SMotor* apMotor, const char* aName )
{
  apMotor->pName = aName;
  apMotor->speed = 0.0;
}

//---InitBattery---------------------------------------------------------------
void InitBattery( SBattery* apBattery )
{
  apBattery->charge = 100;
}

//---ReadLineSensor------------------------------------------------------------
int ReadLineSensor( SLineSensor* apSensor )
{
  const int Track[NumCycles] = { 2, 1, -1, -2 };

  int reading = Track[ apSensor->cycle ];
  ++apSensor->cycle;

  return reading;
}

//---ComputeSteering-----------------------------------------------------------
double ComputeSteering( SController* apController, int aError )
{
  double steering = 0.1 * aError
                  + 0.05 * ( aError - apController->lastError );

  apController->lastError = aError;

  return steering;
}

//---SetMotorSpeed-------------------------------------------------------------
void SetMotorSpeed( SMotor* apMotor, double aSpeed )
{
  apMotor->speed = aSpeed;
}

//---UseBattery----------------------------------------------------------------
void UseBattery( SBattery* apBattery )
{
  apBattery->charge -= BatteryLossPerCycle;
}

//---IsBatteryLow--------------------------------------------------------------
bool IsBatteryLow( SBattery* apBattery )
{
  return apBattery->charge < 80;
}

//---UpdateRobot---------------------------------------------------------------
void UpdateRobot( SLineSensor* apSensor,
                  SController* apController,
                  SMotor* apLeftMotor,
                  SMotor* apRightMotor,
                  SBattery* apBattery )
{
  int error = ReadLineSensor( apSensor );
  double steering = ComputeSteering( apController, error );

  UseBattery( apBattery );

  double forwardSpeed = BaseSpeed;

  if( IsBatteryLow( apBattery ) )
  {
    forwardSpeed = ReducedSpeed;
  }

  SetMotorSpeed( apLeftMotor, forwardSpeed + steering );
  SetMotorSpeed( apRightMotor, forwardSpeed - steering );
}

//---ReportRobot---------------------------------------------------------------
void ReportRobot( SMotor* apLeftMotor,
                  SMotor* apRightMotor,
                  SBattery* apBattery )
{
  printf( "%s motor %g, %s motor %g, battery %d\n",
          apLeftMotor->pName, apLeftMotor->speed,
          apRightMotor->pName, apRightMotor->speed,
          apBattery->charge );
}