#ifndef COMMAND4MOVE_HH
#define COMMAND4MOVE_HH

#ifndef __GNUG__
#pragma interface
#pragma implementation
#endif

#include "Interp4Command.hh"

using namespace std;


/*!
 * \file
 * \brief Definicja klasy Interp4Move
 *
 * Plik zawiera definicję klasy Interp4Move, modelującej ruch do przodu robota mobilnego.
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu.
 *
 *  Klasa modeluje polecenie ruchu do przodu o zadany dystans z zadaną prędkością.
 */
class Interp4Move : public Interp4Command
{
  /*!
   *  \brief Nazwa robota do poruszenia.
   */
  string _object_name;

  /*!
   * \brief Prędkość, z jaką robot ma się poruszyć.
   */
  double _Speed_mmS;

  /*!
   * \brief Dystans, o jaki robot ma się poruszyć.
   */
  double _Path_length;
public:
 
  /*!
   * \brief Konstruktor domyślny klasy.
   */
  Interp4Move();

  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów).
   */
  virtual void PrintCmd() const;

  /*!
   * \brief Wyświetla składnię polecenia.
   */
  virtual void PrintSyntax() const;

  /*!
   * \brief Wyświetla nazwę polecenia.
   */
  virtual const char *GetCmdName() const;

  /*!
   * \brief Wyświetla nazwę obiektu.
   */
  virtual std::string GetObjName() const;

  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację.
   */
  virtual bool ExecCmd(MobileObj *pMobObj, AccessControl *pAccCtrl) const;
  
  
  /*!
   * \brief Czyta wartości parametrów danego polecenia.
   */
  virtual bool ReadParams(std::istream &Strm_CmdsList);

  /*!
   * \brief Wyświetla wartości wczytanych parametrów.
   */
  virtual void PrintParams() {}

  /*!
   * \brief Tworzy interfejs komendy.
   */
  static Interp4Command *CreateCmd();
};

#endif