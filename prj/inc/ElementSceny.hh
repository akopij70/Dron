#ifndef ELEMENT_HH
#define ELEMENT_HH


#include <iostream>
#include "Wektor.hh"
#include "Prostopadloscian.hh"
#include "Graniastoslup.hh"

/**
 * @brief Tworzy pojęcie elementu sceny
 * 
 */
class ElementSceny
{
    private:
    /**
     * @brief Położenie elementu
     * 
     */
    Wektor3D Pol;

    /**
     * @brief Obrys elementu
     * 
     */
    Wektor3D Obrysy[2];
    public:
    /**
     * @brief Wirtualna metoda zwracająca nazwę typu elementu
     * 
     * @return const char* nazwa typy
     */
    virtual const char *NazwaTypu () const {return "Obiekt sceny";}
    
    /**
     * @brief Zwraca nazwę wzorcowego pliku
     * 
     * @return const char* 
     */
    virtual const char *PlikWzor() const {return "wzor";}

    /**
     * @brief Zwraca nazwę finalnego pliku
     * 
     * @return const char* 
     */
    virtual const char *PlikFinal() const {return "final";}

    /**
     * @brief Pobiera położenie elementu
     * 
     * @return Wektor3D położenie
     */
    virtual Wektor3D PobierzPolozenie() const {return Pol;}

    /**
     * @brief Sprawdza czy obrysy elementu nakładają się z obrysem drona
     * 
     * @param pol położenie drona
     * @param promien promień drona
     * @return true gdy się nakładają
     * @return false gdy się nie nakładają
     */
    virtual bool CzyObrysyNakladajaSie(Wektor3D pol, double promien) const {std::cout << pol << std::endl << promien << std::endl; return true;}
    
    /**
     * @brief Pobiera minimalny obrys
     * 
     * @return Wektor3D minimalny punkt
     */
    virtual Wektor3D WezObrysMin() const {return Obrysy[0];}

    /**
     * @brief Pobiera maksymalny obrys
     * 
     * @return Wektor3D maksymalny punkt
     */
    virtual Wektor3D WezObrysMax() const {return Obrysy[1];}
};

#endif