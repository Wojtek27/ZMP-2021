#ifndef COMMAND4PAUSE_HH
#define COMMAND4PAUSE_HH

#ifndef __GNUG__
#pragma interface
#pragma implementation
#endif

#include "Interp4Command.hh"

using namespace std;

class Interp4Pause : public Interp4Command
{
 
  string _object_name;
  int _Pause_mS;

public:
  
  Interp4Pause();
  
  virtual void PrintCmd() const;
  
  virtual void PrintSyntax() const;
 
  virtual const char *GetCmdName() const;
  
  virtual bool ExecCmd(MobileObj *pMobObj, int Socket) const;
  
  virtual bool ReadParams(std::istream &Strm_CmdsList);
  
  virtual void PrintParams() {}
  
  static Interp4Command *CreateCmd();
};

#endif