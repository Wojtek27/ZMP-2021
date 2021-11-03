#ifndef  COMMAND4SET_HH
#define  COMMAND4SET_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"
using namespace std;


class Interp4Set: public Interp4Command {
  
  double  _cordX; // wspolrzedna X
  double  _cordY; // wspolrzedna Y
  double  _angX; // kat X
  double  _angY; // kat Y
  double  _angZ; // kat Z
  string _object_name; // nazwa obiektu
 public:

  Interp4Set();  
  
  virtual void PrintCmd() const;
  
  virtual void PrintSyntax() const;
 
  virtual const char* GetCmdName() const;
  
  virtual bool ExecCmd( MobileObj  *pMobObj, int Socket) const;
  
  virtual bool ReadParams(std::istream& Strm_CmdsList);
 
  virtual void PrintParams() {}
 
  static Interp4Command* CreateCmd();
 };

#endif

