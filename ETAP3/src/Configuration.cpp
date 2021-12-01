#include "Configuration.hh"

void Configuration::AddMobObj(const std::string &name, Vector3D &Scale, const std::string &Rgb, Vector3D &Shift,Vector3D &Trans, Vector3D &Rot){
    auto NewMobileObj = std::make_shared<MobileObj>();

    NewMobileObj->SetName(name.c_str());
    NewMobileObj->SetScale(Scale);
    NewMobileObj->SetColour(Rgb);
    NewMobileObj->SetShift(Shift);
    NewMobileObj->SetPosition_m(Trans);
    NewMobileObj->SetAng_Roll_deg(Rot[0]);  
    NewMobileObj->SetAng_Pitch_deg(Rot[1]); 
    NewMobileObj->SetAng_Yaw_deg(Rot[2]); 

    ObList.insert({name, NewMobileObj});
}

void Configuration::AddLibName(const std::string &LibName){
    LibList.push_back(LibName);
}
