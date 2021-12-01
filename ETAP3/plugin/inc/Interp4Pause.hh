#ifndef COMMAND4PAUSE_HH
#define COMMAND4PAUSE_HH

#ifndef __GNUG__
#pragma interface
#pragma implementation
#endif

#include "Interp4Command.hh"

using namespace std;

/*!
 * \file
 * \brief Definicja klasy Interp4Pause
 *
 * Plik zawiera definicję klasy Interp4Pause, modelującej zatrzymanie robota przez zadany czas.
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza przerwę w wykonywaniu czynności
 *
 *  Klasa modeluje polecenie zatrzymania się robota przez zadany czas. Robot nie wykonuje wtedy żadnej czynności.
 */
class Interp4Pause : public Interp4Command
{
 
  /*!
   * \brief Nazwa robota do zatrzymania. 
   */
  string _object_name;

  /*!
   * \brief Czas, przez jaki robot będzie zatrzymany. Wartość podawana w milisekundach.
   */
  int _Pause_mS;

public:
  
  /*!
   * \brief Konstruktor domyślny klasy.
   */
  Interp4Pause();

  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
   */
  virtual void PrintCmd() const;

  /*!
   * \brief Wyświetla składnię polecenia
   */
  virtual void PrintSyntax() const;

  /*!
   * \brief Wyświetla nazwę polecenia
   */
  virtual const char *GetCmdName() const;

  /*!
   * \brief Wyświetla nazwę obiektu.
   */
  virtual std::string GetObjName() const;

  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   */
  virtual bool ExecCmd(MobileObj *pMobObj, AccessControl *pAccCtrl) const;

  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  virtual bool ReadParams(std::istream &Strm_CmdsList);

  /*!
   * \brief Wyświetla wartości wczytanych parametrów
   */
  virtual void PrintParams() {}

  /*!
   * \brief Tworzy interfejs komendy.
   */
  static Interp4Command *CreateCmd();
};

#endif