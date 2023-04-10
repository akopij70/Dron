#include "Dron.hh"
#include "Plaskowyz.hh"
#include "Gora_z_grania.hh"
#include "Gora_z_ostrym_szczytem.hh"


#define ILOSC_DRONOW 2

/**
 * @brief Tworzy pojęcie sceny(planety)
 * 
 */
class Scena
{
    private:

    enum przeszkody {plaskowyz, gora_z_grania, gora_z_ostrym_szczytem};
    /**
     * @brief Drony znajdujące się na scenie
     * 
     */
    //Dron TabDronow[ILOSC_DRONOW];

    /**
     * @brief Łącze do rysowania w gnuplocie
     * 
     */
    PzG::LaczeDoGNUPlota Lacze_scena;

    /**
     * @brief Lista z przeskodami
     * 
     */
    std::list <std::shared_ptr <BrylaGeometryczna>> ListaObiektow;

    /**
     * @brief Iterator do poruszania się po liście przeszkód
     * 
     */
    std::list <std::shared_ptr <BrylaGeometryczna>> :: iterator Oit = ListaObiektow.begin(); //iterator

    std::list <std::shared_ptr <Dron>> ListaDronow;
    std::list < std::shared_ptr <Dron> > :: iterator Drit = ListaDronow.begin();

    std::list <std::shared_ptr <ElementSceny>> ListaElementow;
    std::list < std::shared_ptr <ElementSceny> > :: iterator Elit = ListaElementow.begin();

    public:

    Scena();

    /**
     * @brief Funkcja umożliwiwająca wzięcie danego drona
     * 
     * @param i indeks z tablice dronów
     * @return Dron& 
     */
    //Dron& WezDrona(unsigned int i) {return TabDronow[i];}

    /**
     * @brief Funkcja umozliwiająca obsługę drona
     * 
     * @param dron obiekt którego chce się użyć
     */
    //void UzyjDrona(Dron &dron);

    /**
     * @brief Funkcja używana w funkcji DodajPreszkodę, tworzy przeszkodę i zwraca wskaźnik do niej
     * 
     * @param idx numer typu przeszkody
     * @param wzorzec plik wzorcowy
     * @param final plik finalny
     * @param skala skala przeszkody
     * @param polozenie położenie przeszkody
     * @return std::shared_ptr <BrylaGeometryczna> 
     */
    //std::shared_ptr <BrylaGeometryczna> StworzPrzeszkode(int idx, const std::string &wzorzec, const std::string &final, const Wektor3D &skala, const Wektor3D &polozenie);

    /**
     * @brief Dodaje przeszkodę na listę i rysuje ją
     * 
     * @param idx numer typu przeszkody
     * @param wzorzec plik wzorcowy
     * @param final plik finalny
     * @param skala skala przeszkody
     * @param polozenie położenie przeszkody
     */
    void DodajPrzeszkode(int idx, const std::string &wzorzec, const std::string &final, const Wektor3D &skala, const Wektor3D &polozenie);

    /**
     * @brief Wyświetla istniejące przeszkody 
     * 
     */
    void WyswietPrzeszkody();

    /**
     * @brief Usuwa przeszkodę
     * 
     * @param idx numer na liście
     */
    void UsunPrzeszkode(int idx);

    void DodajDrona(Wektor3D pol, std::string nazwa);
    void WezDrona1();
    void Kontrola_odczytu_liczby_dronow(int &dana);
    void DodajPlaskowyz(const std::string &wzorzec, const std::string &final, const Wektor3D &skala, const Wektor3D &polozenie);
    void UzyjDrona1();
    std::shared_ptr <ElementSceny> StworzPrzeszkode(int idx, const std::string &wzorzec, const std::string &final, const Wektor3D &skala, const Wektor3D &polozenie);
    void UsunDrona();
};

/**
 * @brief Funkcja zbierająca informacje o przelocie
 * 
 */
void Pobierz_dane_przelotu();

/**
 * @brief Sprawdza czy podano poprawnie liczbę
 * 
 * @param dana 
 */
void Kontrola_odczytu_liczby(double dana);