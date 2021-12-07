#include "Sender.hh"

using namespace std;

void Sender::Watching_and_Sending(){
  while (ShouldCountinueLooping()){
    if (!_pScn->IsChanged()){
      usleep(1000);
      continue;
    }
    _pScn->LockAccess();

    // Wczytanie listy obiektów mobilnych
    // (obiektów typu std::map<std::string, std::shared_ptr<MobileObj>>)
     MobileObjList MobileObjects = _pScn->GetMobObjects();

    // Utworzenie listy na wskaźniki do obiektów mobilnych
    // Wskaźniki będą pobierane z drugiego elementu każdej pary powyższej listy
     std::vector<std::shared_ptr<MobileObj>> MobileObjectsList;


    // Utworzenie iteratora do przeszukania listy obiektów mobilnych
    MobileObjList::iterator iterator;

    // Przepisanie wskaźników na obiekty mobilne
    for (iterator = MobileObjects.begin(); iterator != MobileObjects.end(); iterator++){
      MobileObjectsList.push_back(iterator->second);
    }


    for (auto spObj : MobileObjectsList){

      std::string msg = "UpdateObj ";
      msg += spObj->GetStateDesc();

      Send(msg.c_str());
    }

    _pScn->CancelChange();
    _pScn->UnlockAccess();
  }
}

bool Sender::Connect(){
  if (!OpenConnection(_Socket)){
    cout << endl << "Połączenie z serwerem nie udalo sie" << endl;
    return true;
  }
  else{
    cout << endl << "Połączenie z serwerem udalo sie" << endl;
    return false;
  }
}

int Sender::Send(const char *sMesg){
  ssize_t IlWyslanych;
  ssize_t IlDoWyslania = (ssize_t)strlen(sMesg);
  
  while ((IlWyslanych = write(_Socket, sMesg, IlDoWyslania)) > 0){
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0){
    cerr << "*** Blad przeslania napisu." << endl;
  }
  return 0;
}

bool OpenConnection(int &rSocket){
  struct sockaddr_in DaneAdSerw;

  bzero((char *)&DaneAdSerw, sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);

  rSocket = socket(AF_INET, SOCK_STREAM, 0);

  if (rSocket < 0){
    cerr << "*** Blad otwarcia gniazda." << endl;
    return false;
  }

  if (connect(rSocket, (struct sockaddr *)&DaneAdSerw, sizeof(DaneAdSerw)) < 0){
    cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
    return false;
  }
  return true;
}

Sender::Sender(Scene *pScn) : _pScn(pScn){
  Thread4Sending = std::thread(Fun_CommunicationThread, this);
}

Sender::~Sender(){
  Send("CLOSE \n");
  CancelCountinueLooping();
  Thread4Sending.join();
  close(_Socket);
}

void Fun_CommunicationThread(Sender *pSender){
  pSender->Watching_and_Sending();
}