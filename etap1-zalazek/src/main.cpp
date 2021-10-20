#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#define ERROR_noLib 1
#define ERROR_createCmd 2

using namespace std;


int main()
{

  void *pFun;

  /*
   * Wtyczka Move
   */
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Move)(void);

  

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
    return ERROR_noLib;
  }


  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return ERROR_createCmd;
  }
  pCreateCmd_Move = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);


  Interp4Command *pCmd = pCreateCmd_Move();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  /*
   * Wtyczka Set
   */
  void *pLibHnd_Set = dlopen("libInterp4Set.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Set)(void);

  if (!pLibHnd_Set) {
    cerr << "!!! Brak biblioteki: Interp4Set.so" << endl;
    return ERROR_noLib;
  }

  pFun = dlsym(pLibHnd_Set,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd Set" << endl;
    return ERROR_createCmd;
  }
  pCreateCmd_Set = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);


  pCmd = pCreateCmd_Set();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;

  delete pCmd;
  
  dlclose(pLibHnd_Move);
  dlclose(pLibHnd_Set);
}
