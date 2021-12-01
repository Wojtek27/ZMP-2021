#ifndef SENDER_HH
#define SENDER_HH

#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>
#include "AccessControl.hh"
#include "Port.hh"
#include "Scene.hh"

using namespace std;

/*!
 * \file
 * \brief Definicja klasy Sender.
 *
 * Plik zawiera definicję klasy Sender, modelującej nadajnik poleceń dla obiektów na scenie oraz potrzebne do tego funkcje.
 */

/*!
 * \brief Ilość stanów każdego z obiektów.
 *
 * Ilość stanów każdego z obiektów.
 * Podział na kolejne stany obiektów wykorzystywany jest
 * do animacji ruchu obiektów.
 */
#define STATES_NUMBER 8

/*!
 * \brief Modeluje nadajnik poleceń odzwierciedlających aktualny stan sceny.
 *
 * Modeluje nadajnik poleceń odzwierciedlających aktualny stan sceny.
 * W tym celu monitoruje zmiany na scenie, a gdy je wykryje przesyła
 * informacje o aktualnej pozycji wszystkich obiektów.
 */
class Sender {
  
  /*!
   * \brief Wartość tego pola decyduje o kontynuacji wykonywania wątku.
   * 
   * Wartość tego pola decyduje o kontynuacji wykonywania wątku.
   * W przypadku wartości \p true, pętla wątku będzie wykonywana.
   * Natomiast wartość \p false powoduje przerwanie pętli.
   */
  volatile bool _ContinueLooping = true;
  
  /*!
   * \brief Deskryptor gniazda sieciowego, poprzez które wysyłane są polecenia.
   */
  int _Socket = 0;
  
  /*!
   * \brief Wskaźnik na scenę, które stan jest przesyłany w postaci
   *        poleceń do serwera graficzneg.
   */
  Scene *_pScn = nullptr;

  /*!
   * \brief Wątek odpowiedzialny za wysyłanie informacji na serwer
   */
  std::thread Thread4Sending;

public:
  
  /*!
   * \brief Inicjalizuje obiekt deskryptorem gniazda i wskaźnikiem
   *        na scenę, na zmianę stanu które będzie ten obiekt reagował.
   */
  Sender(Scene *pScn);

  /*!
   * \brief Destruktor
   */
  ~Sender();

  /*!
   * \brief Sprawdza, czy pętla wątku może być wykonywana.
   * 
   * Sprawdza, czy pętla wątku może być wykonywana.
   * \retval true - pętla wątku może być nadal wykonywana.
   * \retval false - w przypadku przeciwnym.
   */
  bool ShouldCountinueLooping() const { return _ContinueLooping; }
  
  /*!
   * \brief Powoduje przerwanie działania pętli wątku.
   *
   * Powoduje przerwanie działania pętli wątku.
   * \warning Reakcja na tę operację nie będize natychmiastowa.
   */
  void CancelCountinueLooping() { _ContinueLooping = false; }
  
  /*!
   * \brief Ta metoda jest de facto treścią wątku komunikacyjnego
   *
   * Przegląda scenę i tworzy odpowiednie polecenia, a następnie
   * wysyła je do serwera.
   * \param[in] Socket - deskryptor gniazda sieciowego, poprzez które
   *                     wysyłane są polecenia.
   */
  void Watching_and_Sending();
  
  /*!
   * \brief  Metofa, dzieki której nawiazane zostaje polaczenie
   */
  bool Connect();

 /*!
  * \brief Wysyła napis do poprzez gniazdo sieciowe.
  *
  * Wysyła napis do poprzez gniazdo sieciowe.
  * \param[in] Sk2Server - deskryptor gniazda sieciowego, poprzez które 
  *                        ma zostać wysłany napis w sensie języka C.
  * \param[in] sMesg - zawiera napis, który ma zostać wysłany poprzez
  *                    gniazdo sieciowe.
  */
  int Send(const char *sMesg);
};

/*!
 * Otwiera połączenie sieciowe
 * \param[out]  rSocket - deskryptor gniazda, poprzez które może być
 *                        realizowana komunikacja sieciowa.
 */
bool OpenConnection(int &rSocket);

/*!
 * \brief Funkcja jest treścią wątku komunikacyjnego
 * 
 * Funkcja jest treścią wątku komunikacyjnego.
 * \param[in] rSender - odpowiada za śledenie zmian na scenie 
 *                      i przesyłanie do serwera graficznego
 *                      aktualnego stanu sceny, gdy uległ on zmianie.
 */
void Fun_CommunicationThread(Sender *pSender);

#endif