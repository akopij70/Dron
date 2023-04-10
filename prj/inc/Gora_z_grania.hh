#ifndef GORAGRANIA_HH
#define GORAGRANIA_HH

#include "BrylaGeometryczna.hh"
#include "ElementSceny.hh"

#define SKALA_GORA_GRANIA_X 20
#define SKALA_GORA_GRANIA_Y 80
#define SKALA_GORA_GRANIA_Z 60
#define DOMYSLNY_GRANIA "dat/Bryly_finalne/Grania.dat"


/**
 * @brief Towrzy pojęcie Góry z granią
 * 
 */
class GoraGrania : public BrylaGeometryczna, public ElementSceny
{
    private:
    std::string Nazwa_pliku_BrylaWzorcowa;
    std::string Nazwa_pliku_BrylaFinalna;
    public:
    /**
     * @brief Tworzy obiekt GoraGrania
     * 
     */
    GoraGrania();

    /**
     * @brief Tworzy obiekt GoraGrania
     * 
     * @param sciezkaWzorzec scieżka do pliku wzorcowego
     * @param sciezkaFinalna scieżka do pliku finalnego
     * @param skala skala w jakiej ma być stworzona przeszkoda
     * @param pol położenie przeszkody
     */
    GoraGrania(const std::string& sciezkaWzorzec, const std::string& sciezkaFinalna, Wektor3D skala, Wektor3D pol);

    /**
     * @brief Transformuje wierzchołek z układu lokalnego do globalnego
     * 
     * @param wierz 
     * @return Wektor3D 
     */
    Wektor3D TransfDoUkladuRodzica(const Wektor3D& wierz) const;

    /**
     * @brief Oblicza i zapisuje współrzędne góry do pliku
     * 
     * @return true jeżeli się uda 
     * @return false jeżeli się nie uda
     */
    bool Oblicz_i_Zapisz_WspGGr();

    /**
     * @brief Zwraca domyślną skalę przeszkody
     * 
     * @return Wektor3D skala
     */
    Wektor3D DomyslnaSkalaGranii(){Wektor3D wek; wek[0] = SKALA_GORA_GRANIA_X; wek[1] = SKALA_GORA_GRANIA_Y; wek[2] = SKALA_GORA_GRANIA_Z; return wek;}

    /**
     * @brief Zwraca nazwę typu elementu sceny
     * 
     * @return const char* 
     */
    virtual const char *NazwaTypu () const override {return "Gora z grania";}

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
    virtual Wektor3D PobierzPolozenie() const override {return (*this).WezPolozenie();}

    /**
     * @brief Zwraca minimalny obrys 
     * 
     * @return Wektor3D minalny punkt
     */
    virtual Wektor3D WezObrysMin() const override {return (*this).WezObrys1();}

    /**
     * @brief Zwraca maksymalny obrys elementu
     * 
     * @return Wektor3D 
     */
    virtual Wektor3D WezObrysMax() const override {return (*this).WezObrys2();}

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
};

#endif