#include "Set4LibInterfaces.hh"

// Konstruktor
Set4LibraryInterfaces::Set4LibraryInterfaces(){
    LoadLibrary("libs/libInterp4Move.so");
    LoadLibrary("libs/libInterp4Set.so");
    LoadLibrary("libs/libInterp4Rotate.so");
    LoadLibrary("libs/libInterp4Pause.so");
}

Set4LibraryInterfaces::~Set4LibraryInterfaces(){

}

void Set4LibraryInterfaces::LoadLibrary(string path){
    //shared_ptr<LibInterface> pLibrary = make_shared<LibInterface>(path);
    auto pLibrary = make_shared<LibraryInterface>(path);
    _libMap.insert({pLibrary->name, pLibrary});
}

LibMap::iterator Set4LibraryInterfaces::FindLibrary(string libName){
    return _libMap.find(libName);
}

LibMap::iterator Set4LibraryInterfaces::EndMap(){
    return _libMap.end();
}
