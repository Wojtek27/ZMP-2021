#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"



extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}


Interp4Command* CreateCmd(void){
  return Interp4Set::CreateCmd();
}


Interp4Set::Interp4Set(): _cordX(0), _cordY(0), _angX(0), _angY(0), _angZ(0){}


void Interp4Set::PrintCmd() const{
  cout << GetCmdName() << " Obj_A " << _cordX << " " << _cordY << " " << _angX << " " << _angY << " " << _angZ << endl;
}


const char* Interp4Set::GetCmdName() const{
  return ::GetCmdName();
}

bool Interp4Set::ExecCmd( MobileObj  *pMobObj,  int  Socket) const{
  return true;
}


bool Interp4Set::ReadParams(std::istream& Strm_CmdsList){
  Strm_CmdsList >> _object_name >> _cordX >> _cordY >> _angX >> _angY >> _angZ;
  return !Strm_CmdsList.fail();
}


Interp4Command* Interp4Set::CreateCmd(){
  return new Interp4Set();
}


void Interp4Set::PrintSyntax() const{
  cout << "   Set  NazwaObiektu  wsp_X  wsp_Y  kat_OX kat_OY kat_OZ" << endl;
}

