#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include "lacze_do_gnuplota.hh"
#include "Wektor.hh"
#include "Macierz.hh"
#include "Macierz3x3.hh"
#include "Rotacja.hh"
#include "Graniastoslup.hh"
#include "BrylaGeometryczna.hh"
#include "Prostopadloscian.hh"
#include "Dron.hh"
#include "Scena.hh"

void Menu();
void MenuPrzeszkod();
//void Kontrola_odczytu_liczby_dronow(int &dana);
void Kontrola_odczytu_indeksu_przeszkody(int &dana);
void Kontrola_przy_usuwaniu(int &dana, int &limit);
void IloscWektorow();

using namespace std;

int main()
{
  Scena Tytan;
  int numer_drona = -1;
  int numer_przeszkody;
  int idx_przeszkody, limit_przeszkod;
  idx_przeszkody = limit_przeszkod = 5;
  char wybor = 'x';
  Wektor3D skala, polozenie;
  string plik_przeszkoda;
  Menu();
  while (wybor != 'k')
  {
    cout << "\nTwoj wybor? (m-menu)" << endl;
    cin >> wybor;
    switch (wybor)
    {
    case 'a':
        Tytan.WezDrona1();
        numer_drona = 1;
      break;
    case 'p':
        if (numer_drona == -1)
        {
          cout << "Najpierw wybierz aktywnego drona";
          break;
        }
        
        Tytan.UzyjDrona1();
        IloscWektorow();
      break;
    case 'm':
      Menu();
      break;
    case 'k':
      cout << "Do widzenia\n";
      break;
    case 'd':
        MenuPrzeszkod();
        cin >> numer_przeszkody;
        Kontrola_odczytu_indeksu_przeszkody(numer_przeszkody);
        cout << "Podaj skale kolejno wzdluz osi OX, OY, OZ:" << endl;
        cin >> skala;
        skala.Kontrola_odczytu_wektora();
        cout << "Podaj polozenie przeszkody (x, y, z)" << endl;
        cin >> polozenie;
        polozenie.Kontrola_odczytu_wektora();
        ++idx_przeszkody;
        ++limit_przeszkod;
        plik_przeszkoda = PRZESZKODA + to_string(idx_przeszkody) + ".dat";
        Tytan.DodajPrzeszkode(numer_przeszkody, PLIK_ROBOCZY_PRZESZKODA, plik_przeszkoda.c_str(), skala, polozenie);
        IloscWektorow();
      break;
    case 'u':
        Tytan.WyswietPrzeszkody();
        cout << "Co usunac? Podaj numer:" << endl;
        cin >> numer_przeszkody;
        Kontrola_przy_usuwaniu(numer_przeszkody, limit_przeszkod);
        Tytan.UsunPrzeszkode(numer_przeszkody);
        --limit_przeszkod;
        IloscWektorow();
        break;
    default:
      cout << "Nie rozpoznano polecenia\n";
      break;
    }
  }
}

void Menu()
{
  cout << "a - wybierz aktywnego drona" << endl 
       << "p - zadaj parametry przelotu" << endl
       << "m - wyswietl menu" << endl
       << "k - koniec dzialania programu" << endl
       << "d - dodaj element powierzchni" << endl
       << "u - usun element powierzchni" << endl;
}

void MenuPrzeszkod()
{
  cout << "Wybierz przeszkode: " << endl 
       << "0 - Plaskowyz" << endl
       << "1 - Gora z grania" << endl
       << "2 - Gora z ostrym sztytem" << endl;
}

/*void Kontrola_odczytu_liczby_dronow(int &dana)
{
  while (cin.fail() || dana > ILOSC_DRONOW) 
  {
    cerr << "Niepoprawny zapis, sprobuj jeszcze raz: " << endl;
    cin.clear();
    cin.ignore(10000, '\n');
    cin >> dana;
  }
}*/

void Kontrola_odczytu_indeksu_przeszkody(int &dana)
{
  while (cin.fail() || dana > 2 || dana < 0) 
  {
    cerr << "Niepoprawny zapis, sprobuj jeszcze raz: " << endl;
    cin.clear();
    cin.ignore(10000, '\n');
    cin >> dana;
  }
}

void Kontrola_przy_usuwaniu(int &dana, int &limit)
{
  std::cout << "Ilosc przeszkod przed usunieciem: " << limit << std::endl;
  while (cin.fail() || dana > limit || dana < 1) 
  {
    cerr << "Niepoprawny zapis, sprobuj jeszcze raz: " << endl;
    cin.clear();
    cin.ignore(10000, '\n');
    cin >> dana;
  }
}
void IloscWektorow()
{
  cout << "Aktualna ilosc obiektow Wektor3D: " << Wektor3D::WezAktualna_ilosc() << endl;
  cout << "Ogolna ilosc obiektow Wektor3D: " << Wektor3D::WezOgolna_ilosc() << endl;
}