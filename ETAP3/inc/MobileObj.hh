#ifndef MOBILEOBJ_HH
#define MOBILEOBJ_HH

#include <string>
#include "Vector3D.hh"
#include <sstream>
#include <map>
#include <memory>

/*!
 * \file
 * \brief Zawiera definicję klasy MobileObj
 *
 * Plik zawiera definicję klasy MobileObj.
 * Definicja to może być rozszerzona i zmienione mogą
 * być nazwy pól. Obowiązkowe są jedynie nazwy metod.
 */

   /*!
    * Nazwy pól klasy są jedynie propozycją i mogą być zmienione
    * Nazwy metod są obowiązujące.
    */
    class MobileObj{
       
       /*!
        * \brief Kąt \e yaw reprezentuje rotację zgodnie z ruchem wskazówek zegara
        *        wokół osi \e OZ.
	*
	* Kąt \e yaw reprezentuje rotację zgodnie z ruchem wskazówek zegara
        * wokół osi \e OZ. Wartość kąta wyrażona jest w stopniach.
        */
       double _Ang_Yaw_deg = 0;

       /*!
        * \brief Kąt \e pitch reprezentuje rotację zgodnie z ruchem wskazówek zegara
        *        wokół osi \e OY.
	*
	* Kąt \e pitch reprezentuje rotację zgodnie z ruchem wskazówek zegara
        * wokół osi \e OY. Wartość kąta wyrażona jest w stopniach.
        */
       double _Ang_Pitch_deg = 0;

       /*!
        * \brief Kąt \e roll reprezentuje rotację zgodnie z ruchem wskazówek zegara
        *        wokół osi \e OX.
	*
	* Kąt \e roll reprezentuje rotację zgodnie z ruchem wskazówek zegara
        * wokół osi \e OX. Wartość kąta wyrażona jest w stopniach.
        */
       double _Ang_Roll_deg = 0;

       /*!
        * \brief Współrzędne aktualnej pozycji obiektu.
	*
	* Współrzędne aktualnej pozycji obiektu. Przyjmuje się,
	* że współrzędne wyrażone są w metrach.
        */
       Vector3D  _Position_m;

        /*!
        * \brief Współrzędne aktualnej pozycji obiektu.
	*
	* Współrzędne aktualnej pozycji obiektu. Przyjmuje się,
	* że współrzędne wyrażone są w metrach.
        */
        Vector3D _Shift;

       /*!
        * \brief Nazwa obiektu, która go indentyfikuje.
        *
        * Nazwa obiektu, która go indentyfikuje. Z tego względu musi
        * musi to być nazwa unikalna wśród wszystkich obiektów na scenie.
        */
       std::string  _Name;

       /*!
        * \brief Kolor obiektu.
	*
	* Kolor obiektu w formacie RGB. Wartość dla każego koloru
        * reprezentuje liczba całkowita o wartości z przedziału [0, 255].
        */
        int RGB_Colour[3];

        /*!
        * \brief Wielkość obiektu określana w trzech wymiarach X, Y, Z
        *
        */
        Vector3D _Scale;


     public:
      
      /*!
       * \brief Udostępia wartość kąta \e roll.
       *
       * Udostępia wartość kąta \e roll. Jest ona wyrażona w stopniach.
       */
       double GetAng_Roll_deg() const { return _Ang_Roll_deg; }
      
      /*!
       * \brief Udostępia wartość kąta \e pitch.
       *
       * Udostępia wartość kąta \e pitch. Jest ona wyrażona w stopniach.
       */
       double GetAng_Pitch_deg() const { return _Ang_Pitch_deg; }
      
       /*!
       * \brief Udostępia wartość kąta \e yaw.
       *
       * Udostępia wartość kąta \e yaw. Jest ona wyrażona w stopniach.
       */
       double GetAng_Yaw_deg() const { return _Ang_Yaw_deg; }

      /*!
       * \brief Zmienia wartość kąta \e roll.
       *
       * Zmienia wartość kąta \e roll.
       * \param[in] Ang_Roll_deg - nowa wartość kąta \e roll wyrażona w stopniach.
       */
       void SetAng_Roll_deg(double Ang_Roll_deg) { _Ang_Roll_deg = Ang_Roll_deg; }
      
      /*!
       * \brief Zmienia wartość kąta \e pitch.
       *
       * Zmienia wartość kąta \e pitch.
       * \param[in] Ang_Pitch_deg - nowa wartość kąta \e pitch wyrażona w stopniach.
       */
       void SetAng_Pitch_deg(double Ang_Pitch_deg) { _Ang_Pitch_deg = Ang_Pitch_deg; }
      
      /*!
       * \brief Zmienia wartość kąta \e yaw.
       *
       * Zmienia wartość kąta \e yaw.
       * \param[in] Ang_Yaw_deg - nowa wartość kąta \e yaw wyrażona w stopniach.
       */
       void SetAng_Yaw_deg(double Ang_Yaw_deg) { _Ang_Yaw_deg = Ang_Yaw_deg; }

      /*!
       * \brief Udostępnia współrzędne położenia obiektu w trybie tylko do odczytu.
       *
       * Udostępnia współrzędne punktu, który definiuje położenia obiektu
       * w trybie tylko do odczytu.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       */
       const Vector3D & GetPosition_m() const { return _Position_m; }
      
      /*!
       * \brief Udostępnia współrzędne położenia obiektu w trybie modyfikacji.
       *
       * Udostępnia współrzędne punktu, który definiuje położenia obiektu
       * w trybie modyfikacji.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       */
       Vector3D & UsePosition_m() { return _Position_m; }
      
      /*!
       * \brief Zmienia współrzędne położenia obiektu.
       *
       * Zmienia współrzędne punktu, który definiuje położenia obiektu.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       * \param[in] rPos_m - współrzędne nowgo położenia. Przyjmuje się,
       *                     że są one wyrażone w metrach.
       */
       void SetPosition_m(const Vector3D &rPos_m) { _Position_m = rPos_m; }

      /*!
       * \brief Zmienia współrzędne położenia obiektu.
       *
       * Zmienia współrzędne punktu, który definiuje położenia obiektu.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       * \param[in] rPos_m - współrzędne nowgo położenia. Przyjmuje się,
       *                     że są one wyrażone w metrach.
       */
        void SetShift(Vector3D &Shift) { _Shift = Shift; }

      /*!
       * \brief Zmienia nazwę obiektu.
       *
       *  Zmienia nazwę obiektu.
       *  \param[in] sName - nowa nazwa obiektu.
       */
       void SetName(const char* sName) { _Name = sName; }
       
       /*!
        * \brief Udostępnia nazwę obiektu.
	*
	* Udostępnia nazwę obiektu w trybie tylko do odczytu.
        */
       const std::string & GetName() const { return _Name; }

       /*!
        * \brief Zmienia kolor obiektu.
        *
        * Zmienia wartość koloru obiektu na wartość wczytaną ze zmiennej tekstowej
        * typu string. Wartości spoza dopuszczalnego zakresu [0, 255] sprowadzane są
        * odpowiednio do wartości maksymalnej lub minimalnej.
        * \pre Zmienna tekstowa zawiera zapis 3 wartości stałyvh, oddzielonych spacjami.
        *
        * \param[in] Colour - zmienna string zawierająca wartości kolorów.
        */ 
       void SetColour(const std::string &Colour){
                std::istringstream IStrm(Colour);
                int RCol, GCol, BCol;
                IStrm >> RCol >> GCol >> BCol;

                if(RCol <= 0){
                      RGB_Colour[0] = 0;  
                }else if(RCol >= 255){
                        RGB_Colour[0] = 255;
                }else{
                   RGB_Colour[0] = RCol;     
                } 

                if(GCol <= 0){
                      RGB_Colour[1] = 0;  
                }else if(GCol >= 255){
                        RGB_Colour[1] = 255;
                }else{
                   RGB_Colour[1] = GCol;     
                } 

                if(BCol <= 0){
                      RGB_Colour[2] = 0;  
                }else if(BCol >= 255){
                        RGB_Colour[2] = 255;
                }else{
                   RGB_Colour[2] = BCol;     
                } 
       }

        /*!
         * \brief Ustawia wielkość obiektu
         * 
         * \param[in] Scale - wielkość obiektu
         */
       void SetScale(Vector3D &Scale) {_Scale = Scale;}

        /*!
         * \brief Zwraca informację o stanie obiektu
         * 
         * \return obiekt std::string zawierający ciag informacji o obiekcie.
         */
       std::string GetStateDesc(){
               char c_buf[300];
               int len = sprintf(c_buf, "Name=%s Scale=(%f, %f, %f) RotXYZ_deg=(%f,%f,%f) Trans_m=(%f, %f, %f) RGB=(%d, %d, %d) Shift=(%f, %f, %f)\n",
                                  _Name.c_str(),
                                  _Scale[0], _Scale[1], _Scale[2],
                                  _Ang_Roll_deg, _Ang_Pitch_deg, _Ang_Yaw_deg,
                                  _Position_m[0], _Position_m[1], _Position_m[2],
                                  RGB_Colour[0], RGB_Colour[1], RGB_Colour[2],
                                  _Shift[0], _Shift[1], _Shift[2]);

               std::string result(c_buf, len);
               return result;
       }
    };


#endif

