#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include "Interp4Command.hh"
#include <string>
#include <map>
#include <dlfcn.h>
#include <iostream>

using namespace std;

class LibraryInterface{
private:

    void *libHandler;

public:
    string name;
    LibraryInterface(string path);
    ~LibraryInterface();
    Interp4Command *(*pCreateCmd)(void);
};
#endif