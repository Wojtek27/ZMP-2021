#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"

extern "C"{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Rotate"; }
}


Interp4Command *CreateCmd(void){
  return Interp4Rotate::CreateCmd();
}


Interp4Rotate::Interp4Rotate() : objectName("no_name"), AngularSpeedDegS(0), Axis('X'), RotationAngleDeg(0){
}


void Interp4Rotate::PrintCmd() const{ 
  cout << GetCmdName() << " " << objectName << " " << AngularSpeedDegS << " " << Axis << " " << RotationAngleDeg << endl;
}


const char *Interp4Rotate::GetCmdName() const{
  return ::GetCmdName();
}


bool Interp4Rotate::ExecCmd(MobileObj *pMobObj, int Socket) const{
  return true;
}

std::string Interp4Rotate::GetObjName() const
{
  return objectName;
}

bool Interp4Rotate::ReadParams(std::istream &Strm_CmdsList){
  Strm_CmdsList >> objectName >> AngularSpeedDegS >> Axis >> RotationAngleDeg;
  return !Strm_CmdsList.fail();
}


Interp4Command *Interp4Rotate::CreateCmd(){
  return new Interp4Rotate();
}


void Interp4Rotate::PrintSyntax() const{
  cout << "   Rotate  NazwaObiektu  SzybkoscKatowa[deg/s]  NazwaOsi KatObrotu[deg]" << endl;
}