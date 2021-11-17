#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"


extern "C"{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Move"; }
}

Interp4Command *CreateCmd(void){
  return Interp4Move::CreateCmd();
}


Interp4Move::Interp4Move() : _object_name("no_name"), _Speed_mmS(0), _Path_length(0){
}


void Interp4Move::PrintCmd() const { 
  cout << GetCmdName() << " " << _object_name << " " << _Speed_mmS << " " << _Path_length << endl;
}

const char *Interp4Move::GetCmdName() const{
  return ::GetCmdName();
}

std::string Interp4Move::GetObjName() const
{
  return _object_name;
}

bool Interp4Move::ExecCmd(MobileObj *pMobObj, int Socket) const{
  return true;
}


bool Interp4Move::ReadParams(std::istream &Strm_CmdsList){
  Strm_CmdsList >> _object_name >> _Speed_mmS >> _Path_length;
  return !Strm_CmdsList.fail();
}

Interp4Command *Interp4Move::CreateCmd(){
  return new Interp4Move();
}


void Interp4Move::PrintSyntax() const{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}