#include <cassert>
#include "Set4LibInterfaces.hh"
#include "MobileObj.hh"
#include <sstream>
#include <cstdio>

#define LINE_SIZE 500

using namespace std;

/*!
 * \brief Funkcja czyta plik przy wykorzystaniu preprocesora.
 *
 * Funkcja odpowiada za interpretowanie pliku za pomoca preprocesora języka C, a następnie przepisuje go do strumienia.
 * \param[in]  FileName   - Nazwa pliku do interpretacji.
 * \param[out] IStrm4Cmds - Strumień, do którego zostanie zapisany zinterpretowany plik.
 * \retval true  - Interpretacja preprocesorem udała się, a plik został poprawnie zamknięty.
 * \retval false - Funkcja nie wykonała się poprawnie.
 */
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

/*!
 * \brief Funkcja odpowiada za uwtorzenie serii komend wraz z parametrami na podstawie zadanego strumienia.
 *
 * Funkcja interpretuje ciąg obiektów typu string w strumieniu utworzonym przez funkcję ExecPreprocesor(...) na serię komend wraz z parametrami.  
 * \param[in] iStrm       - Strumień utworzony przez funkcję ExecPreprocesor(...) z zapisanym plikiem do przeparsowania na komendy.
 * \param[in] LibraryList - Lista wszystkich komend, która jest potrzebna do sprawdzania poprawności zadanych komend w pliku.
 * \retval true  - Utworzenie komend zawartych w strumieniu z wartościami przepisanymi z pliku zakonńczyło się pomyślnie.
 * \retval false - Utworzenie komend zawartych w strumieniu z wartościami przepisanymi z pliku zakonńczyło się nie pomyślnie.
 */
bool ExecActions(istringstream &iStrm, Set4LibraryInterfaces &LibraryList){
  string command_name, object_name;

  while (iStrm >> command_name){ // sprawdza, czy w strumieniu jest jeszcze jakaś komenda
    
    // Sprawdzenie, czy komenda o podanej nazwie istnieje
    LibMap::iterator cmd_iterator = LibraryList.FindLibrary(command_name);
    if (cmd_iterator == LibraryList.EndMap()){
      cerr << "Taka komenda: " << command_name << "' nie istnieje" << endl;
      return false;
    }

    // Tworzy komendę na podstawie funkcji wtyczki
    Interp4Command *pCommand = cmd_iterator->second->pCreateCmd();
    if (!pCommand->ReadParams(iStrm)){
      cerr << "Czytanie parametrów komendy " << command_name << " nie udało się" << endl;
      return false;
    }
    cout << "Poszczególny ruch: ";
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
  ExecPreprocesor("trasa.cmd", iStrm);
  cout << endl << "Pokonywana trasa robota: " << endl << iStrm.str() << endl;

  // Parsowanie pliku na komendy z parametrami
  if (!ExecActions(iStrm, LibraryList))
    return 2;
}