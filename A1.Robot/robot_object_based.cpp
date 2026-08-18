// A line-following robot (object-based version)
//
// This program models a robot that follows a line. Each cycle the robot reads
// its line sensor, works out how hard to steer, and sets its two drive motors.
// The robot also owns a battery which loses charge every cycle. If the battery
// charge falls below 80, the forward speed is reduced.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>

//--Consts---------------------------------------------------------------------
const int NumCycles = 4;
const double BaseSpeed = 0.5;
const double ReducedSpeed = 0.25;
const int BatteryLossPerCycle = 10;

//---CLineSensor---------------------------------------------------------------
class CLineSensor
{
  public:
    CLineSensor();
    int Read();

  private:
    int mCycle;
};

//---CController---------------------------------------------------------------
class CController
{
  public:
    CController();
    double ComputeSteering( int aError );

  private:
    double mLastError;
};

//---CMotor--------------------------------------------------------------------
class CMotor
{
  public:
    CMotor( const std::string& aName );
    void SetSpeed( double aSpeed );
    void Report();

  private:
    std::string mName;
    double mSpeed;
};

//---CBattery------------------------------------------------------------------
class CBattery
{
  public:
    CBattery();

    void UseCharge();
    bool IsLow();
    void Report();

  private:
    int mCharge;
};

//---CRobot--------------------------------------------------------------------
class CRobot
{
  public:
    CRobot();

    void Update();
    void Report();

  private:
    CLineSensor mSensor;
    CController mController;
    CMotor mLeftMotor;
    CMotor mRightMotor;
    CBattery mBattery;
};

//---main----------------------------------------------------------------------
int main()
{
  CRobot robot;

  for( int i = 0; i < NumCycles; ++i )
  {
    robot.Update();
    robot.Report();
  }

  return 0;
}

//---CLineSensor Implementation------------------------------------------------
CLineSensor::CLineSensor()
  : mCycle( 0 )
{
}

int CLineSensor::Read()
{
  const int Track[NumCycles] = { 2, 1, -1, -2 };

  int reading = Track[ mCycle ];
  ++mCycle;

  return reading;
}

//---CController Implementation------------------------------------------------
CController::CController()
  : mLastError( 0.0 )
{
}

double CController::ComputeSteering( int aError )
{
  double steering = 0.1 * aError
                  + 0.05 * ( aError - mLastError );

  mLastError = aError;

  return steering;
}

//---CMotor Implementation-----------------------------------------------------
CMotor::CMotor( const std::string& aName )
  : mName( aName ),
    mSpeed( 0.0 )
{
}

void CMotor::SetSpeed( double aSpeed )
{
  mSpeed = aSpeed;
}

void CMotor::Report()
{
  std::cout << mName << " motor " << mSpeed;
}

//---CBattery Implementation---------------------------------------------------
CBattery::CBattery()
  : mCharge( 100 )
{
}

void CBattery::UseCharge()
{
  mCharge -= BatteryLossPerCycle;
}

bool CBattery::IsLow()
{
  return mCharge < 80;
}

void CBattery::Report()
{
  std::cout << "battery " << mCharge;
}

//---CRobot Implementation-----------------------------------------------------
CRobot::CRobot()
  : mLeftMotor( "Left" ),
    mRightMotor( "Right" )
{
}

void CRobot::Update()
{
  int error = mSensor.Read();
  double steering = mController.ComputeSteering( error );

  mBattery.UseCharge();

  double forwardSpeed = BaseSpeed;

  if( mBattery.IsLow() )
  {
    forwardSpeed = ReducedSpeed;
  }

  mLeftMotor.SetSpeed( forwardSpeed + steering );
  mRightMotor.SetSpeed( forwardSpeed - steering );
}

void CRobot::Report()
{
  mLeftMotor.Report();
  std::cout << ", ";

  mRightMotor.Report();
  std::cout << ", ";

  mBattery.Report();
  std::cout << std::endl;
}