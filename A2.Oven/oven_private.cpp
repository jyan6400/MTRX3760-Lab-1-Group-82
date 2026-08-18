// An oven temperature model (encapsulated version)
//
// This program models two ovens that warm up in steps and warn if they
// overheat. Each oven's data is private, and main() works through meaningful
// functions rather than touching the temperatures directly.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>

//---COven---------------------------------------------------------------------
class COven
{
  public:
    COven( const std::string& aName );

    void WarmUp();
    bool IsOverheating();
    void Report();

  private:
    std::string mName;
    int mTemperatureTenthsC;
};

//---main----------------------------------------------------------------------
int main()
{
  COven ReflowOven( "Reflow oven" );
  COven CuringOven( "Curing oven" );

  for( int i = 0; i < 5; ++i )
  {
    ReflowOven.WarmUp();
  }

  for( int i = 0; i < 8; ++i )
  {
    CuringOven.WarmUp();
  }

  if( ReflowOven.IsOverheating() )
  {
    std::cout << "Warning: oven is overheating!" << std::endl;
  }

  if( CuringOven.IsOverheating() )
  {
    std::cout << "Warning: oven is overheating!" << std::endl;
  }

  ReflowOven.Report();
  CuringOven.Report();

  return 0;
}

//---COven Implementation------------------------------------------------------
COven::COven( const std::string& aName )
  : mName( aName ),
    mTemperatureTenthsC( 200 )
{
}

void COven::WarmUp()
{
  mTemperatureTenthsC += 10;
}

bool COven::IsOverheating()
{
  return mTemperatureTenthsC >= 2500;
}

void COven::Report()
{
  std::cout << mName << " is at "
            << mTemperatureTenthsC / 10
            << "C" << std::endl;
}