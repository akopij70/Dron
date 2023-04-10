#include "Dron.hh"

Dron::Dron()
{
    Wektor3D translacja_rotor_1, translacja_rotor_2, translacja_rotor_3, translacja_rotor_4;
    double poczatkowy_kat = 0;

    Polozenie[0] = 20, Polozenie[1] = 20; Polozenie[2] = 2;
    translacja_rotor_1[0] = 5; translacja_rotor_1[1] = 4; translacja_rotor_1[2] = 3;
    translacja_rotor_2[0] = 5; translacja_rotor_2[1] = -4; translacja_rotor_2[2] = 3;
    translacja_rotor_3[0] = -5; translacja_rotor_3[1] = 4; translacja_rotor_3[2] = 3;
    translacja_rotor_4[0] = -5; translacja_rotor_4[1] = -4; translacja_rotor_4[2] = 3;

    Kat_Orientacji = 0;

    Korpus = Prostopadloscian(PLIK_WZORCOWEGO_SZESCIANU, PLIK_WLASCIWY__DRON1_KORPUS);
    Korpus.UstawSkale(DomyslnaSkalaKorpusu());

    RotorDrona[0] = Graniastoslup(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, PLIK_WLASCIWY__DRON1_ROTOR1);
    RotorDrona[1] = Graniastoslup(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, PLIK_WLASCIWY__DRON1_ROTOR2);
    RotorDrona[2] = Graniastoslup(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, PLIK_WLASCIWY__DRON1_ROTOR3);
    RotorDrona[3] = Graniastoslup(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, PLIK_WLASCIWY__DRON1_ROTOR4);
    for (int i = 0; i < ILOSC_ROTOROW; ++i)
    {
      RotorDrona[i].UstawSkale(DomyslnaSkalaRotora());
      RotorDrona[i].WezKat() = poczatkowy_kat;
    }
    RotorDrona[0].WezPolozenie() = translacja_rotor_1;
    RotorDrona[1].WezPolozenie() = translacja_rotor_2;
    RotorDrona[2].WezPolozenie() = translacja_rotor_3;
    RotorDrona[3].WezPolozenie() = translacja_rotor_4;

    Korpus.WezKat() = poczatkowy_kat;

    Oblicz_i_Zapisz_WspGlbDrona();
}


Dron::Dron(Wektor3D polozenie, std::string nazwa)
{
    Wektor3D skala_korpus, skala_rotor, translacja_rotor_1, translacja_rotor_2, translacja_rotor_3, translacja_rotor_4;
    double poczatkowy_kat = 0;

    std::string sciezka = BRYLY_FINALNE + nazwa;

    Polozenie[0] = polozenie[0], Polozenie[1] = polozenie[1]; Polozenie[2] = 2;

    skala_korpus = DomyslnaSkalaKorpusu();

    translacja_rotor_1[0] =  5; translacja_rotor_1[1] = 4; translacja_rotor_1[2] = 3;
    translacja_rotor_2[0] =  5; translacja_rotor_2[1] =  - 4; translacja_rotor_2[2] = 3;
    translacja_rotor_3[0] =  - 5; translacja_rotor_3[1] =  + 4; translacja_rotor_3[2] = 3;
    translacja_rotor_4[0] =  - 5; translacja_rotor_4[1] =  - 4; translacja_rotor_4[2] = 3;

    Kat_Orientacji = 0;

    std::string plik_korpus = sciezka + "korpus.dat";
    Korpus = Prostopadloscian(PLIK_WZORCOWEGO_SZESCIANU, plik_korpus);
    Korpus.UstawSkale(skala_korpus);
    Korpus.WezKat() = poczatkowy_kat;

    for (int i = 0; i < ILOSC_ROTOROW; ++i)
    {
        std::string plik_rotor = sciezka + "rotor" + std::to_string(i+1) + ".dat";
        RotorDrona[i] = Graniastoslup(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, plik_rotor);
        RotorDrona[i].UstawSkale(DomyslnaSkalaRotora());
        RotorDrona[i].WezKat() = poczatkowy_kat;
    }   

    RotorDrona[0].WezPolozenie() = translacja_rotor_1;
    RotorDrona[1].WezPolozenie() = translacja_rotor_2;
    RotorDrona[2].WezPolozenie() = translacja_rotor_3;
    RotorDrona[3].WezPolozenie() = translacja_rotor_4;

    Oblicz_i_Zapisz_WspGlbDrona();
}


bool Dron::Planuj_sciezke(double Kat_skretu, double Dlugosc_lotu, std::vector<Wektor3D>& punkty)
{
    Wektor3D tymczasowy_pkt, pol_dron;
    Macierz3x3 rotacja;
    double kat_drona = WezKat();
    std::ofstream plik_trasy(PLIK_TRASY_PRZELOTU);

    if (!plik_trasy.is_open()) 
    {
    std::cerr << std::endl
	  << " Nie mozna otworzyc do zapisu pliku: " << PLIK_TRASY_PRZELOTU << std::endl
	  << std::endl;
    return false;
    }

    rotacja = ObrotZ((Kat_skretu+kat_drona));
    pol_dron = WezPolozenie();

    punkty.push_back(pol_dron);
    tymczasowy_pkt = pol_dron;
    tymczasowy_pkt[2] = pol_dron[2] + WYSOKOSC_LOTU;
    punkty.push_back(tymczasowy_pkt);
    tymczasowy_pkt[0] = Dlugosc_lotu;
    tymczasowy_pkt[1] = 0;
    tymczasowy_pkt = rotacja * tymczasowy_pkt;
    tymczasowy_pkt = tymczasowy_pkt + pol_dron;
    punkty.push_back(tymczasowy_pkt);
    tymczasowy_pkt[2] = tymczasowy_pkt[2] - WYSOKOSC_LOTU;
    punkty.push_back(tymczasowy_pkt);

    for (unsigned int i = 0; i < punkty.size(); ++i)
    {
        plik_trasy << punkty[i] << std::endl;
    }
    return true;
}

bool Dron::Oblicz_i_Zapisz_WspGlbKorpusu()
{
    std::string lokalny_korpus, globalny_korpus;
    lokalny_korpus = Korpus.WezNazwePliku_BrylaWzorcowa();
    globalny_korpus = Korpus.WezNazwePliku_BrylaFinalna();
    std::ifstream Bryla_Wzorcowa(lokalny_korpus);
    std::ofstream Bryla_Finalna(globalny_korpus);
    if (!Bryla_Wzorcowa.is_open()) 
    {
    std::cerr << std::endl
	 << " Blad otwarcia do odczytu pliku: " << lokalny_korpus << std::endl
	 << std::endl;
    return false;
    }

    if (!Bryla_Finalna.is_open()) 
    {
    std::cerr << std::endl
	 << " Blad otwarcia do odczytu pliku: " << globalny_korpus << std::endl
	 << std::endl;
    return false;
    }

    assert(Bryla_Wzorcowa.good());
    assert(Bryla_Finalna.good());
    Wektor3D wierz_pobrany, wierz_zmodyfikowany, wierz_max;
    Bryla_Wzorcowa >> wierz_pobrany;
    while (!Bryla_Wzorcowa.fail()) 
    {
        for (unsigned int IloscWierzcholkow = 0; IloscWierzcholkow < ILOSC_WIERZ_LINII_TWORZACEJ; ++IloscWierzcholkow) 
        {
            wierz_zmodyfikowany = wierz_pobrany;
            wierz_zmodyfikowany = Korpus.Skaluj(wierz_pobrany);
            wierz_zmodyfikowany = Korpus.TransfDoUkladuRodzica(wierz_zmodyfikowany);
            wierz_zmodyfikowany = TransfDoUklWspRodzica(wierz_zmodyfikowany);
            Bryla_Finalna << wierz_zmodyfikowany << std::endl;
            Bryla_Wzorcowa >> wierz_pobrany;
            if (wierz_zmodyfikowany[0] > wierz_max[0])    wierz_max[0] = wierz_zmodyfikowany[0];
            if (wierz_zmodyfikowany[1] > wierz_max[1])    wierz_max[1] = wierz_zmodyfikowany[1];

            assert(IloscWierzcholkow == ILOSC_WIERZ_LINII_TWORZACEJ-1 || !Bryla_Wzorcowa.fail());
        }
        Bryla_Finalna << std::endl;
    }
    //std::cout << wierz_max << std::endl;
    ObliczPromien(wierz_max);
    return !Bryla_Finalna.fail();
}

bool Dron::Oblicz_i_Zapisz_WspGlbRotora(const Graniastoslup& Rotor) const
{
    std::string lokalny_rotor, globalny_rotor;
    lokalny_rotor = Rotor.WezNazwePliku_BrylaWzorcowa();
    globalny_rotor = Rotor.WezNazwePliku_BrylaFinalna();
    std::ifstream Bryla_Wzorcowa(lokalny_rotor);
    std::ofstream Bryla_Finalna(globalny_rotor);
    if (!Bryla_Wzorcowa.is_open()) 
    {
    std::cerr << std::endl
	 << " Blad otwarcia do odczytu pliku: " << lokalny_rotor << std::endl
	 << std::endl;
    return false;
    }

    if (!Bryla_Finalna.is_open()) 
    {
    std::cerr << std::endl
	 << " Blad otwarcia do odczytu pliku: " << globalny_rotor << std::endl
	 << std::endl;
    return false;
    }

    assert(Bryla_Wzorcowa.good());
    assert(Bryla_Finalna.good());
    Wektor3D wierz_pobrany, wierz_zmodyfikowany;
    Bryla_Wzorcowa >> wierz_pobrany;
    while (!Bryla_Wzorcowa.fail()) 
    {
        for (unsigned int IloscWierzcholkow = 0; IloscWierzcholkow < ILOSC_WIERZ_LINII_TWORZACEJ; ++IloscWierzcholkow) 
        {
            wierz_zmodyfikowany = wierz_pobrany;
            wierz_zmodyfikowany = Rotor.Skaluj(wierz_pobrany);
            wierz_zmodyfikowany = Rotor.TransfDoUkladuRodzica(wierz_zmodyfikowany);
            wierz_zmodyfikowany = TransfDoUklWspRodzica(wierz_zmodyfikowany);
            Bryla_Finalna << wierz_zmodyfikowany << std::endl;
            Bryla_Wzorcowa >> wierz_pobrany;  

            assert(IloscWierzcholkow == ILOSC_WIERZ_LINII_TWORZACEJ-1 || !Bryla_Wzorcowa.fail());
        }
        Bryla_Finalna << std::endl;
    }
  return !Bryla_Finalna.fail();
}

bool Dron::Oblicz_i_Zapisz_WspGlbDrona()
{
    if (!Oblicz_i_Zapisz_WspGlbKorpusu())
    {
        std::cerr << std::endl << " Blad zapisu wspolrzednych korpusu " << std::endl << std::endl;
        return false;
    } 
    for (int i = 0; i < ILOSC_ROTOROW; ++i)
    {
        if(!Oblicz_i_Zapisz_WspGlbRotora(RotorDrona[i]))
        {
            std::cerr << std::endl << " Blad zapisu wspolrzednych rotora nr " << i << std::endl << std::endl;
            return false;
        }
    }

    return true;
}

bool Dron::PionowyLot(double Dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze)
{
    Wektor3D polozenie_dron = WezPolozenie();

    if (Dlugosc_lotu > 0)
    {
        std::cout << std::endl << "Wznoszenie ... " << std::endl;
        for (; (Dlugosc_lotu+2) > 0; Dlugosc_lotu-=2,  polozenie_dron[2] += 2) 
        {
            ObracajRotorami();
            WezPolozenie() = polozenie_dron;
            if (!Oblicz_i_Zapisz_WspGlbDrona()) return false;
            usleep(100000); // 0.1 ms
            Lacze.Rysuj();
        }
    }
    else if (Dlugosc_lotu < 0)
    {
        std::cout << std::endl << "Opadanie ... " << std::endl;
        for (; (Dlugosc_lotu-2) < 0; Dlugosc_lotu+= 2, polozenie_dron[2] -= 2) 
        {
            ObracajRotorami();
            WezPolozenie() = polozenie_dron;
            if (!Oblicz_i_Zapisz_WspGlbDrona()) return false;
            usleep(100000); // 0.1 ms
            Lacze.Rysuj();
        }
    }
    return true;
}

bool Dron::PoziomyLot(std::vector<Wektor3D>& punkty, PzG::LaczeDoGNUPlota& Lacze)
{
    Wektor3D polozenie_dron, punkt;
    double Dlugosc_lotu, Dlugosc_y, stosunek_y_do_x;
    punkt = punkty[2];
    Dlugosc_lotu = punkt[0];
    Dlugosc_y = punkt[1];
    polozenie_dron = WezPolozenie();

    if (Dlugosc_lotu == polozenie_dron[0])
        stosunek_y_do_x = 1;
    else
        stosunek_y_do_x = (Dlugosc_y-polozenie_dron[1])/(Dlugosc_lotu - polozenie_dron[0]);

    std::cout << std::endl << "Lot w bok ... " << std::endl;
    if (Dlugosc_lotu > polozenie_dron[0])
    {
        for (; polozenie_dron[0] < Dlugosc_lotu; polozenie_dron[0] += 1, polozenie_dron[1] += stosunek_y_do_x) 
        {
            WezPolozenie() = polozenie_dron;
            ObracajRotorami();
            if (!Oblicz_i_Zapisz_WspGlbDrona()) return false;
            usleep(100000); // 0.1 ms
            Lacze.Rysuj();
        }
        std::cout << polozenie_dron << std::endl;
    }
    else if (Dlugosc_lotu < polozenie_dron[0])
    {
        for (; polozenie_dron[0] > Dlugosc_lotu; polozenie_dron[0] -= 1, polozenie_dron[1] -= stosunek_y_do_x) 
        {
            WezPolozenie() = polozenie_dron;
            ObracajRotorami();
            if (!Oblicz_i_Zapisz_WspGlbDrona()) return false;
            usleep(100000); // 0.1 ms
            Lacze.Rysuj();
        }
        std::cout << polozenie_dron << std::endl;
    }

    else if (Dlugosc_lotu == polozenie_dron[0])
    {
        std::cout << "Tutaj";
        if (Dlugosc_y > polozenie_dron[1])
        {
            for (; Dlugosc_y > polozenie_dron[1]; polozenie_dron[1] += stosunek_y_do_x) 
            {
                WezPolozenie() = polozenie_dron;
                ObracajRotorami();
                if (!Oblicz_i_Zapisz_WspGlbDrona()) return false;
                usleep(100000); // 0.1 ms
                Lacze.Rysuj();
            }
            std::cout << polozenie_dron << std::endl;
        }
        else if (Dlugosc_y < polozenie_dron[1])
        {
            for (; Dlugosc_y < polozenie_dron[1]; polozenie_dron[1] -= stosunek_y_do_x) 
            {
                WezPolozenie() = polozenie_dron;
                ObracajRotorami();
                if (!Oblicz_i_Zapisz_WspGlbDrona()) return false;
                usleep(100000); // 0.1 ms
                Lacze.Rysuj();
            }
            std::cout << polozenie_dron << std::endl;
        }
    }    
    return true;
}

bool Dron::ObrotLot(double Kat, PzG::LaczeDoGNUPlota& Lacze)
{
    double kat_dron = WezKat();
    double kat_do_kontroli = 0;
    ObracajRotorami();

    std::cout << std::endl << "Zmiana orientacji..."  << std::endl;

    if (Kat > 0)
    {
        for (; kat_do_kontroli <= Kat; kat_do_kontroli += 5, kat_dron += 5)
        {
            WezKat() = kat_dron;
            if (!Oblicz_i_Zapisz_WspGlbDrona()) return false;
            usleep(100000); // 0.1 ms
            Lacze.Rysuj();
        }
    }
    else if (Kat < 0)
    {
        for (; kat_do_kontroli >= Kat; kat_do_kontroli -= 5, kat_dron -= 5)
        {
            WezKat() = kat_dron;
            if (!Oblicz_i_Zapisz_WspGlbDrona()) return false;
            usleep(100000); // 0.1 ms
            Lacze.Rysuj();
        }
    }
    return true;  
}

Wektor3D Dron::TransfDoUklWspRodzica(const Wektor3D &wek) const
{
    Macierz3x3 rotacja;
    double kat;
    Wektor3D przetransformowany, polozenie_drona;
    polozenie_drona = WezPolozenie();
    przetransformowany = wek;
    kat = WezKat();
    rotacja = ObrotZ(kat);

    przetransformowany = rotacja * wek;
    przetransformowany = przetransformowany + polozenie_drona;

    return przetransformowany;
}

void Dron::ObliczPromien(Wektor3D punkt)
{
    Wektor2D transoformowane_pol, transformowany_pkt;
    Wektor3D pol = WezPolozenie();
    transoformowane_pol = pol;
    transformowany_pkt = punkt;
    double promien = (transformowany_pkt.Oblicz_dlugosc(transoformowane_pol))*STALA_DO_PROMIENIA;
    //std::cout << transformowany_pkt << transoformowane_pol;
    //std::cout << "\n\n\nPromien" << promien << "\n\n\n";
    WezPromien() = promien;
}

void Dron::ObracajRotorami()
{
    double kat_rotor[ILOSC_ROTOROW];
    for  (int i = 0; i < ILOSC_ROTOROW; ++i)
    {
        kat_rotor[i] = RotorDrona[i].WezKat();
    }
    kat_rotor[0] += SKOK_OBROTU_ROTOROW_stopnie;
    kat_rotor[1] -= SKOK_OBROTU_ROTOROW_stopnie;
    kat_rotor[2] -= SKOK_OBROTU_ROTOROW_stopnie;
    kat_rotor[3] += SKOK_OBROTU_ROTOROW_stopnie;

    for  (int i = 0; i < ILOSC_ROTOROW; ++i)
    {
        RotorDrona[i].WezKat() = kat_rotor[i];
    }
}

bool Dron::CzyMoznaLadowac(const std::list <std::shared_ptr<ElementSceny>> &ElementySceny) const
{
    for(std::list <std::shared_ptr<ElementSceny>>::const_iterator wsk = ElementySceny.begin(); wsk != ElementySceny.end(); ++wsk)
    {
        //std::cout << (*wsk)->NazwaTypu() << std::endl;
        Wektor3D wek = WezPolozenie();
        double pr = WezPromien();
        if ((*wsk)->CzyObrysyNakladajaSie(wek, pr))
            { std::cout << "Zderzenie z obiektem:\t" << (*wsk)->NazwaTypu() << std::endl; return false;}
    }
    std::cout<< "BRAK KOLIZJI";
    return true;
}

bool Dron::PlanujZmianeSciezki(double Kat_skretu, double Dlugosc_lotu, std::vector<Wektor3D>& punkty)
{
    Wektor3D tymczasowy_pkt, pol_dron;
    Macierz3x3 rotacja;
    double kat_drona = WezKat();
    std::ofstream plik_trasy(PLIK_TRASY_PRZELOTU);

    rotacja = ObrotZ((Kat_skretu+kat_drona));
    pol_dron = WezPolozenie();

    punkty.push_back(pol_dron);
    tymczasowy_pkt = pol_dron;
    tymczasowy_pkt[0] = Dlugosc_lotu;
    tymczasowy_pkt[1] = 0;
    //tymczasowy_pkt[2] = pol_dron[2];
    tymczasowy_pkt = rotacja * tymczasowy_pkt;
    tymczasowy_pkt = tymczasowy_pkt + pol_dron;
    tymczasowy_pkt[2] = pol_dron[2];
    //std::cout << "Taki pkt:" << tymczasowy_pkt;
    punkty.push_back(tymczasowy_pkt);

    return true;
}

bool Dron::PoziomyLotPoZmianieSciezki(std::vector<Wektor3D>& punkty, PzG::LaczeDoGNUPlota& Lacze)
{
    Wektor3D polozenie_dron, punkt;
    double Dlugosc_lotu, Dlugosc_y, stosunek_y_do_x;
    punkt = punkty[1];
    Dlugosc_lotu = punkt[0];
    Dlugosc_y = punkt[1];
    polozenie_dron = WezPolozenie();

    if (Dlugosc_lotu == polozenie_dron[0])
        stosunek_y_do_x = 1;
    else
        stosunek_y_do_x = (Dlugosc_y-polozenie_dron[1])/(Dlugosc_lotu - polozenie_dron[0]);

    std::cout << std::endl << "Lot w bok ... " << std::endl;
    if (Dlugosc_lotu > polozenie_dron[0])
    {
        for (; polozenie_dron[0] < Dlugosc_lotu; polozenie_dron[0] += 1, polozenie_dron[1] += stosunek_y_do_x) 
        {
            WezPolozenie() = polozenie_dron;
            ObracajRotorami();
            if (!Oblicz_i_Zapisz_WspGlbDrona()) return false;
            usleep(100000); // 0.1 ms
            Lacze.Rysuj();
        }
        std::cout << polozenie_dron << std::endl;
    }
    else if (Dlugosc_lotu < polozenie_dron[0])
    {
        for (; polozenie_dron[0] > Dlugosc_lotu; polozenie_dron[0] -= 1, polozenie_dron[1] -= stosunek_y_do_x) 
        {
            WezPolozenie() = polozenie_dron;
            ObracajRotorami();
            if (!Oblicz_i_Zapisz_WspGlbDrona()) return false;
            usleep(100000); // 0.1 ms
            Lacze.Rysuj();
        }
        std::cout << polozenie_dron << std::endl;
    }

    else if (Dlugosc_lotu == polozenie_dron[0])
    {
        std::cout << "Tutaj";
        if (Dlugosc_y > polozenie_dron[1])
        {
            for (; Dlugosc_y > polozenie_dron[1]; polozenie_dron[1] += stosunek_y_do_x) 
            {
                WezPolozenie() = polozenie_dron;
                ObracajRotorami();
                if (!Oblicz_i_Zapisz_WspGlbDrona()) return false;
                usleep(100000); // 0.1 ms
                Lacze.Rysuj();
            }
            std::cout << polozenie_dron << std::endl;
        }
        else if (Dlugosc_y < polozenie_dron[1])
        {
            for (; Dlugosc_y < polozenie_dron[1]; polozenie_dron[1] -= stosunek_y_do_x) 
            {
                WezPolozenie() = polozenie_dron;
                ObracajRotorami();
                if (!Oblicz_i_Zapisz_WspGlbDrona()) return false;
                usleep(100000); // 0.1 ms
                Lacze.Rysuj();
            }
            std::cout << polozenie_dron << std::endl;
        }
    }    
    return true;
}