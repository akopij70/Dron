#include "Prostopadloscian.hh"

Wektor3D Prostopadloscian::TransfDoUkladuRodzica(const Wektor3D& wierz) const
{
    Macierz3x3 rotacja;
    double kat;
    Wektor3D przetransformowany, polozenie;
    polozenie = WezPolozenie();
    przetransformowany = wierz;
    kat = WezKat();
    rotacja = ObrotZ(kat);
    przetransformowany = rotacja * wierz;
    przetransformowany = przetransformowany + polozenie;
    return przetransformowany;
}

Wektor3D DomyslnaSkalaKorpusu() {Wektor3D wek; wek[0] = SKALA_KORPUSU_X; wek[1] = SKALA_KORPUSU_Y; wek[2] = SKALA_KORPUSU_Z; return wek;}