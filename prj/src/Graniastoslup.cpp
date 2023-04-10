#include "Graniastoslup.hh"

Wektor3D Graniastoslup::TransfDoUkladuRodzica(const Wektor3D& wierz) const
{
    Macierz3x3 rotacja;
    double kat;
    Wektor3D przetransformowany, polozenie_wrinika;
    polozenie_wrinika = WezPolozenie();
    przetransformowany = wierz;
    kat = WezKat();
    rotacja = ObrotZ(kat);

    przetransformowany = rotacja * wierz;
    przetransformowany = przetransformowany + polozenie_wrinika;

    return przetransformowany;
}

Wektor3D DomyslnaSkalaRotora() 
{
    Wektor3D wek; 
    wek[0] = SKALA_ROTORA_X; 
    wek[1] = SKALA_ROTORA_Y; 
    wek[2] = SKALA_ROTORA_Z; 
    return wek;
}
