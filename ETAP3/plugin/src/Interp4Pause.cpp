#include <iostream>
#include "Interp4Pause.hh"
#include "MobileObj.hh"



extern "C"{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Pause"; }
}


Interp4Command *CreateCmd(void){
  return Interp4Pause::CreateCmd();
}


Interp4Pause::Interp4Pause() : _object_name("no_name"), _Pause_mS(0){
}


void Interp4Pause::PrintCmd() const{
  cout << GetCmdName() << " " << _object_name << " " << _Pause_mS << endl;
}

const char *Interp4Pause::GetCmdName() const{
  return ::GetCmdName();
}


std::string Interp4Pause::GetObjName() const{
  return _object_name;
}

bool Interp4Pause::ExecCmd(MobileObj *pMobObj, AccessControl *pAccCtrl) const{
  
  // Zablokowanie dostępu
  pAccCtrl->LockAccess();

  // Czas odczekania
  usleep(_Pause_mS);
  
  // Odblokowanie dostępu
  pAccCtrl->UnlockAccess();
  usleep(100000);
  return true;
}


bool Interp4Pause::ReadParams(std::istream &Strm_CmdsList){
  Strm_CmdsList >> _object_name >> _Pause_mS;
  return !Strm_CmdsList.fail();
}


Interp4Command *Interp4Pause::CreateCmd(){
  return new Interp4Pause();
}


void Interp4Pause::PrintSyntax() const{
  cout << "   Pause  CzasPauzy[ms]" << endl;
}