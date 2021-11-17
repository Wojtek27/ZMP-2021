#include "Configuration.hh"

void Configuration::AddMobObj(const std::string &name, Vector3D &Scale, const std::string &Rgb){
    auto NewMobileObj = std::make_shared<MobileObj>();

    NewMobileObj->SetName(name.c_str());
    NewMobileObj->SetScale(Scale);
    NewMobileObj->SetColour(Rgb);

    ObList.insert({name, NewMobileObj});
}

void Configuration::AddLibName(const std::string &LibName){
    LibList.push_back(LibName);
}
