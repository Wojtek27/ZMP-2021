#include "Sender.hh"

using namespace std;

void Sender::Watching_and_Sending()
{
  while (ShouldCountinueLooping()){
    if (!_pScn->IsChanged()){
      usleep(10000);
      continue;
    }
    _pScn->LockAccess();

    // Wczytanie listy obiektów mobilnych
    // (obiektów typu std::map<std::string, std::shared_ptr<MobileObj>>)
    ListMobileOb MobileObjects = _pScn->GetMobObjects();

    // Utworzenie listy na wskaźniki do obiektów mobilnych
    // Wskaźniki będą pobierane z drugiego elementu każdej pary powyższej listy
    std::vector<std::shared_ptr<MobileObj>> MobileObjectsList;

    // Utworzenie iteratora do przeszukania listy obiektów mobilnych
    ListMobileOb::iterator iterator;

    // Przepisanie wskaźników na obiekty mobilne
    for (iterator = MobileObjects.begin(); iterator != MobileObjects.end(); iterator++){
      MobileObjectsList.push_back(iterator->second);
    }

    //------- Przeglądanie tej kolekcji to uproszczony przykład

    for (auto spObj : MobileObjectsList)
    {

      // Konwersja do zwykłego wskaźnika
      MobileObj *pObj = spObj.get();

      std::string ObjState = pObj->GetStateDesc();
      cout << "Wysyłam: " << ObjState;
      Send(_Socket, ObjState.c_str()); // Tu musi zostać wywołanie odpowiedniej
                                       // metody/funkcji gerującej polecenia dla serwera.
    }

    _pScn->CancelChange();
    _pScn->UnlockAccess();
  }
}

int Send(int Sk2Server, const char *sMesg)
{
  ssize_t IlWyslanych;
  ssize_t IlDoWyslania = (ssize_t)strlen(sMesg);

  while ((IlWyslanych = write(Sk2Server, sMesg, IlDoWyslania)) > 0)
  {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0)
  {
    cerr << "*** Blad przeslania napisu." << endl;
  }
  return 0;
}

bool OpenConnection(int &rSocket)
{
  struct sockaddr_in DaneAdSerw;

  bzero((char *)&DaneAdSerw, sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);

  rSocket = socket(AF_INET, SOCK_STREAM, 0);

  if (rSocket < 0)
  {
    cerr << "*** Blad otwarcia gniazda." << endl;
    return false;
  }

  if (connect(rSocket, (struct sockaddr *)&DaneAdSerw, sizeof(DaneAdSerw)) < 0)
  {
    cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
    return false;
  }
  return true;
}

bool ChangeState(Scene &Scn) //MobileObj *pObj, AccessControl  *pAccCtrl)
{                            /*
  bool Changed;
  while (true)
  {
    Scn.LockAccess(); // Zamykamy dostęp do sceny, gdy wykonujemy
                      // modyfikacje na obiekcie.
    for (MobileObj &rObj : Scn._Container4Objects)
    {
      if (!(Changed = rObj.IncStateIndex()))
      {
        Scn.UnlockAccess();
        return false;
      }
    }
    Scn.MarkChange();
    Scn.UnlockAccess();
    usleep(300000);
  }*/
  return true;
}

void Fun_CommunicationThread(Sender *pSender)
{
  pSender->Watching_and_Sending();
}