#include <cassert>
//#include "Interp4Command.hh"
#include "Set4LibInterfaces.hh"
#include "MobileObj.hh"
#include <sstream>
#include <cstdio>

#define LINE_SIZE 500

using namespace std;

bool ExecPreprocesor(const char *FileName, istringstream &IStrm4Cmds){
  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;

  Cmd4Preproc += FileName;
  FILE *pProc = popen(Cmd4Preproc.c_str(), "r");

  if (!pProc)
    return false;

  while (fgets(Line, LINE_SIZE, pProc)){
    OTmpStrm << Line;
  }

  IStrm4Cmds.str(OTmpStrm.str());

  return pclose(pProc) == 0;
}

bool ExecActions(istringstream &iStrm, Set4LibraryInterfaces &LibraryList){
  string commandName, objectName;

  while (iStrm >> commandName){ // sprawdza, czy w strumieniu jest jeszcze jakaś komenda
    // Sprawdzenie, czy komenda o podanej nazwie istnieje
    LibMap::iterator cmd_iterator = LibraryList.FindLibrary(commandName);
    if (cmd_iterator == LibraryList.EndMap()){
      cerr << "Komenda o nazwie '" << commandName << "' nie istnieje" << endl;
      return false;
    }

    // Tworzy komendę na podstawie funkcji wtyczki
    Interp4Command *pCommand = cmd_iterator->second->pCreateCmd();
    if (!pCommand->ReadParams(iStrm)){
      cerr << "Czytanie parametrów komendy '" << commandName << "' nie powiodło się" << endl;
      return false;
    }
    cout << "Komenda: ";
    pCommand->PrintCmd();
  }
  return true;
}

int main(int argc, char **argv){
  Set4LibraryInterfaces LibraryList; // Lista (zestaw) bibliotek
  istringstream iStrm;           // strumień danych wejściowych komend

  // Sprawdzanie liczby argumentów
  if (argc != 2){
    cout << endl
         << "Niepoprawna liczba argumentów"
         << endl;
    return 1;
  }

  // Czytanie pliku preprocesorem do strumienia
  ExecPreprocesor("program.cmd", iStrm);
  cout << endl
       << "Cały plik:"
       << endl
       << iStrm.str()
       << endl;

  // Parsowanie pliku na komendy z parametrami
  if (!ExecActions(iStrm, LibraryList))
    return 2;
}