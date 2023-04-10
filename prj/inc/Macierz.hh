#ifndef MACIERZ_HH
#define MACIERZ_HH


#include <iostream>
#include <cmath>
#include "Wektor.hh"

/*!
 * \file
 * \brief Ten plik zawiera definicję szablonu Macierz<>
 *
 */

/*!
 * \brief  Szablon opisujący macierz
 *
 *  Modeluje macierz dowolnego wymiaru
 */

template <int Wymiar>
class Macierz
{
  private:
    /**
     * @brief Element macierzy
     * 
     */
    double _Tab[Wymiar][Wymiar];
  public:
    /**
     * @brief Pozwala odczytać wartości danego pola
     * 
     * @param Wiersz 
     * @param Kolumna 
     * @return double wartość danego pola
     */
    double  operator() (int Wiersz, int Kolumna) const // pozwala odczytac wartości danego pola
    {
      assert(((Wiersz >= 0) && Wiersz < (Wymiar)) && ((Kolumna >= 0) && Kolumna < (Wymiar)));
      return _Tab[Wiersz][Kolumna];
    }

    /**
     * @brief Umożliwia zapis przez zwrócenie referencji do danego pola
     * 
     * @param Wiersz 
     * @param Kolumna 
     * @return double& referencja do danego pola
     */
    double& operator() (int Wiersz, int Kolumna)    // umozliwia zapis przez zwrocenie referencji do danego pola
    {
      assert(((Wiersz >= 0) && Wiersz < (Wymiar)) && ((Kolumna >= 0) && Kolumna < (Wymiar)));
      return _Tab[Wiersz][Kolumna];
    }

    /**
     * @brief Konstruuje nowy obiekt Macierz wypełniony zerami
     * 
     */
    Macierz();

    /**
     * @brief Realizuje przeciążenie operatora * w celu wymnożenia macierzy przez wektor
     * 
     * @param W wektor do przemnożenia
     * @return Wektor<Wymiar> wektor po operacji przemnożenia
     */
    Wektor<Wymiar> operator * (const Wektor<Wymiar>& W) const;

    /**
     * @brief Tworzy macierz obrotu w zależności od stopni
     * 
     * @param stopnie 
     * @return Macierz<Wymiar> macierz obrotu
     */
    Macierz<Wymiar> Stworz_macierz_obrotu(const double stopnie);

    /**
     * @brief Tworzy macierz jednostkową
     * 
     * @return Macierz<Wymiar> macierz jednonstkowa
     */
    Macierz<Wymiar> Macierz_jednostkowa();

    /**
     * @brief Realizuje przeciążenie operatora *= w celu wymnożenia 2 macierzy
     * 
     * @param M druga macierz do wymnożenia
     * @return Macierz<Wymiar> wynik jako macierz
     */
    Macierz<Wymiar> operator*=(const Macierz<Wymiar>& M);

    /**
     * @brief Tworzy macierz ze skalą
     * 
     * @param W wektor zawierający skalę
     * @return Macierz<Wymiar> 
     */
    Macierz<Wymiar> Stworz_macierz_ze_skala(const Wektor<Wymiar> &W);
};

/**
 * @brief Tworzy nowy typ Macierz2x2, czyli macierz z 2 wierszami i 2 kolumnami
 * 
 */
typedef Macierz<2> Macierz2x2;


template <int Wymiar>
Macierz<Wymiar>::Macierz()
{
    for (int i = 0; i < Wymiar; ++i)
    {
        for (int j = 0; j < Wymiar; ++j)
        {
            _Tab[i][j] = 0.0;
        }
    }
}


template <int Wymiar>
Wektor<Wymiar> Macierz<Wymiar>::operator * (const Wektor<Wymiar>& W) const
{
  Wektor<Wymiar> wynik;
  for (int i = 0; i < Wymiar; ++i)
  {
    for (int j = 0; j < Wymiar; ++j)
    {
      wynik[i] += _Tab[i][j] * W[j];
    }
  }
  return wynik;
}

template <int Wymiar>
Macierz<Wymiar> Macierz<Wymiar>::operator*=(const Macierz<Wymiar>& M)
{
  Macierz<Wymiar> wynik;
  for (int i = 0; i < Wymiar; ++i)
  {
    for (int j = 0; j < Wymiar; ++j)
    {
      for (int k = 0; k < Wymiar; ++k)
      {
        wynik(i,j) += (_Tab[i][k] * M(k, j));
      }
    }
  }

  for (int i = 0; i < Wymiar; ++i)
  {
    for (int j = 0; j < Wymiar; ++j)
    {
      _Tab[i][j] = wynik(i,j);
    }
  }
  return (*this);
}

template <int Wymiar>
Macierz<Wymiar> Macierz<Wymiar>::Stworz_macierz_obrotu(const double stopnie)
{
    double radiany = stopnie * M_PI/180;
    
    _Tab[0][0] = cos(radiany);
    _Tab[0][1] = -sin(radiany);
    _Tab[1][0] = sin(radiany);
    _Tab[1][1] = cos(radiany);
    return (*this);
}

template <int Wymiar>
Macierz<Wymiar> Macierz<Wymiar>::Macierz_jednostkowa()
{
  int i = 0;
  for (int j = 0; j < Wymiar; ++j)
  {
    _Tab[i][j] = 1;
    i += 1;
  }
  return (*this);
}

template <int Wymiar>
Macierz<Wymiar> Macierz<Wymiar>::Stworz_macierz_ze_skala(const Wektor<Wymiar> &W)
{
  int i = 0;
  for (int j = 0; j < Wymiar; ++j)
  {
    _Tab[i][j] = W[j];
    i += 1;
  }
  return (*this);
}

/**
 * @brief Przeciążenie dla wyjścia musi także być szablonem. Realizuje przeciążenie operatora << w celu wyświetlenia macierzy
 * 
 * @tparam Wymiar 
 * @param Strm strumień
 * @param Mac macierz do wyświetlenia
 * @return std::ostream& strumień
 */
template <int Wymiar>
inline
std::ostream& operator << (std::ostream &Strm, const Macierz<Wymiar> &Mac)
{
  for (int i = 0; i < Wymiar; ++i)
  {
    for (int j = 0; j < Wymiar; ++j)
      {
        Strm << std::setw(16) << std::fixed << std::setprecision(14) << Mac(i,j) << " ";
      }
      Strm << std::endl;
  }
  return Strm;  
}

#endif