#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH
#include <iostream>
#include "BrylaGeometryczna.hh"

#define PLIK_WZORCOWEGO_SZESCIANU "bryly_wzorcowe/szescian.dat"

#define SKALA_KORPUSU_X 10
#define SKALA_KORPUSU_Y 8.0
#define SKALA_KORPUSU_Z 4.0

/**
 * @brief Tworzy pojęcie prostopadłościanu
 * 
 */
class Prostopadloscian
: public BrylaGeometryczna
{
    private:

    /**
     * @brief Kąt orientacji obiektu
     * 
     */
    double Kat_Orientacji;
    public:

    /**
     * @brief Tworzy obiekt prostopadłościan przez dziedziczenie z bryły geometrycznej, w zależności od podanych argumentów
     * 
     * @param sciezkaDoProstopadloscianuWzorcowego 
     * @param sciezkaDoProstopadloscianuFinalnego 
     */
    Prostopadloscian(const std::string& sciezkaDoProstopadloscianuWzorcowego, const std::string& sciezkaDoProstopadloscianuFinalnego):
    BrylaGeometryczna(sciezkaDoProstopadloscianuWzorcowego, sciezkaDoProstopadloscianuFinalnego) {}

    /**
     * @brief Tworzy domyślny obiekt prostopadłościan przez dziedziczenie z bryły geometrycznej
     * 
     * @param sciezkaDoGraniastoslupaWzorcowego 
     * @param sciezkaDoGraniastoslupaFinalnego 
     */
    Prostopadloscian():BrylaGeometryczna(PLIK_WZORCOWEGO_SZESCIANU, PLIK_ROBOCZY__DRON1_KORPUS){std::cout << "+";}
    /**
     * @brief Transformuje wierzchołek z układu lokalnego do globalnego
     * 
     * @param wierz 
     * @return Wektor3D 
     */
    Wektor3D TransfDoUkladuRodzica(const Wektor3D& wierz) const;

    /**
     * @brief Umożliwia zmianę kąta przez zwrócenie referencji
     * 
     * @return double kąt
     */
    double& WezKat(){return Kat_Orientacji;}

    /**
     * @brief Umożliwia odczytanie kąta
     * 
     * @return double kąt
     */
    double WezKat() const {return Kat_Orientacji;}
};

/**
 * @brief Zwraca domyślną skalę dla prostopadłościanu
 * 
 * @return Wektor3D 
 */
Wektor3D DomyslnaSkalaKorpusu();

#endif