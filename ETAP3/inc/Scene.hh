#ifndef SCENE_HH
#define SCENE_HH

#include "MobileObj.hh"
#include "AccessControl.hh"
#include <string>
#include <map>
#include <memory>
#include <vector>

using namespace std;

/*!
 * \file
 * \brief Definicja klasy Scene
 *
 * Plik zawiera definicje klasy Scene, która przechowuje liste obiektów mobilnych
 */

/*!
 * \brief Odpowiada za modelowanie sceny dla obiektów mobilnych
 */
class Scene : public AccessControl{ 
    private:

    /*!
     * \brief Lista obiektów z klasy MobileObj
     */
    MobileObjList MobileObjects;

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
    void LoadMobObjects(MobileObjList &MobileObjList);
    
    /*!
     * \brief Zwraca listę obiektów mobilnych
     */
    MobileObjList GetMobObjects();

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

    /*!
     * \brief Wyświetla nazwy istniejących na scenie obiektów mobilnych.
     */
    std::vector<std::shared_ptr<MobileObj>> GetPtrs();

};
#endif