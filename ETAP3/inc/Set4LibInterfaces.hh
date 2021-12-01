#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include "LibInterface.hh"
#include <memory>

/*!
 * \file
 * \brief Definicja klasy Set4LibInterfaces
 * 
 * Plik zawiera definicje klasy, która odpowiada za modelowanie wtyczek (komend)
 *
 */

 /*!
 * \brief Typ, który odpowiada za  definiowanie listy komend. Komendy są przechowywane w postaci par nazw komendy (obiekt typu string) i adresu (wskaźnik shared_ptr). 
 */
typedef map<std::string, std::shared_ptr<LibraryInterface>> LibMap;

/*!
 * \brief Klasa odpowiada za modelowanie komend(wtyczek), które odpowiadaja za poruszanie robotem
 */
class Set4LibraryInterfaces{
  
private:

/*!
 * \brief Lista komend
 */
  LibMap _libMap;

public:

/*!
 * \brief Konstruktor
 *
 * Odpowiada za załadowanie 4 wtyczki i dodaje je do komend.
 */
  Set4LibraryInterfaces();

/*!
 * \brief Dekonstruktor
 */
  ~Set4LibraryInterfaces();

/*!
 * \brief Funkcja, która wczytuje konkretną bibliotekę.
 *
 * \param[in] path - scieżka, gdzie znajduje się plik biblioteki dynamicznej.
 */
  void LoadLibrary(string path);

/*!
 * \brief Funckja, która przeszukuje listę komend i zwraca jej numer. 
 *
 * \param[in] libName - komenda, która odnajduje bibliotekę.
 */
  LibMap::iterator FindLibrary(string libName);

/*!
 *
 * \brief Funkcja zwracająca kolejny iterator po ostanim iteratorze z listy.
 *
 */
  LibMap::iterator EndMap();
};

#endif
