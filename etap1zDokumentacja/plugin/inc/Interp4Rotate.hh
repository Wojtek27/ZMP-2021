#ifndef COMMAND4ROTATE_HH
#define COMMAND4ROTATE_HH

#ifndef __GNUG__
#pragma interface
#pragma implementation
#endif

#include "Interp4Command.hh"

using namespace std;

/*!
 * \file
 * \brief Definicja klasy Interp4Rotate
 *
 * Plik zawiera definicję klasy Interp4Rotate, modelującej możliwość obrotu robota wokół dowolnej osi. 
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego obrót w dowolnej osi o dowolny kąt z nieujemną prędkością.
 */
class Interp4Rotate : public Interp4Command
{
  /*!
   *  \brief Nazwa obiektu
   */  
  string objectName;   

  /*!
   *  \brief Prędkość obrotowa, z jaką robot ma się obrócić.
   */  
  int AngularSpeedDegS;

  /*!
   *  \brief Oś, wokół której robota ma się obrócić.
   */  
  char Axis; 

  /*!
   *  \brief Kąt, o jaki robot ma się obrócić.
   */             
  int RotationAngleDeg; // kat obrotu

public:
  
  /*!
  * \brief Konstrukor
  */
  Interp4Rotate();
  
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