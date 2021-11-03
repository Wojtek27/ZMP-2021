#include "LibInterface.hh"

// Konstruktor
LibraryInterface::LibraryInterface(string path){
    // Operacja otwierania biblioteki
    libHandler = dlopen(path.c_str(), RTLD_LAZY);

    if (!libHandler){
        cerr << "Brak biblioteki: " << path << endl;
    }
    else
        cout << "Znaleziono bibliotekę: " << path << endl;

    // Operacja wyszukiwania funkcji CreateCmd
    void *cmd = dlsym(libHandler, "CreateCmd");
    if (!cmd)
        cerr << "Nie znaleziono funkcji CreateCmd [" << path << "]" << endl;

    // Tworzenie komendy
    pCreateCmd = *reinterpret_cast<Interp4Command *(*)(void)>(cmd);
    Interp4Command *interp_cmd = pCreateCmd();
    name = interp_cmd->GetCmdName();
    delete interp_cmd;
}

// Destruktor
LibraryInterface::~LibraryInterface(){
    dlclose(libHandler);
}
