// A clock model
//
// This program models a simple clock that keeps a time in minutes and can
// advance, report, and reset it. main() creates one plain clock and steps it
// forward by a minute.
//
// Edit this file directly to build the version asked for in the handout.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>

const int ONE_DAY_MINUTES = 1440;

//---CClock--------------------------------------------------------------------
// A CClock keeps a time, measured in whole minutes, and can advance it one
// minute at a time, report it, and reset it to where it started.
class CClock
{
  public:
    // Creates a clock with the given name and starting time, in minutes
    // since midnight.
    CClock( const std::string& aName, int aStartMinutes );

    // Tick advances the clock by one minute.
    void Tick();

    // GetTime returns the current time, in minutes since midnight.
    int GetTime();

    // Reset returns the clock to its starting time.
    void Reset();

    // Report prints the clock's name and current time as HH:MM.
    void Report();

  private:
    std::string mName;          // the clock's label, e.g. "Kitchen"
    int mStartMinutes;          // the time the clock was initialised to
    int mCurrentMinutes;        // current time, in minutes since midnight
};

class CClockStandAlone
{
  public:
    CClockStandAlone( const std::string& aName, int aStartMinutes );
    void Tick();
    int GetTime();
    void Reset();
    void Report();

    // Set a clock
    void SetClock( int aClockMinutes );

    // Clock ringing control
    bool ClockRing();

  private:
    std::string mName;
    int mStartMinutes;
    int mCurrentMinutes;
    int mClockMinutes;          // the time when clock should ring
    bool mClockSet;             // record whether a clock has been set 
};

//---main----------------------------------------------------------------------
// Creates one plain clock, starts it at 06:59, advances it one minute, and
// reports it.
int main()
{
  CClock clock( "Kitchen", 419 );    // 419 minutes = 06:59
  clock.Tick();
  clock.Report();

  CClockStandAlone AlarmClock( "WakeUpClock", 418 ); 

  // Set a clock at 08:00
  AlarmClock.SetClock( 480 );

  // Keep running the clock until it reaches the preset time
  while ( AlarmClock.ClockRing() == false )
  {
    AlarmClock.Tick();
    AlarmClock.Report();
  }

  return 0;
}

//---CClock Implementation-----------------------------------------------------
CClock::CClock( const std::string& aName, int aStartMinutes )
  : mName( aName ),
    mStartMinutes( aStartMinutes ),
    mCurrentMinutes( aStartMinutes )
{
}
//---
void CClock::Tick()
{
  ++mCurrentMinutes;
}
//---
int CClock::GetTime()
{
  return mCurrentMinutes;
}
//---
void CClock::Reset()
{
  mCurrentMinutes = mStartMinutes;
}
//---
void CClock::Report()
{
  int hours = ( mCurrentMinutes / 60 ) % 24;
  int minutes = mCurrentMinutes % 60;
  std::cout << mName << " "
            << ( hours < 10 ? "0" : "" ) << hours << ":"
            << ( minutes < 10 ? "0" : "" ) << minutes << std::endl;
}

// A brand-new, separate class
CClockStandAlone::CClockStandAlone( const std::string & aName, int aStartMinutes )
  : mName( aName ),
    mStartMinutes( aStartMinutes ),
    mCurrentMinutes( aStartMinutes ),
    mClockMinutes( 0 ),
    mClockSet( false )
{
}

//---
void CClockStandAlone::Tick()
{
  ++mCurrentMinutes;
}
//---
int CClockStandAlone::GetTime()
{
  return mCurrentMinutes;
}
//---
void CClockStandAlone::Reset()
{
  mCurrentMinutes = mStartMinutes;
}
//---
void CClockStandAlone::Report()
{
  int hours = ( mCurrentMinutes / 60 ) % 24;
  int minutes = mCurrentMinutes % 60;
  std::cout << mName << " "
            << ( hours < 10 ? "0" : "" ) << hours << ":"
            << ( minutes < 10 ? "0" : "" ) << minutes << std::endl;
  if ( ClockRing() )
  {
    std::cout << " Clock is ringing! " << std::endl;
  }

}

void CClockStandAlone::SetClock( int aClockMinutes )
{
  mClockMinutes = aClockMinutes;
  mClockSet = true;
}

bool CClockStandAlone::ClockRing()
{
  // Close if no alarm has been set
  if ( mClockSet == false )
  {
    return false;
  }
  // Ring at the preset time 
  if ( mCurrentMinutes % ONE_DAY_MINUTES == mClockMinutes % ONE_DAY_MINUTES )
  {
    return true;
  }
  else
  {
    return false;
  }
}