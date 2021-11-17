#ifndef SCENE_HH
#define SCENE_HH

#include "MobileObj.hh"
#include "AccessControl.hh"
#include <string>
#include <map>
#include <memory>

using namespace std;

/*!
 * \file
 * \brief Definicja klasy Scene
 *
 * Plik zawiera definicje klasy Scene, która przechowuje liste obiektów mobilnych
 */

/*!
 * \brief Typ definiujący listę obiektów mobilnych. Komendy przechowywane są w postaci par, nazwy komendy (obiekt typu string) i adresu (wskaźnik shared_ptr). 
 */
typedef std::map<std::string, std::shared_ptr<MobileObj>> ListMobileOb;


/*!
 * \brief Odpowiada za modelowanie sceny dla obiektów mobilnych
 */
class Scene : public AccessControl{ 
    private:

    /*!
     * \brief Lista obiektów z klasy MobileObj
     */
    ListMobileOb MobileObjects;

    public:

    /*!
     * \brief Konsturktor
     */
    Scene();

    /*!
     * \brief Dekonsturktor
     */
    ~Scene();

     /*!
     * \brief Ładuje listę obiektów mobilnych do sceny
     *
     * Podana w parametrze lista obiektów mobilnych jest kopiowana do atrybutu SetMobileOb
     * 
     * \param[in] ListMobileOb - lista obiektów mobilnych do załadowania do sceny
     */
    void LoadMobObjects(ListMobileOb &ListMobileOb);
    
    /*!
     * \brief Zwraca listę obiektów mobilnych
     */
    ListMobileOb GetMobObjects();

    /*!
     * \brief Wyszukuje i zwraca wskaźnik na obiekt o nazwie podanej w parametrze
     * 
     * \param[in] name - nazwa obiektu mobilnego do wyszukania na scenie
     * \return Zwraca wskaźnik na znaleziony obiekt lub nullptr, gdy obiekt nie zostanie znaleziony
     */
    std::shared_ptr<MobileObj> FindMobObjects(std::string name);

    /*!
     * \brief Sprawdza, czy na scenie istnieje obiekt mobilny o podanej nazwie
     * 
     * \param[in] name - nazwa obiektu mobilnego do wyszukania na scenie
     * \return Zwraca <c>True</c>, gdy obiekt zostanie znaleziony lub <c>False</c>, gdy nie zostanie znaleziony.
     */
    bool ExistMobObjects(std::string name);

    /*!
     * \brief Odpowiada za wyświetlenie nazwy istniejących na scenie obiektów mobilnych.
     */
    void Print();


};


#endif