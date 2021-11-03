#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;

extern "C"
{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Rotate"; }
}


Interp4Command *CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


Interp4Rotate::Interp4Rotate() : _object_name("no_name"), _Angular_speed_degS(0), _Axis('X'), _Rotation_angle_deg(0)
{
}


void Interp4Rotate::PrintCmd() const
{
  
  cout << GetCmdName() << " " << _object_name << " " << _Angular_speed_degS << " " << _Axis << " " << _Rotation_angle_deg << endl;
}


const char *Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


bool Interp4Rotate::ExecCmd(MobileObj *pMobObj, int Socket) const
{
  
  return true;
}


bool Interp4Rotate::ReadParams(std::istream &Strm_CmdsList)
{
  
  Strm_CmdsList >> _object_name >> _Angular_speed_degS >> _Axis >> _Rotation_angle_deg;
  return !Strm_CmdsList.fail();
}


Interp4Command *Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  SzybkoscKatowa[deg/s]  NazwaOsi KatObrotu[deg]" << endl;
}