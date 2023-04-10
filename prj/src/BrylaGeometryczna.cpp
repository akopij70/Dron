#include "BrylaGeometryczna.hh"



Wektor3D BrylaGeometryczna::Skaluj(const Wektor3D& Wierz) const
{
    Wektor3D przeskalowany, skala;
    Macierz3x3 mac_skali;
    skala = WezSkale();
    mac_skali = mac_skali.Stworz_macierz_ze_skala(skala);
    przeskalowany = mac_skali * Wierz;
    return przeskalowany;
}