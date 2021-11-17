#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include "Interp4Command.hh"
#include <string>
#include <map>
#include <dlfcn.h>
#include <iostream>

using namespace std;

/*!
 * \file
 * \brief Definicja klasy LibInterface.
 *
 * Plik zawierający definicję klasy LibInterface, która odpowiada za modelowanie interfejsów pluginów odpowiadających za komendy.
 */

/*!
 * \brief Odpowiada za modelowanie interfejsu bibliotek odpowiedzialnych za sterowanie robotem.
 *
 */
class LibraryInterface{
private:

/*!
 * \brief Uchwyt dla biblioteki.
 */
    void *libHandler;

public:

/*! 
 * \brief Nazwa komendy odpowiadającej za sterowanie robotem.
 */
    string name;

/*!
 * \brief Konstruktor
 *
 * \param [in] - scieżka, gdzie znajduje się plik biblioteki dynamicznej.
 */ 
     LibraryInterface(string path);

/*!
 * \brief Deknstruktor
 */
    ~LibraryInterface();

/*!
 * 
 * \brief Odpowiada za utworzenie komendy.
 *
 * Wskaźnik do funkcji, która tworzy nowy obiekt klasy Interp4Command. 
 * Modeluje interfejs polecenia do sterowania robotem.
 */
    Interp4Command *(*pCreateCmd)(void);
};
#endif