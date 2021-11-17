#include "Scene.hh"

Scene::Scene(){}

Scene::~Scene(){}

void Scene::LoadMobObjects(ListMobileOb &ListMobileOb){
    MobileObjects = ListMobileOb;
}

void Scene::Print(){
    std::cout << "\n Istniejące obiekty mobilne: ";

    for(ListMobileOb::iterator i = MobileObjects.begin(); i != MobileObjects.end(); i++){
        std::cout << "\n \t" << i->first;
    }
    std::cout << endl;
}

ListMobileOb Scene::GetMobObjects(){
    return MobileObjects;
}

std::shared_ptr<MobileObj> Scene::FindMobObjects(std::string name){
    auto iterator = MobileObjects.find(name);
    if(iterator == MobileObjects.end()){
        return nullptr;
    }else{
        return iterator->second;
    }
}

bool Scene::ExistMobObjects(std::string name){
    auto iterator = MobileObjects.find(name);
    if(iterator == MobileObjects.end()){
        return false;
    }else{
        return true;
    }
}