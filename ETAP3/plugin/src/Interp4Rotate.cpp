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


bool Interp4Rotate::ExecCmd(MobileObj *pMobObj, AccessControl *pAccCtrl) const{
  double angle;
  Vector3D tmp_pos, zeros;

  zeros[0] = 0;
  zeros[1] = 0;
  zeros[2] = 0;

  switch (Axis){
  case 'X':
    angle = pMobObj->GetAng_Roll_deg();
    break;
  case 'Y':
    angle = pMobObj->GetAng_Pitch_deg();
    break;
  case 'Z':
    angle = pMobObj->GetAng_Yaw_deg();
    break;
  }

  // Animacja i wykonywanie ruchu
  for (int s = 0; s < RotationAngleDeg; s += 5){
    // Zablokowanie dostępu
    pAccCtrl->LockAccess();

    // Wykonanie obrotu
    // Każdy "s" to jedna sekunda obrotu,
    // a _Angular_speed_degS to prędkość obrotu w stopniach na sekundę,
    // więc _Angular_speed_degS wyznacza kąt obrotu.
    angle += 5; 

    // Zapisanie nowych kątów
    switch (Axis){
    case 'X':
      pMobObj->SetAng_Roll_deg(angle);
      break;
    case 'Y':
      pMobObj->SetAng_Pitch_deg(angle);
      break;
    case 'Z':
      pMobObj->SetAng_Yaw_deg(angle);
      break;
    }
  
    // Zapisanie zmian
    pAccCtrl->MarkChange();

    // Odblokowanie dostępu
    pAccCtrl->UnlockAccess();
    usleep(100000);   
  }
  return true;
}

std::string Interp4Rotate::GetObjName() const{
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