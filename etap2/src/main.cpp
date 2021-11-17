#include <cassert>
#include "Set4LibInterfaces.hh"
#include "MobileObj.hh"
#include <sstream>
#include <cstdio>
#include "Configuration.hh"
#include "xmlinterp.hh"
#include "Scene.hh"

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
//#include <xercesc/util/XMLString.hpp>
#include <iostream>
#include <list>

#define LINE_SIZE 500

using namespace std;
using namespace xercesc;

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
 * \param[in] ProgramScene - Scena programu zawierające listę obiektów mobilnych.
 * \retval true  - Utworzenie komend zawartych w strumieniu z wartościami przepisanymi z pliku zakonńczyło się pomyślnie.
 * \retval false - Utworzenie komend zawartych w strumieniu z wartościami przepisanymi z pliku zakonńczyło się nie pomyślnie.
 */
bool ExecActions(istringstream &iStrm, Set4LibraryInterfaces &LibraryList , Scene &ProgramScene){
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
    if (!pCommand->ReadParams(iStrm))
    {
      cerr << "Czytanie parametrów komendy '" << command_name << "' nie powiodło się" << endl;
      return false;
    }

    object_name = pCommand->GetObjName();

    if (!ProgramScene.ExistMobObjects(object_name))
    {
      cerr << "Obiekt o nazwie '" << object_name << "' nie istnieje" << endl;
      return false;
    }

    auto object_ptr = ProgramScene.FindMobObjects(object_name);

    cout << " Komenda: ";
    pCommand->PrintCmd();

    pCommand->ExecCmd(object_ptr.get(), 0);
  }
  return true;
}

/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool ReadFile(const char* sFileName, Configuration &rConfig)
{
   try {
            XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar("config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/actions.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}


int main(int argc, char **argv){

/*
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
*/

  Configuration Config;          // Obiekt konfiguracji, konfiguracja zostanie wczytana po odczytaniu pliku XML
  ListOfLibs ConfigLibraryList;     // Lista bibliotek odczytana z pliku konfiguracyjnego
  ListMobileOb MobileObjList;   // Lista obiektów mobilnych odczytana z pliku konfiguracyjnego
  Set4LibraryInterfaces LibraryList; // Lista (zestaw) wczytanych bibliotek
  Scene ProgramScene;            // Scena, lista obiektów mobilnych

  //Sender   ClientSender(Socket4Sending,&Scn);
  //thread   Thread4Sending(Fun_CommunicationThread,&ClientSender);

  // Sprawdzanie liczby argumentów
  if (argc != 2)
  {
    cout << endl
         << "Niepoprawna liczba argumentów"
         << endl;
    return 1;
  }

  istringstream iStrm; // strumień danych wejściowych komend

  // Wczytanie konfiguracji z pliku XML
  if (!ReadFile("config/config.xml", Config))
  {
    cout << endl
         << "Wczytywanie pliku konfiguracji config/config.xml nie powiodło się"
         << endl;
    return 2;
  }

  // Ładowanie bibliotek
  ConfigLibraryList = Config.GetLibList();
  for (long unsigned int i = 0; i < ConfigLibraryList.size(); i++) // long unsigned int żeby uniknąć ostrzeżenia przy kompilacji
  {
    LibraryList.LoadLibrary(ConfigLibraryList.at(i));
  }

  // Wczytanie obiektów mobilnych (odczytanych z pliku XML)
  MobileObjList = Config.GetObList();
  ProgramScene.LoadMobObjects(MobileObjList);

  ProgramScene.Print(); // testowo wyświetla nazwy obiektów

  // Czytanie pliku preprocesorem do strumienia
  ExecPreprocesor("trasa.cmd", iStrm);
  cout << endl
       << "Cały plik:"
       << endl
       << iStrm.str()
       << endl;

  // Parsowanie pliku na komendy z parametrami
  if (!ExecActions(iStrm, LibraryList, ProgramScene))
    return 3;

}