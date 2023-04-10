#include "Gora_z_grania.hh"



GoraGrania::GoraGrania(const std::string& sciezkaGoraGraniaWzorcowa, const std::string& sciezkaGoraGraniaFinalna, Wektor3D skala, Wektor3D pol)
:BrylaGeometryczna(sciezkaGoraGraniaWzorcowa, sciezkaGoraGraniaFinalna)
{
    UstawSkale(skala); 
    WezPolozenie() = pol; 
    Oblicz_i_Zapisz_WspGGr();
    Nazwa_pliku_BrylaFinalna = sciezkaGoraGraniaFinalna;
    Nazwa_pliku_BrylaWzorcowa = sciezkaGoraGraniaWzorcowa; 
}

GoraGrania::GoraGrania():BrylaGeometryczna(PLIK_ROBOCZY_PRZESZKODA, DOMYSLNY_GRANIA)
{
    UstawSkale(DomyslnaSkalaGranii()); 
    Wektor3D wek; wek[0] = 90; wek[1] = 40; WezPolozenie() = wek; 
    Oblicz_i_Zapisz_WspGGr(); 
}

Wektor3D GoraGrania::TransfDoUkladuRodzica(const Wektor3D& wierz) const
{
    Wektor3D przetransformowany, polozenie;
    polozenie = WezPolozenie();
    przetransformowany = wierz;
    przetransformowany = przetransformowany + polozenie;
    return przetransformowany;
}

bool GoraGrania::Oblicz_i_Zapisz_WspGGr()
{
    std::string wzorzec, przeszkoda;
    wzorzec = WezNazwePliku_BrylaWzorcowa();
    przeszkoda = WezNazwePliku_BrylaFinalna();
    std::ifstream Bryla_Wzorcowa(wzorzec);
    std::ofstream Bryla_Finalna(przeszkoda);
    if (!Bryla_Wzorcowa.is_open()) 
    {
    std::cerr << std::endl
	 << " Blad otwarcia do odczytu pliku: " << wzorzec << std::endl
	 << std::endl;
    return false;
    }

    if (!Bryla_Finalna.is_open()) 
    {
    std::cerr << std::endl
	 << " Blad otwarcia do odczytu pliku: " << przeszkoda << std::endl
	 << std::endl;
    return false;
    }

    assert(Bryla_Wzorcowa.good());
    assert(Bryla_Finalna.good());
    Wektor3D wierz_pobrany, wierz_zmodyfikowany, wierz_max, wierz_min;
    wierz_min[1] = wierz_min[0] = MAX_YX;
    Bryla_Wzorcowa >> wierz_pobrany;
    while (!Bryla_Wzorcowa.fail()) 
    {
        for (unsigned int IloscWierzcholkow = 0; IloscWierzcholkow < ILOSC_WIERZ_LINII_TWORZACEJ; ++IloscWierzcholkow) 
        {
            wierz_zmodyfikowany = wierz_pobrany;
            wierz_zmodyfikowany = Skaluj(wierz_pobrany);
            if (wierz_zmodyfikowany[2] > 0.5) 
            {                                   // Tutaj realizowana jest deformacja
	            if (wierz_zmodyfikowany[0] < 0) 
                    wierz_zmodyfikowany[0] = fabs(wierz_zmodyfikowany[0]);
            }
            wierz_zmodyfikowany = TransfDoUkladuRodzica(wierz_zmodyfikowany);
            Bryla_Finalna << wierz_zmodyfikowany << std::endl;
            Bryla_Wzorcowa >> wierz_pobrany;
            if (wierz_zmodyfikowany[0] > wierz_max[0])    wierz_max[0] = wierz_zmodyfikowany[0];
            if (wierz_zmodyfikowany[1] > wierz_max[1])    wierz_max[1] = wierz_zmodyfikowany[1];
            if (wierz_zmodyfikowany[0] < wierz_min[0])    wierz_min[0] = wierz_zmodyfikowany[0];
            if (wierz_zmodyfikowany[1] < wierz_min[1])    wierz_min[1] = wierz_zmodyfikowany[1];

            assert(IloscWierzcholkow == ILOSC_WIERZ_LINII_TWORZACEJ-1 || !Bryla_Wzorcowa.fail());
        }
        Bryla_Finalna << std::endl;
    }
    //std::cout << wierz_min << std::endl << wierz_max << std::endl;
    WezObrys2() = wierz_max;
    WezObrys1() = wierz_min;
    //std::cout << WezObrys1() << WezObrys2();
    return !Bryla_Finalna.fail();
}