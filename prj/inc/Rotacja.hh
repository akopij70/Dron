#ifndef ROTACJA_HH
#define ROTACJA_HH
#include "Macierz3x3.hh"
#include "Wektor.hh"
#include <vector>
#include <iostream>

/**
 * @brief Modeluje pojęcie rotacji
 * 
 */
class Rotacja
{
    private:

    /**
     * @brief Informacja o osi wokół której należy wykonać obrót
     * 
     */
    char os;

    /**
     * @brief Informacja o kącie o jaki należy wykonać obrót
     * 
     */
    double kat;

    public:

    /**
     * @brief Funkcja zwracająca nazwę osi
     * 
     * @return char oś
     */
    char wez_os() const {return os;}

    /**
     * @brief Funkcja umożliwiająca modyfikację osi
     * 
     * @return char& referencja do pola z osią
     */
    char& modyfikuj_os() {return os;}

    /**
     * @brief Funkcja zwracająca kąt obrotu
     * 
     * @return double kąt obrotu
     */
    double wez_kat() const {return kat;}

    /**
     * @brief Funkcja umożliwiająca modyfikację kąta
     * 
     * @return double& referecnja do pola z kątem
     */
    double& modyfikuj_kat() {return kat;}

};

/**
 * @brief Funkcja modelująca macierz obrotu o kąt podany jako parametr wokół osi X
 * 
 * @param kat 
 * @return Macierz3x3 macierz obrotu
 */
Macierz3x3 ObrotX(double kat);

/**
 * @brief Funkcja modelująca macierz obrotu o kąt podany jako parametr wokół osi Y
 * 
 * @param kat 
 * @return Macierz3x3 macierz obrotu
 */
Macierz3x3 ObrotY(double kat);

/**
 * @brief Funkcja modelująca macierz obrotu o kąt podany jako parametr wokół osi Z
 * 
 * @param kat 
 * @return Macierz3x3 macierz obrotu 
 */
Macierz3x3 ObrotZ(double kat);

/**
 * @brief Funkcja tworząca finalną macierz obrotu przez odpowiednie wymnożenie macierzy
 * 
 * @param lista_obrotow kontener zawierający macierze obrotu
 * @return Macierz3x3 finalna macierz obrotu
 */
Macierz3x3 UstawObrot(std::vector<Rotacja> lista_obrotow);

/**
 * @brief Funkcja ustalająca dla jakiej osi stworzyć macierz obrotu na podstawie obiektu Rot
 * 
 * @param Rot obiekt zawierający informację o osi
 * @return Macierz3x3 macierz obrotu
 */
Macierz3x3 UstawOs(Rotacja Rot);

/**
 * @brief Funkcja zbiera dane podawane przez ożytkownika dotyczące sekwencji obrotów i umieszcza je w zwracanym kontenerze
 * 
 * @return std::vector<Rotacja> kontener z informacjami o obtotach
 */
std::vector<Rotacja> Pobierz_dane();


/**
 * @brief Przeciążenie operatora << w cely wyświetlenia danych związanych z rotacją - funkcja wykorzystywana przy testach programu
 * 
 * @param Strm strumień
 * @param Rot obiekt zawierający informacje o rotacji
 * @return std::ostream& strumień
 */
std::ostream& operator << ( std::ostream &Strm, const Rotacja &Rot);
#endif