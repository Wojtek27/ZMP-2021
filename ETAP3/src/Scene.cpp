#include "Scene.hh"

Scene::Scene(){}

Scene::~Scene(){}

void Scene::LoadMobObjects(MobileObjList &MobileObjList){
    MobileObjects = MobileObjList;
}

void Scene::Print(){
    std::cout << "\n Istniejące obiekty mobilne: ";

    for(MobileObjList::iterator i = MobileObjects.begin(); i != MobileObjects.end(); i++){
        std::cout << "\n \t" << i->first;
    }
    std::cout << endl;
}

MobileObjList Scene::GetMobObjects(){
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

std::vector<std::shared_ptr<MobileObj>> Scene::GetPtrs(){
    std::vector<std::shared_ptr<MobileObj>> Ptrs;

    for (MobileObjList::iterator i = MobileObjects.begin(); i != MobileObjects.end(); i++)
        Ptrs.push_back(i->second);

    return Ptrs;
}