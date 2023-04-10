#ifndef BRYLA_HH
#define BRYLA_HH

#include <iostream>
#include <string>
#include "Wektor.hh"
#include "Macierz3x3.hh"
#include "Rotacja.hh"
#include <fstream>
#include <cassert>
#include <memory>
#include <list>
#define ILOSC_WIERZ_LINII_TWORZACEJ 4
#define PLIK_ROBOCZY__DRON1_KORPUS "bryly_wzorcowe/szescian.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR1  "dat/PlikRoboczy_Dron1_Rotor1.dat"
#define PLIK_ROBOCZY_PRZESZKODA "bryly_wzorcowe/szescian_na_powierzchni.dat"

#define PLIK_WLASCIWY__DRON1_KORPUS  "dat/test.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR1  "dat/test_Rotor1.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR2  "dat/test_Rotor2.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR3  "dat/test_Rotor3.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR4  "dat/test_Rotor4.dat"

#define BRYLY_WZORCOWE "dat/Bryly_wzorcowe/"
#define BRYLY_FINALNE "dat/Bryly_finalne/"
#define PRZESZKODA "dat/Bryly_finalne/Przeszkoda"
#define MAX_YX 200

/**
 * @brief Tworzy pojęcie bryły geometrycznej
 * 
 */
class BrylaGeometryczna
{
    private:
    /**
     * @brief Plik z którego są pobierane dane
     * 
     */
    std::string Nazwa_pliku_BrylaWzorcowa;

    /**
     * @brief Plik do którego są zapisywane zmienione wierzchołki
     * 
     */
    std::string Nazwa_pliku_BrylaFinalna;

    /**
     * @brief Skala względem której są przeliczane wierzchołki
     * 
     */
    Wektor3D Skala;
    Wektor3D Polozenie;
    Wektor3D Obrys[2];

    public:
    /**
     * @brief Tworzy obiekt bryły geometrycznej w zależności od podanych argumentów
     * 
     * @param nazwa_brylywzorcowej 
     * @param nazwa_brylyfinalnej 
     */
    BrylaGeometryczna(const std::string& nazwa_brylywzorcowej, const std::string& nazwa_brylyfinalnej) 
    {Nazwa_pliku_BrylaWzorcowa = nazwa_brylywzorcowej; Nazwa_pliku_BrylaFinalna = nazwa_brylyfinalnej; Skala[0] = Skala[1] = Skala[2] = 1; }

    /**
     * @brief Tworzy domyślny "pusty" obiekt bryły geometrycznej 
     * 
     */
    BrylaGeometryczna() {Nazwa_pliku_BrylaWzorcowa = nullptr; Nazwa_pliku_BrylaFinalna = nullptr;}

    /**
     * @brief Destruktor obiektu BrylaGeometryczna
     * 
     */
    ~BrylaGeometryczna() {}

    /**
     * @brief Skaluje wierzchołek bryły
     * 
     * @param Wierz podany wierzchołek
     * @return Wektor3D 
     */
    Wektor3D Skaluj(const Wektor3D& Wierz) const;

    /**
     * @brief Umożliwia zmianę skali przez referencję
     * 
     * @return Wektor3D& skala
     */
    Wektor3D& WezSkale(){return Skala;}

    /**
     * @brief Umożliwia odczytanie skali
     * 
     * @return Wektor3D skala
     */
    Wektor3D WezSkale() const {return Skala;}

    /**
     * @brief Zwraca nazwę bryły wzorcowej
     * 
     * @return const std::string& 
     */
    const std::string& WezNazwePliku_BrylaWzorcowa() const {return Nazwa_pliku_BrylaWzorcowa;}

    /**
     * @brief Zwraca nazwę bryły finalnej
     * 
     * @return const std::string& 
     */
    const std::string& WezNazwePliku_BrylaFinalna() const {return Nazwa_pliku_BrylaFinalna;}

    /**
     * @brief Umożliwia ustawienie skali
     * 
     * @param skala 
     */
    void UstawSkale(const Wektor3D& skala) {WezSkale() = skala;}

    /**
     * @brief Umożliwia zmianę położenia przez referencję
     * 
     * @return Wektor3D położenie
     */
    Wektor3D& WezPolozenie() {return Polozenie;}

    /**
     * @brief Umożliwia odczyt położenia
     * 
     * @return Wektor3D położenie
     */
    Wektor3D WezPolozenie() const {return Polozenie;}

    
    /**
     * @brief Umożliwia modyfikację obrysu minimalnego bryły
     * 
     * @return Wektor3D& punkt minimalny
     */
    Wektor3D& WezObrys1() {return Obrys[0];}

    /**
     * @brief Umożliwia odczyt obrysu minimalnego
     * 
     * @return Wektor3D położenie obrys minimalny
     */
    Wektor3D WezObrys1() const {return Obrys[0];}

    /**
     * @brief Umożliwia modyfikację obrysu maksymalnego bryły
     * 
     * @return Wektor3D& punkt minimalny
     */
    Wektor3D& WezObrys2() {return Obrys[1];}

    /**
     * @brief Umożliwia odczyt obrysu maksymalnego bryły
     * 
     * @return Wektor3D punkt maksymalny
     */
    Wektor3D WezObrys2() const {return Obrys[1];}
};
#endif