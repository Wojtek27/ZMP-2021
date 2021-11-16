#ifndef  COMMAND4SET_HH
#define  COMMAND4SET_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"
using namespace std;


/*!
 * \file
 * \brief Definicja klasy Interp4Set
 *
 * Plik zawiera definicję klasy Interp4Set, modelującej ustawienie wybranego obiektu w zadanym miejscu.
 */

/*!
 * \brief Modeluje polecenie ustawienia robota mobilnego w zadanym miejscu.
 */
class Interp4Set: public Interp4Command {
  
  /*!
   * \brief Wspolrzedna X
   */
  double  _cordX; 
  
  /*!
   * \brief Wspolrzedna Y
   */
  double  _cordY; 
  
  /*!
   * \brief Kat X
   */
  double  _angX; 
  
  /*!
   * \brief Kat Y
   */
  double  _angY; 
  
  /*!
   * \brief Kat Z
   */
  double  _angZ; 

  /*!
   * \brief Nazwa obiektu
   */
  string _object_name; 
 public:

  /*!
   * \brief Konstruktor domyślny klasy.
   */
  Interp4Set();

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
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   */
  virtual bool ExecCmd(MobileObj *pMobObj, int Socket) const;

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

