//#include <cassert>
//#include "Interp4Command.hh"
#include "Set4LibInterfaces.hh"
//#include "MobileObj.hh"
//#include <sstream>
#include <cstdio>
//#include "Configuration.hh"
#include "xmlinterp.hh"
#include "Scene.hh"

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"
//#include <iostream>
#include <list>

#include "Sender.hh"

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
bool ExecActions(istringstream &iStrm, Set4LibraryInterfaces &LibraryList , Scene *ProgramScene){
  string command_name, object_name;

  while (iStrm >> command_name){ // sprawdza, czy w strumieniu jest jeszcze jakaś komenda
    
    // Przechowywanie watkow
    std::vector<std::thread> cmd_threads;

    // Sprawdzanie czy zawartość odczytana to poczatek bloku polnecen
    if(command_name == "Begin_Parallel_Actions"){
      std::cout << endl << "Begin_Parallel_Actions";
    }else{
      cout << endl << " Brak Begin_Parallel_Actions";
      return false;
    }

    /// Odczytuje blok
    while (true){
      // Pobiera nową wartosć
      iStrm >> command_name;

      // Sprawdza, czy to już koniec bloku
      if (command_name == "End_Parallel_Actions"){
        std::cout << endl << "End_Parallel_Actions";

        // Kończenie wątkow
        for (thread &cmd_thread : cmd_threads){
          cmd_thread.join();
          }

        break;
      }

      // Sprawdzenie, czy komenda o podanej nazwie istnieje
      LibMap::iterator cmd_iterator = LibraryList.FindLibrary(command_name);
      if (cmd_iterator == LibraryList.EndMap()){
        cerr << "Komenda o nazwie '" << command_name << "' nie istnieje" << endl;
        return false;
      }

      // Tworzy komendę na podstawie funkcji wtyczki
      Interp4Command *pCommand = cmd_iterator->second->pCreateCmd();
      if (!pCommand->ReadParams(iStrm)){
        cerr << "Czytanie parametrów komendy '" << command_name << "' nie powiodło się" << endl;
        return false;
      }

      // Wskaźnik na obiekt mobilny
      std::shared_ptr<MobileObj> object_ptr;

      if (command_name != "Pause"){
        // Pobranie nazwy obiektu, które dotyczy komenda
        object_name = pCommand->GetObjName();

        // Sprawdza, czy istnieje obiekt o podanej nazwie
        if (!ProgramScene->ExistMobObjects(object_name)){
          cerr << "Obiekt o nazwie '" << object_name << "' nie istnieje" << endl;
          return false;
        }
        object_ptr = ProgramScene->FindMobObjects(object_name);
      }
      else{
        object_ptr = nullptr;
      }
      pCommand->PrintCmd();

      // Tworzy nowy wątek wykonujący odczytane polecenie
      cmd_threads.push_back(std::thread(&Interp4Command::ExecCmd, pCommand, object_ptr.get(), ProgramScene));
      }
    usleep(100000);
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

            cerr << " Blad! " << endl
                 << " Plik:  " << sSystemId << endl
                 << " Linia: " << Exception.getLineNumber() << endl
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

void SendMobileObjectsToServer(Scene &Scn, Sender &ClientSender){
  auto MobileObjects = Scn.GetPtrs();

  for (auto MobileObject : MobileObjects){
    auto object = MobileObject.get();

    string msg = "AddObj ";
    msg += object->GetStateDesc();

    cout << endl << msg << endl;

    ClientSender.Send(msg.c_str());
  }
}

int main(int argc, char **argv){

  Configuration Config;              // Obiekt konfiguracji, konfiguracja zostanie wczytana po odczytaniu pliku XML
  ListOfLibs ConfigLibraryList;      // Lista bibliotek odczytana z pliku konfiguracyjnego
  ListMobileOb MobileObjList;        // Lista obiektów mobilnych odczytana z pliku konfiguracyjnego
  Set4LibraryInterfaces LibraryList; // Lista (zestaw) wczytanych bibliotek
  Scene ProgramScene;                // Scena, lista obiektów mobilnych
  Sender ClientSender(&ProgramScene);
  istringstream iStrm;
  
  // Łączenie z serwerem
  ClientSender.Connect();

  // Sprawdzanie liczby argumentów
  if (argc != 2){
    cout << endl << "Niepoprawna liczba argumentów" << endl;
    return 2;
  }

  // Wczytanie konfiguracji z pliku XML
  if (!ReadFile("config/config.xml", Config)){
    cout << endl << "Wczytywanie pliku konfiguracji config/config.xml nie powiodło się" << endl;
    return 3;
  }

  // Ładowanie bibliotek
  ConfigLibraryList = Config.GetLibList();
  for (long unsigned int i = 0; i < ConfigLibraryList.size(); i++){
    LibraryList.LoadLibrary(ConfigLibraryList.at(i));
  }

  // Wczytanie obiektów mobilnych (odczytanych z pliku XML)
  MobileObjList = Config.GetObList();
  ProgramScene.LoadMobObjects(MobileObjList);
  SendMobileObjectsToServer(ProgramScene, ClientSender);
  ProgramScene.Print(); // testowo wyświetla nazwy obiektów

  // Czytanie pliku preprocesorem do strumienia
  ExecPreprocesor(argv[1], iStrm);
  cout << endl << "Pokonywana trasa robota:" << endl << iStrm.str() << endl;

  // Parsowanie pliku na komendy z parametrami
  if (!ExecActions(iStrm, LibraryList, &ProgramScene))
    return 4;
}