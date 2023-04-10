#ifndef DRON_HH
#define DRON_HH

#include <iostream>
#include "ElementSceny.hh"
#include "lacze_do_gnuplota.hh"
#include <unistd.h>
#include <vector>
#include <cstring>
#define ILOSC_ROTOROW 4
#define SKOK_OBROTU_ROTOROW_stopnie  5
#define WYSOKOSC_LOTU 40
#define DLUGOSC_LOTU 50
#define PLIK_TRASY_PRZELOTU "dat/trasa_przelotu.dat"
#define PLIK_Z_KORPUSEM "dat/Korpus"
#define PLIK_Z_ROTOREM1 "dat/Rotor1"
#define PLIK_Z_ROTOREM2 "dat/Rotor2"
#define PLIK_Z_ROTOREM3 "dat/Rotor3"
#define PLIK_Z_ROTOREM4 "dat/Rotor4"
#define STALA_DO_PROMIENIA 1.5

/**
 * @brief Tworzy pojęcie drona
 * 
 */
class Dron : public ElementSceny
{
    private:
    /**
     * @brief Położenie drona
     * 
     */
    Wektor3D Polozenie;

    /**
     * @brief Kąt oreintacji drona
     * 
     */
    double Kat_Orientacji;

    /**
     * @brief Korpus drona
     * 
     */
    Prostopadloscian Korpus;

    /**
     * @brief Rotory drona
     * 
     */
    Graniastoslup RotorDrona[ILOSC_ROTOROW];


    /**
     * @brief Lącze umożliwiające rysowanie w gnuplocie
     * 
     */
    PzG::LaczeDoGNUPlota Lacze_dron;
    double Promien;
    /**
     * @brief Przenosi współrzędne rotora z układu lokalnego do globalnego
     * 
     * @param Rotor 
     * @return true jeżeli się uda
     * @return false jeżeli wystąpi błąd
     */
    bool Oblicz_i_Zapisz_WspGlbRotora(const Graniastoslup& Rotor) const;

    /**
     * @brief Przenosi współrzędne korpusu z układu lokalnego do globalnego
     * 
     * @param Rotor 
     * @return true jeżeli się uda
     * @return false jeżeli wystąpi błąd
     */
    bool Oblicz_i_Zapisz_WspGlbKorpusu();
    //protected:
    //Wektor3D TransfDoUklRodzica(const Wektor3D)
    public:

    /**
     * @brief Tworzy domyślny obiekt dron
     * 
     */
    Dron();

    /**
     * @brief Tworzy drona w zależności od nazwy i początkowego połozenia
     * 
     * @param pol położenie
     * @param nazwa nazwa
     */
    Dron(Wektor3D pol, std::string nazwa);

    /**
     * @brief Umożliwia zmianę położenia drona przez zwrócenie referencji
     * 
     * @return Wektor3D& położenie
     */
    Wektor3D& WezPolozenie() {return Polozenie;}

    /**
     * @brief Umożliwia odczyt położenia drona
     * 
     * @return Wektor3D& położenie
     */
    Wektor3D WezPolozenie() const {return Polozenie;}

    /**
     * @brief Umożliwia zmianę kąta przez zwrócenie referencji
     * 
     * @return Wektor3D& położenie
     */
    double& WezKat(){return Kat_Orientacji;}

    /**
     * @brief Umożliwia odczyt kąta 
     * 
     * @return double kąt
     */
    double WezKat() const {return Kat_Orientacji;}

    /**
     * @brief Ustawia ścieżkę w zależności od kąta i długości oraz punktów
     * 
     * @param Kat_skretu kąt
     * @param Dlugosc_lotu długość trasy
     * @param punkty punkty przeze które ma przebiegać
     * @return true jeżeli się uda
     * @return false jeżli wystąpi błąf
     */
    bool Planuj_sciezke(double Kat_skretu, double Dlugosc_lotu, std::vector<Wektor3D>& punkty);

    /**
     * @brief Realizuje pionowy przelot 
     * 
     * @param Dlugosc_lotu długość lotu
     * @param Lacze Lącze do gnuplota rysujace przelot
     * @return true jeżeli się uda
     * @return false jeżeli wystąpi błąd
     */
    bool PionowyLot(double Dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze);

    /**
     * @brief Realizuje poziomy przelot 
     * 
     * @param Dlugosc_lotu długość lotu
     * @param Lacze Lącze do gnuplota rysujace przelot
     * @return true jeżeli się uda
     * @return false jeżeli wystąpi błąd
     */
    bool PoziomyLot(double Dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze);

    /**
     * @brief Realizuje poziomy przelot 
     * 
     * @param punkty punkty ścieżki aby wyliczyć długość lotu
     * @param Lacze Lącze do gnuplota rysujace przelot
     * @return true jeżeli się uda
     * @return false jeżeli wystąpi błąd
     */
    bool PoziomyLot(std::vector<Wektor3D>& punkty, PzG::LaczeDoGNUPlota& Lacze);

    /**
     * @brief Realizuje obrót drona o dany kąt
     * 
     * @param Kat kąt o jaki ma się obrócić
     * @param Lacze Lącze do gnuplota rysujace obrót
     * @return true jeżeli się uda
     * @return false jeżeli wystąpi błąd
     */
    bool ObrotLot(double Kat, PzG::LaczeDoGNUPlota& Lacze);

    /**
     * @brief Zapisuje współrzędne drona do układu globalnego
     * 
     * @return true jeżeli się uda
     * @return false jeżeli wystąpi błąd
     */
    bool Oblicz_i_Zapisz_WspGlbDrona();

    /**
     * @brief Relizuje obrót rotorami drona
     * 
     */
    void ObracajRotorami();

    /**
     * @brief Pozwala odczytać lokalne współrzędne korpusu
     * 
     * @return Prostopadloscian 
     */
    Prostopadloscian WezKorpus() const{return Korpus;}

    /**
     * @brief Pozwala odczytać lokalne współrzędne rotora
     * 
     * @param i 
     * @return Graniastoslup 
     */
    Graniastoslup WezRotor(unsigned int i) const{return RotorDrona[i];}

    /**
     * @brief Transformuje punkt drona do układu sceny
     * 
     * @param wek punkt do przetransowformowania
     * @return Wektor3D wynikowy punkt
     */
    Wektor3D TransfDoUklWspRodzica(const Wektor3D &wek) const;

    /**
     * @brief Umożliwia modyfikację promienia
     * 
     * @return double& 
     */
    double& WezPromien() {return Promien;}

    /**
     * @brief Umożliwia odczyt promienia drona
     * 
     * @return Wektor3D& położenie
     */
    double WezPromien() const {return Promien;}
    
    /**
     * @brief Metoda wirtualna
     * 
     * @return const char* zwraca typ obiektu sceny
     */
    virtual const char *NazwaTypu() const override {return "Dron";}
    
    /**
     * @brief Metoda wirtualna do odczytu położenia obiektu
     * 
     * @return Wektor3D położenie obiektu
     */
    virtual Wektor3D PobierzPolozenie() const {return (*this).WezPolozenie();}

    /**
     * @brief Sprawdza czy jest możliwe lądowanie drona
     * 
     * @param ElementySceny lista wskaźników do elementów sceny
     * @return true jeżeli pod dronem nie ma przeszkody
     * @return false jeżeli pod dronem jest przeszskoda
     */
    bool CzyMoznaLadowac(const std::list <std::shared_ptr<ElementSceny>> &ElementySceny) const;
    
    /**
     * @brief Metoda wirtualna sprawdza czy obrys drona nakłada się z obiektem
     * 
     * @param pol polozenie drona
     * @param promien promien drona
     * @return true jeżeli ubrysy nie nakładają się
     * @return false jeżeli obrysy nakładają się
     */
    virtual bool CzyObrysyNakladajaSie(Wektor3D pol, double promien) const override 
    {
        Wektor3D Polozenie_elementu = WezPolozenie();
        double pkt1 = Polozenie_elementu[0] - pol[0];
        double pkt2 = Polozenie_elementu[1] - pol[1];
        double odleglosc = sqrt(pow(pkt1, 2) + pow(pkt2, 2));
        double suma_promieni = Promien + promien;
        //std::cout << "LIZCZYMY\n";
        if(odleglosc == 0) { return false; }
        if(odleglosc >= suma_promieni) { return false; }
        std::cout << pkt2 << "\t" << pkt1 << "\n" << Promien << "\t" << promien << "\n";
        std::cout << odleglosc <<std::endl;
        return true;
    }

    /**
     * @brief Funkcja licząca promień drona
     * 
     * @param punkt punkt od którego ma być liczona długość promienia
     */
    void ObliczPromien(Wektor3D punkt);

    /**
     * @brief Funkcja tworzy dalszą trasę gdy mogłaby nastąpić kolizja
     * 
     * @param Kat_skretu 
     * @param Dlugosc_lotu 
     * @param punkty 
     * @return true 
     * @return false 
     */
    bool PlanujZmianeSciezki(double Kat_skretu, double Dlugosc_lotu, std::vector<Wektor3D>& punkty);
    
    /**
     * @brief Realizuje przelot drona po nowej ścieżce 
     * 
     * @param punkty 
     * @param Lacze 
     * @return true 
     * @return false 
     */
    bool PoziomyLotPoZmianieSciezki(std::vector<Wektor3D>& punkty, PzG::LaczeDoGNUPlota& Lacze);
};

#endif