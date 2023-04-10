#ifndef PLASKOWYZ_HH
#define PLASKOWYZ_HH

#include "BrylaGeometryczna.hh"
#include "ElementSceny.hh"

#define SKALA_PLASKOWYZ_X 50
#define SKALA_PLASKOWYZ_Y 60
#define SKALA_PLASKOWYZ_Z 15
#define DOMYSLNY_PLASKOWYZ "dat/Bryly_finalne/Plaskowyz.dat"



/**
 * @brief Towrzy pojęcie Płaskowyżu
 * 
 */
class Plaskowyz : public BrylaGeometryczna, public ElementSceny
{
    private:
    public:

    /**
     * @brief Tworzy nowy obiekt Plaskowyz
     * 
     */
    Plaskowyz();

    /**
     * @brief Tworzy nowy obiekt Plaskowyz
     * 
     * @param sciezkaWzorzec scieżka do pliku wzorcowego
     * @param sciezkaFinalna scieżka do pliku finalnego
     * @param skala skala w jakiej ma być stworzona przeszkoda
     * @param pol położenie przeszkody
     */
    Plaskowyz(const std::string& sciezkaDoProstopadloscianuWzorcowego, const std::string& sciezkaDoProstopadloscianuFinalnego, const Wektor3D &skala, const Wektor3D &pol);

    /**
     * @brief Transformuje wierzchołek z układu lokalnego do globalnego
     * 
     * @param wierz 
     * @return Wektor3D 
     */
    Wektor3D TransfDoUkladuRodzica(const Wektor3D& wierz) const;
    
    /**
     * @brief Oblicza i zapisuje wspolrzedne płaskowyżu do pliku
     * 
     * @return true jeżeli się uda 
     * @return false jeżeli się nie uda
     */
    bool Oblicz_i_Zapisz_WspPl();

    /**
     * @brief Zwraca domyślną skalę przeszkody
     * 
     * @return Wektor3D skala
     */
    Wektor3D DomyslnaSkalaPlaskowyzu(){Wektor3D wek; wek[0] = SKALA_PLASKOWYZ_X; wek[1] = SKALA_PLASKOWYZ_Y; wek[2] = SKALA_PLASKOWYZ_Z; return wek;}

    /**
     * @brief Zwraca nazwę typu elementu sceny
     * 
     * @return const char* 
     */
    virtual const char *NazwaTypu () const override {return "Plaskowyz";}

    /**
     * @brief Zwraca ścieżkę do wzorcowego pliku
     * 
     * @return const char* 
     */
    virtual const char *PlikWzor() const override {return (*this).WezNazwePliku_BrylaWzorcowa().c_str();}

    /**
     * @brief Zwraca ścieżkę do finalnego pliku
     * 
     * @return const char* 
     */
    virtual const char *PlikFinal() const override {return (*this).WezNazwePliku_BrylaFinalna().c_str();}

    /**
     * @brief Zwraca położenie elementu
     * 
     * @return Wektor3D 
     */
    virtual Wektor3D PobierzPolozenie() const override{return (*this).WezPolozenie();}

    /**
     * @brief Sprawdza czy obys elementu pokrywa się z obrysem drona
     * 
     * @param pol 
     * @param promien 
     * @return true 
     * @return false 
     */
    virtual bool CzyObrysyNakladajaSie(Wektor3D pol, double promien) const override 
    {
        Wektor3D pol_przeszkody = WezPolozenie();
        Wektor3D pkt_min = WezObrys1();
        Wektor3D pkt_max = WezObrys2();
        Wektor2D pol_Dr = pol;
        Wektor2D pol_Prz = pol_przeszkody;
        Wektor2D pol_Prz_Max = pkt_max;
        Wektor2D pol_Prz_Min = pkt_min;
        Wektor2D pkt_B = pkt_max;   pkt_B[1] = pkt_min[1];              //prawy dolny punkt
        Wektor2D pkt_D = pkt_min;   pkt_D[1] = pkt_max[1];              //lewy górny punkt

        if (pol[0] > pkt_max[0] && pol[1] > pkt_max[1]) {/*std::cout << "rog1\n";*/ return (pol_Dr.Oblicz_dlugosc(pol_Prz_Max)<= promien);}
        if (pol[0] > pkt_max[0] && pol[1] < pkt_min[1]) {/*std::cout << "rog2\n";*/ return (pol_Dr.Oblicz_dlugosc(pkt_B)<= promien);}
        if (pol[0] < pkt_min[0] && pol[1] < pkt_min[1]) {/*std::cout << "rog3\n";*/return (pol_Dr.Oblicz_dlugosc(pol_Prz_Min)<= promien);}
        if (pol[0] < pkt_min[0] && pol[1] > pkt_max[1]) {/*std::cout << "rog4\n";*/return (pol_Dr.Oblicz_dlugosc(pkt_D)<= promien);}
        if ((pol[0] > pkt_min[0] && pol[0] < pkt_max[0]) && (pol[1] > pkt_max[1])) {/*std::cout << "nad\n";*/ return((pol[1] - pkt_max[1]) <= promien);}// czy okrag jest "nad" prostokatem
        if ((pol[0] > pkt_min[0] && pol[0] < pkt_max[0]) && (pol[1] < pkt_max[1])) {/*std::cout << "pod\n";*/ return ((pkt_min[1] - pol[1]) <= promien);}// czy okrag jest "pod" prostokatem
        if ((pol[1] > pkt_min[1] && pol[1] < pkt_max[1]) && (pol[0] > pkt_max[0])) {/*std::cout << "prawa\n";*/ return ((pol[0] - pkt_max[0]) <= promien);}// czy okrag jest "z prawej" prostokata
        if ((pol[1] > pkt_min[1] && pol[1] < pkt_max[1]) && (pol[0] < pkt_max[0])) {/*std::cout << "lewa\n";*/ return ((pkt_min[0] - pol[0]) <= promien);}// czy okrag jest "z lewej" prostokata
        std::cout << "Dron idealnie nad przeszkoda\n";
        
        return true;
    }

    /**
     * @brief Zwraca minimalny obrys elementu
     * 
     * @return Wektor3D 
     */
    virtual Wektor3D WezObrysMin() const override { return (*this).WezObrys1();}

    /**
     * @brief Zwraca maksymalny obrys elementu
     * 
     * @return Wektor3D 
     */
    virtual Wektor3D WezObrysMax() const override { return (*this).WezObrys2();}
};

#endif