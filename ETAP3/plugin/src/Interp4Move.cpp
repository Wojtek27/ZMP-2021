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

std::string Interp4Move::GetObjName() const{
  return _object_name;
}

bool Interp4Move::ExecCmd(MobileObj *pMobObj, AccessControl *pAccCtrl) const{
  
  double Speed_mS = _Speed_mmS / 1000;
  Vector3D position;
  double angle = pMobObj->GetAng_Yaw_deg();

  // Animacja i wykonywanie ruchu
  for (int s = 0; s < 10 * _Path_length; s++){
    
    // Zablokowanie dostępu
    pAccCtrl->LockAccess();

    // Pobranie aktualnej pozycji obiektu
    Vector3D position = pMobObj->GetPosition_m();

    // Pozycja na osiach X, Y oraz Z
    // Każdy "s" to jedna sekunda drogi,
    // a Speed_mS to prędkość w metrach na sekundę,
    // więc Speed_mS wyznacza odcinek drogi do przebycia.
    position[0] += /*Speed_mS * */ 0.1 * cos(PI * angle / 180);
    position[1] += /*Speed_mS * */ 0.1 * sin(PI * angle / 180);
    position[2] += _Speed_mmS * sin(PI * angle / 180);

    // Zapisanie nowej pozycji obiektu
    pMobObj->SetPosition_m(position);
    
    // Zapisanie zmian
    pAccCtrl->MarkChange();
    
    // Odblokowanie dostępu
    pAccCtrl->UnlockAccess();
    usleep(50000 * 1 / Speed_mS);
  }
  cout << endl << pMobObj->GetStateDesc();
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