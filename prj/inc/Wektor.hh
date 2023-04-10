#ifndef WEKTOR_HH
#define WEKTOR_HH

#include <iostream>
#include <cassert>
#include <cmath>
#include <iomanip>


/*!
 * \file
 * \brief Ten plik powinien zawierać definicję szablonu Wektor<>
 * 
 */


/*!
 * \brief Szablon opsiujący wektor
 * 
 *  Modeluje wektor dowolnego wymiaru 
 */
template <int Wymiar>
class Wektor
{
  private:
     /**
     * @brief Współrzędna wektora
     * 
     */
      double _Wsp[Wymiar];


  public:

    /**
     * @brief Zmienna statyczna do zliczania aktualnie istniejących obiektów wektor
     * 
     */
    static unsigned int aktualna_ilosc_ob;

    /**
     * @brief Zmienna statyczna do zliczania wszystkich stworzonych obiektów wektor
     * 
     */
    static unsigned int ogolna_ilosc_ob;


     /**
      * @brief Konstruuje obiekt Wektor wypełniony zerami, zwiększa licznik aktualnych i ogólnych obiektów
      * 
      */
      Wektor();

    /**
     * @brief Niszczy obiekt wektor, zmniejsza licznik aktualnych obiektów
     * 
     */
      ~Wektor();

      Wektor(const Wektor<Wymiar> &W);
      Wektor<Wymiar>& operator=(const Wektor<Wymiar> &W);

  
      /**
      * @brief Pozwala odczytać wartości danej współrzędnej 
      * 
      * @param lnd indeks współrzędnej
      * @return double wartość współrzędnej
      */
      double operator  [] (int lnd) const {assert((lnd >= 0) && lnd < (Wymiar)); return _Wsp[lnd];}
  
      /**
       * @brief Umożliwia zapis przez zwrócenie referencji do danego pola
       * 
       * @param lnd Indeks współrzędnej
       * @return double& pole 
       */
      double& operator [] (int lnd)                {assert((lnd >= 0) && lnd < (Wymiar)); return _Wsp[lnd];}

      /**
       * @brief Realizuje przeciążenie operatora +, w celu dodania 2 wektorow.
       * 
       * @param W  drugi wektor do odejmowania
       * @return Wektor<Wymiar> suma 2 wektorów
       */
      Wektor<Wymiar> operator + (const Wektor<Wymiar>& W) const;
      
      /**
       * @brief Realizuje przeciążenie operatora -, w celu odjęcia 2 wektorow.
       * 
       * @param W drugi wektor do odejmowania 
       * @return Wektor<Wymiar> różnica 2 wektorów
       */
      Wektor<Wymiar> operator - (const Wektor<Wymiar>& W) const;

      /**
       * @brief Oblicza długość odcinka utworzonego przez 2 wektory
       * 
       * @param W drugi wektor do obliczenia długości
       * @return double długość odcinka
       */
      double Oblicz_dlugosc(const Wektor<Wymiar>& W) const;

      /**
       * @brief Sprawdza czy udało się poprawnie wczytać współrzędne wektora.
       * 
       */
      void Kontrola_odczytu_wektora();

    static unsigned int &WezAktualna_ilosc() {return aktualna_ilosc_ob;}
    static unsigned int &WezOgolna_ilosc() {return ogolna_ilosc_ob;}
    operator Wektor<Wymiar - 1> () const {Wektor<Wymiar-1> Wynik; for (int i = 0; i < Wymiar-1; ++i) Wynik[i] = (*this)[i]; return Wynik;}


};
template <int Wymiar>
unsigned int Wektor<Wymiar>::aktualna_ilosc_ob = 0;

template <int Wymiar>
unsigned int Wektor<Wymiar>::ogolna_ilosc_ob = 0;

/**
 * @brief Tworzy typ Wektor2D, czyli wektor o 2 współrzędnych.
 * 
 */
typedef Wektor<2> Wektor2D;

/**
 * @brief Tworzy typ Wektor3D, czyli wektor o 3 współrzędnych.
 * 
 */
typedef Wektor<3> Wektor3D;

template <int Wymiar>
Wektor<Wymiar>::Wektor()
{
    for (int i = 0; i < Wymiar; ++i)
    {
        _Wsp[i] = 0.0;
    }
    ++aktualna_ilosc_ob;
    ++ogolna_ilosc_ob;
}





template <int Wymiar>
Wektor<Wymiar>::Wektor(const Wektor<Wymiar> &W)
{
    for (int i = 0; i < Wymiar; ++i)
    {
        _Wsp[i] = W[i];
    }
    ++aktualna_ilosc_ob;
    ++ogolna_ilosc_ob;
}

template <int Wymiar>
Wektor<Wymiar>& Wektor<Wymiar>::operator=(const Wektor<Wymiar> &W)
{
    for (int i = 0; i < Wymiar; ++i)
    {
        _Wsp[i] = W[i];
    }
    ++aktualna_ilosc_ob;
    ++ogolna_ilosc_ob;

    return *this;
}





template <int Wymiar>
Wektor<Wymiar>::~Wektor()
{
    --aktualna_ilosc_ob;
}


template <int Wymiar>
Wektor<Wymiar> Wektor<Wymiar>::operator + (const Wektor<Wymiar>& W) const
{
    Wektor<Wymiar> suma;
    for (int i = 0; i < Wymiar; ++i)
    {
        suma[i] = _Wsp[i] + W._Wsp[i];
    }
    return suma;
}

template <int Wymiar>
Wektor<Wymiar> Wektor<Wymiar>::operator - (const Wektor<Wymiar>& W) const
{
    Wektor<Wymiar> roznica;
    for (int i = 0; i < Wymiar; ++i)
    {
        roznica[i] = _Wsp[i] - W._Wsp[i];
    }
    return roznica;
}

template <int Wymiar>
double Wektor<Wymiar>::Oblicz_dlugosc(const Wektor<Wymiar>& W) const
{
    Wektor<Wymiar> nowy_wektor;
    double wynik;
    double potega[Wymiar];
    double suma_poteg = 0.0;
    nowy_wektor = (*this) - W;
    for (int i = 0; i < Wymiar; ++i)
    {
        potega[i] = pow(nowy_wektor._Wsp[i], 2.0);
    }
    for (int i = 0; i < Wymiar; ++i)
    {
        suma_poteg += potega[i];
    }
    wynik = sqrt(suma_poteg);
    return wynik;
}

template <int Wymiar>
void Wektor<Wymiar>::Kontrola_odczytu_wektora()
{
    while (std::cin.fail()) 
    {
        std::cerr << "Niepoprawny zapis, sprobuj jeszcze raz: " << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin >> (*this);
    }
}


/**
 * @brief Przeciążenie dla wejścia musi także być szablonem. Wczytuje współrzędne wektora.
 * 
 * @tparam Wymiar 
 * @param Strm strumień
 * @param Wek wektor do wczytania
 * @return std::istream& 
 */
template <int Wymiar>
inline
std::istream& operator >> (std::istream &Strm, Wektor<Wymiar> &Wek)
{
    for (int i = 0; i < Wymiar; ++i)
    {
        Strm >> Wek[i];
        if (Strm.fail()) //czy wczytywanie zakonczylo sie bledem
            return Strm;
    }    
    return Strm;
}

/**
 * @brief Przeciążenie dla wyjścia musi także być szablonem. Wyświetla współrzędne wektora.
 * 
 * @tparam Wymiar 
 * @param Strm strumień
 * @param Wek wektor do wyświetlenia
 * @return std::ostream& strumień
 */
template <int Wymiar>
inline
std::ostream& operator << (std::ostream &Strm, const Wektor<Wymiar> &Wek)
{
    for (int i = 0; i < Wymiar; ++i)
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Wek[i] << " ";
        return Strm;
}

#endif
