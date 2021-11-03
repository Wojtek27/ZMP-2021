#ifndef COMMAND4ROTATE_HH
#define COMMAND4ROTATE_HH

#ifndef __GNUG__
#pragma interface
#pragma implementation
#endif

#include "Interp4Command.hh"

using namespace std;

class Interp4Rotate : public Interp4Command
{
  
  string objectName;     // nazwa obiektu
  int AngularSpeedDegS; // predkosc obrotowa
  char Axis;              // os obrotu
  int RotationAngleDeg; // kat obrotu

public:
  
  Interp4Rotate();
  
  virtual void PrintCmd() const;
  
  virtual void PrintSyntax() const;
 
  virtual const char *GetCmdName() const;
  
  virtual bool ExecCmd(MobileObj *pMobObj, int Socket) const;
 
  virtual bool ReadParams(std::istream &Strm_CmdsList);
  
  virtual void PrintParams() {}

  static Interp4Command *CreateCmd();
};

#endif