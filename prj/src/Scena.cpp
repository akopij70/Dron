#include "Scena.hh"

Scena::Scena()
{
    Wektor3D poczatkowe_pol;
    poczatkowe_pol[0] = poczatkowe_pol[1] = 20;

    for (int i = 0; i < ILOSC_DRONOW; ++i, poczatkowe_pol[0] += 25)
    {
        std::string nazwa = "Dron" + std::to_string(i+1);
        DodajDrona(poczatkowe_pol, nazwa);
    }
    Lacze_scena.DodajNazwePliku("bryly_wzorcowe/plaszczyzna.dat");

    Wektor3D skala1, pol1, pol2, pol3;
    skala1[0] += 10;  skala1[1] += 10;  skala1[2] += 15;
    pol1[0] = 30;    pol1[1] = 40;
    pol2[0] = pol1[0] + 40; pol2[1] = pol1[1];
    pol3[0] = pol1[0]; pol3[1] = pol1[1] + 50;

    ListaElementow.push_back(StworzPrzeszkode(plaskowyz, PLIK_ROBOCZY_PRZESZKODA, DOMYSLNY_PLASKOWYZ, skala1, pol1));
    ++Elit;
    std::cout << (*Elit)->PlikFinal() << std::endl;
    Lacze_scena.DodajNazwePliku((*Elit)->PlikFinal());

    ListaElementow.push_back(StworzPrzeszkode(gora_z_grania, PLIK_ROBOCZY_PRZESZKODA, DOMYSLNY_GRANIA, skala1, pol2));
    ++Elit;
    std::cout << (*Elit)->PlikFinal() << std::endl;
    Lacze_scena.DodajNazwePliku((*Elit)->PlikFinal());
    
    ListaElementow.push_back(StworzPrzeszkode(gora_z_ostrym_szczytem, PLIK_ROBOCZY_PRZESZKODA, DOMYSLNY_SZCZYT, skala1, pol3));
    ++Elit;
    std::cout << (*Elit)->PlikFinal() << std::endl;
    Lacze_scena.DodajNazwePliku((*Elit)->PlikFinal());



    /*(ListaObiektow.push_back(StworzPrzeszkode(plaskowyz, PLIK_ROBOCZY_PRZESZKODA, DOMYSLNY_PLASKOWYZ, skala1, pol1));
    ++Oit;
    Lacze_scena.DodajNazwePliku(((*Oit)->WezNazwePliku_BrylaFinalna()).c_str());

    ListaObiektow.push_back(StworzPrzeszkode(gora_z_grania, PLIK_ROBOCZY_PRZESZKODA, DOMYSLNY_GRANIA, skala1, pol2));
    ++Oit;
    Lacze_scena.DodajNazwePliku(((*Oit)->WezNazwePliku_BrylaFinalna()).c_str());
    
    ListaObiektow.push_back(StworzPrzeszkode(gora_z_ostrym_szczytem, PLIK_ROBOCZY_PRZESZKODA, DOMYSLNY_SZCZYT, skala1, pol3));
    ++Oit;
    Lacze_scena.DodajNazwePliku(((*Oit)->WezNazwePliku_BrylaFinalna()).c_str());*/

    Lacze_scena.ZmienTrybRys(PzG::TR_3D);
    Lacze_scena.Inicjalizuj();  // Tutaj startuje gnuplot.

    Lacze_scena.UstawZakresX(0, 200);
    Lacze_scena.UstawZakresY(0, 200);
    Lacze_scena.UstawZakresZ(0, 120);

    Lacze_scena.UstawRotacjeXZ(64,65); // Tutaj ustawiany jest widok
    Lacze_scena.Rysuj();
}

/*std::shared_ptr <BrylaGeometryczna> Scena::StworzPrzeszkode(int idx, const std::string &wzorzec, const std::string &final, const Wektor3D &skala, const Wektor3D &polozenie)
{
    if(idx == 0)
    {
        auto tmp = std::make_shared<Plaskowyz>(wzorzec, final, skala, polozenie);
        return tmp;
    }
    else if(idx == 1)
    {
        auto tmp = std::make_shared <GoraGrania> (wzorzec, final, skala, polozenie);
        return tmp;
    }
    else if(idx == 2)
    {
        auto tmp = std::make_shared <GoraSzczyt> (wzorzec, final, skala, polozenie);
        return tmp;
    }

    else 
    {
        std::cout << "Nie rozpoznano polecenia wiec tworze gore ze szczytem";
        auto tmp = std::make_shared <GoraSzczyt> (wzorzec, final, skala, polozenie);
        return tmp;
    }
}*/

void Kontrola_odczytu_liczby(double dana)
{
  while (std::cin.fail()) 
  {
    std::cerr << "Niepoprawny zapis, sprobuj jeszcze raz (liczby musza byc dodatnie): " << std::endl;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cin >> dana;
  }
}

/*void Scena::DodajPrzeszkode(int idx, const std::string &wzorzec, const std::string &final, const Wektor3D &skala, const Wektor3D &polozenie)
{
    ListaObiektow.push_back(StworzPrzeszkode(idx, wzorzec, final, skala, polozenie));
    ++Oit;
    Lacze_scena.DodajNazwePliku(((*Oit)->WezNazwePliku_BrylaFinalna()).c_str());
    Lacze_scena.Rysuj();
}*/

void Scena::DodajPrzeszkode(int idx, const std::string &wzorzec, const std::string &final, const Wektor3D &skala, const Wektor3D &polozenie)
{
    ListaElementow.push_back(StworzPrzeszkode(idx, wzorzec, final, skala, polozenie));
    ++Elit;
    Lacze_scena.DodajNazwePliku((*Elit)->PlikFinal());
    Lacze_scena.Rysuj();
}

/*void Scena::WyswietPrzeszkody()
{
    int i = 1;
    for (std::list<std::shared_ptr <BrylaGeometryczna>>::iterator it = ListaObiektow.begin(); it != ListaObiektow.end(); ++it, ++i)
    {
        std::cout << "Przeszkoda "<< i <<", polozenie: ";
        std::cout << (*it)->WezPolozenie() << std::endl;
        //std::cout << (*it)->WezNazwePliku_BrylaFinalna() << std::endl;
    }
}*/

void Scena::WyswietPrzeszkody()
{
    int i = 1;
    for (std::list<std::shared_ptr <ElementSceny>>::iterator it = ListaElementow.begin(); it != ListaElementow.end(); ++it, ++i)
    {
        std::cout << "Przeszkoda "<< i << " " << (*it)->NazwaTypu();
        std::cout << ", polozenie: \n" << (*it)->PobierzPolozenie() << "Obrys min: " << (*it)->WezObrysMin() << std::endl;
    }
}

void Scena::UsunPrzeszkode(int idx)
{
    std::list<std::shared_ptr <ElementSceny>>::iterator it = ListaElementow.begin();
    std::list<std::shared_ptr <Dron>>::iterator itdr = ListaDronow.begin();
    for (int i = 1; i < idx; ++i)
    {
        ++it;
    }
    const char *ch = (*it)->NazwaTypu();
    std::string test = ch;
    if (test == "Dron")
    {
        Drit = ListaDronow.end();
        while ((*itdr)!= (*it))
        {
            ++itdr;
        }
        std::cout << "Usuwam " << test << ": " << (*itdr)->WezPolozenie() << std::endl;
        Lacze_scena.UsunNazwePliku((*itdr)->WezKorpus().WezNazwePliku_BrylaFinalna().c_str());
        for (int i = 0; i < ILOSC_ROTOROW; ++i)
        {
            Lacze_scena.UsunNazwePliku((*itdr)->WezRotor(i).WezNazwePliku_BrylaFinalna().c_str());
        }
        if (itdr == --ListaDronow.end())
        --Drit;
        itdr = ListaDronow.erase(itdr);
        Lacze_scena.Rysuj();
    }
    else
        Lacze_scena.UsunNazwePliku((*it)->PlikFinal());
    if (it == --ListaElementow.end())
        --Elit;
    it = ListaElementow.erase(it);
    Lacze_scena.Rysuj();
}

void Scena::DodajDrona(Wektor3D pol, std::string nazwa)
{
    std::shared_ptr<Dron> wsk_dron = std::make_shared <Dron>(pol, nazwa);

    ListaDronow.push_back(wsk_dron);
    ++Drit;
    ListaElementow.push_back(wsk_dron);
    ++Elit;
    Lacze_scena.DodajNazwePliku((wsk_dron)->WezKorpus().WezNazwePliku_BrylaFinalna().c_str());
    for (int j = 0; j < ILOSC_ROTOROW; ++j)
    {
        Lacze_scena.DodajNazwePliku((wsk_dron)->WezRotor(j).WezNazwePliku_BrylaFinalna().c_str());
    }
}

void Scena::WezDrona1()
{
    int w;
    std::cout << std::endl << "Aktualnie aktywne roboty: " << std::endl;
    Drit = ListaDronow.begin();

    for(unsigned int i = 1; Drit != ListaDronow.end(); ++i, ++Drit)
    {
        std::cout << "Dron " << i << "\t Polozenie: " << (*Drit)->WezPolozenie() << std::endl;
    }

    std::cout << "Podaj numer aktywnego drona: " << std::endl;
    std::cin >> w;
    Kontrola_odczytu_liczby_dronow(w);
    Drit = ListaDronow.begin();

    for(int i = 1; i < w; ++i)
    {
        ++Drit;
    }
    std::cout << "Polozenie aktwynego drona: " << (*Drit)->WezPolozenie() << std::endl;
}

void Scena::Kontrola_odczytu_liczby_dronow(int &dana)
{
  while (std::cin.fail() || dana > ILOSC_DRONOW || dana < 1) 
  {
    std::cerr << "Niepoprawny zapis, sprobuj jeszcze raz: " << std::endl;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cin >> dana;
  }
}

void Scena::UzyjDrona1()
{
    std::vector<Wektor3D> punkty;
    std::vector<Wektor3D> punkty2;
    double dlugosc_lotu, kat_sciezka;
    std::cout << "Podaj dlugosc lotu i kat w stopniach." << std::endl;
    std::cout << "Dlugosc: ";
    std::cin >> dlugosc_lotu;
    Kontrola_odczytu_liczby(dlugosc_lotu);
    std::cout << "Kat: ";
    std::cin >> kat_sciezka;
    Kontrola_odczytu_liczby(kat_sciezka);
    (*Drit)->Planuj_sciezke(kat_sciezka, dlugosc_lotu, punkty);
    Lacze_scena.DodajNazwePliku(PLIK_TRASY_PRZELOTU);
    Lacze_scena.Rysuj();
    (*Drit)->PionowyLot(WYSOKOSC_LOTU, Lacze_scena);
    (*Drit)->ObrotLot(kat_sciezka, Lacze_scena);
    (*Drit)->PoziomyLot(punkty, Lacze_scena);
    while (!(*Drit)->CzyMoznaLadowac(ListaElementow))
    {
        std::cout << "Zmieniam trase\n";
        punkty2.clear();
        (*Drit)->PlanujZmianeSciezki(0, 10, punkty2);
        //Lacze_scena.Rysuj();
        //break;
        (*Drit)->PoziomyLotPoZmianieSciezki(punkty2, Lacze_scena);
    }
    (*Drit)->PionowyLot(-WYSOKOSC_LOTU, Lacze_scena);
}

std::shared_ptr <ElementSceny> Scena::StworzPrzeszkode(int idx, const std::string &wzorzec, const std::string &final, const Wektor3D &skala, const Wektor3D &polozenie)
{
    if(idx == 0)
    {
        auto tmp = std::make_shared<Plaskowyz>(wzorzec, final, skala, polozenie);
        return tmp;
    }
    else if(idx == 1)
    {
        auto tmp = std::make_shared <GoraGrania> (wzorzec, final, skala, polozenie);
        return tmp;
    }
    else if(idx == 2)
    {
        auto tmp = std::make_shared <GoraSzczyt> (wzorzec, final, skala, polozenie);
        return tmp;
    }

    else 
    {
        std::cout << "Nie rozpoznano polecenia wiec tworze gore ze szczytem";
        auto tmp = std::make_shared <GoraSzczyt> (wzorzec, final, skala, polozenie);
        return tmp;
    }
}

/*void Scena::DodajPlaskowyz(const std::string &wzorzec, const std::string &final, const Wektor3D &skala, const Wektor3D &polozenie)
{
    std::shared_ptr<Plaskowyz> wsk_plaskowyz = std::make_shared <Plaskowyz>(wzorzec, final, skala, polozenie);

    //ListaObiektow.push_back(wsk_plaskowyz);

    std::shared_ptr<Dron> wsk_dron = std::make_shared <Dron>(polozenie, wzorzec);

    ListaObiektow.push_back(wsk_dron);
    Lacze_scena.DodajNazwePliku((wsk_plaskowyz)->WezNazwePliku_BrylaFinalna().c_str());
    for (int j = 0; j < ILOSC_ROTOROW; ++j)
    {
        Lacze_scena.DodajNazwePliku((wsk_plaskowyz)->WezNazwePliku_BrylaFinalna().c_str());
    }
}*/

/*void Scena::UzyjDrona(Dron &dron)
{
    std::vector<Wektor3D> punkty;
    double dlugosc_lotu, kat_sciezka;
    std::cout << "Podaj dlugosc lotu i kat w stopniach." << std::endl;
    std::cout << "Dlugosc: ";
    std::cin >> dlugosc_lotu;
    Kontrola_odczytu_liczby(dlugosc_lotu);
    std::cout << "Kat: ";
    std::cin >> kat_sciezka;
    Kontrola_odczytu_liczby(kat_sciezka);
    dron.Planuj_sciezke(kat_sciezka, dlugosc_lotu, punkty);
    Lacze_scena.DodajNazwePliku(PLIK_TRASY_PRZELOTU);
    Lacze_scena.Rysuj();
    dron.PionowyLot(WYSOKOSC_LOTU, Lacze_scena);
    dron.ObrotLot(kat_sciezka, Lacze_scena);
    dron.PoziomyLot(punkty, Lacze_scena);
    dron.PionowyLot(-WYSOKOSC_LOTU, Lacze_scena);
}*/