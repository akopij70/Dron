#ifndef GRANIASTOSLUP6_HH
#define GRANIASTOSLUP6_HH
#include <iostream>
#include "BrylaGeometryczna.hh"

#define PLIK_WZORCOWEGO_GRANIASTOSLUPA6 "bryly_wzorcowe/graniastoslup6.dat"
#define SKALA_ROTORA_X 8
#define SKALA_ROTORA_Y 8
#define SKALA_ROTORA_Z 2

/**
 * @brief Tworzy pojęcie graniastosłupa
 * 
 */
class Graniastoslup: public BrylaGeometryczna
{
    private:

    /**
     * @brief Lokalny kąt orientacji 
     * 
     */
    double Kat_Orientacji;
    public:

    /**
     * @brief Tworzy obiekt graniastosłup przez dziedziczenie z bryły geometrycznej, w zależności od podanych argumentów
     * 
     * @param sciezkaDoGraniastoslupaWzorcowego 
     * @param sciezkaDoGraniastoslupaFinalnego 
     */
    Graniastoslup(const std::string& sciezkaDoGraniastoslupaWzorcowego, const std::string& sciezkaDoGraniastoslupaFinalnego):
    BrylaGeometryczna(sciezkaDoGraniastoslupaWzorcowego, sciezkaDoGraniastoslupaFinalnego) {}

    /**
     * @brief Tworzy domyślny obiekt graniastosłup przez dziedziczenie z bryły geometrycznej
     * 
     * @param sciezkaDoGraniastoslupaWzorcowego 
     * @param sciezkaDoGraniastoslupaFinalnego 
     */
    Graniastoslup():BrylaGeometryczna(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, PLIK_ROBOCZY__DRON1_ROTOR1){}

    /**
     * @brief Umożliwia zmianę kąta przez referencję
     * 
     * @return double& kąt
     */
    double& WezKat(){return Kat_Orientacji;}

    /**
     * @brief Umożliwia odczytanie kąta
     * 
     * @return double kąt
     */
    double WezKat() const {return Kat_Orientacji;}

    /**
     * @brief Transformuje wierzchołek z układu lokalnego do globalnego
     * 
     * @param wierz 
     * @return Wektor3D 
     */
    Wektor3D TransfDoUkladuRodzica(const Wektor3D& wierz) const;

};

/**
 * @brief Zwraca domyślną skalę dla graniastosłupa
 * 
 * @return Wektor3D 
 */
Wektor3D DomyslnaSkalaRotora();
#endif