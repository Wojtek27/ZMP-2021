#ifndef COMMAND4MOVE_HH
#define COMMAND4MOVE_HH

#ifndef __GNUG__
#pragma interface
#pragma implementation
#endif

#include "Interp4Command.hh"

using namespace std;


class Interp4Move : public Interp4Command
{
  
  string _object_name; // nazwa obiektu
  double _Speed_mmS;   // predkosc obiektu
  double _Path_length; // dystans

public:
 
  Interp4Move();

  virtual void PrintCmd() const;

  virtual void PrintSyntax() const;

  virtual const char *GetCmdName() const;

  virtual bool ExecCmd(MobileObj *pMobObj, int Socket) const;

  virtual bool ReadParams(std::istream &Strm_CmdsList);

  virtual void PrintParams() {}

  static Interp4Command *CreateCmd();
};

#endif