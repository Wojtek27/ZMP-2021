#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include "LibInterface.hh"
#include <memory>

typedef map<std::string, std::shared_ptr<LibraryInterface>> LibMap;

class Set4LibraryInterfaces{
private:
  LibMap _libMap;

public:
  Set4LibraryInterfaces();
  ~Set4LibraryInterfaces();
  void LoadLibrary(string path);
  LibMap::iterator FindLibrary(string libName);
  LibMap::iterator EndMap();
};

#endif
