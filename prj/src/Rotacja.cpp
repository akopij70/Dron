#include "Rotacja.hh"

/*
 * Tworzy ostateczna macierz obrotu przez wymnozenie macierzy
 * Argumenty:
 *    lista_obrotow - kontener z macierzami do wymnozenia
 * Zwraca:
 *    rot_fin - finalna macierz obrotu
 */
Macierz3x3 UstawObrot(std::vector<Rotacja> lista_obrotow)
{
    Macierz3x3 rot_fin;
    rot_fin.Macierz_jednostkowa();
    for (unsigned int i = 0; i < lista_obrotow.size(); ++i)
    {
        rot_fin *= UstawOs(lista_obrotow[i]);
    }
    return rot_fin;
}

/*
 * Tworzy macierz obrotu w zaleznosci od osi i kata
 * Argumenty:
 *    Rot - obiekt rotacja zawierajacy informacje o kacie i osi
 * Zwraca:
 *    macierz_obrotu - macierz obrotu stworzona na podstawie przekazanych danych
 */
Macierz3x3 UstawOs(Rotacja Rot)
{
    Macierz3x3 macierz_obrotu;
    double kat = Rot.wez_kat();
    char os = Rot.wez_os();
    switch(os)
    {
        case 'x':
            macierz_obrotu = ObrotX(kat);
            break;
        case 'y':
            macierz_obrotu = ObrotY(kat);
            break;
        case 'z':
            macierz_obrotu = ObrotZ(kat);
            break;
        default:
            std::cout << "Nie rozpoznano osi" << std::endl;
            break;
    }
    return macierz_obrotu;
}

/*
 * Tworzy macierz obrotu wokol osi X o zadany kat
 * Argumenty:
 *    kat - kat obrotu
 * Zwraca:
 *    obrot_x - macierz obrotu
 */
Macierz3x3 ObrotX(double kat)
{
    Macierz3x3 obrot_x;
    double radiany = kat * M_PI/180;
    obrot_x(0, 0) = 1.0;
    obrot_x(0, 1) = 0.0;
    obrot_x(0, 2) = 0.0;
    obrot_x(1, 0) = 0.0;
    obrot_x(1, 1) = cos(radiany);
    obrot_x(1, 2) = -sin(radiany);
    obrot_x(2, 0) = 0.0;
    obrot_x(2, 1) = sin(radiany);
    obrot_x(2, 2) = cos(radiany);
    return obrot_x;
}

/*
 * Tworzy macierz obrotu wokol osi Y o zadany kat
 * Argumenty:
 *    kat - kat obrotu
 * Zwraca:
 *    obrot_y - macierz obrotu
 */
Macierz3x3 ObrotY(double kat)
{
    Macierz3x3 obrot_y;
    double radiany = kat * M_PI/180;
    obrot_y(0, 0) = cos(radiany);
    obrot_y(0, 1) = 0.0;
    obrot_y(0, 2) = sin(radiany);
    obrot_y(1, 0) = 0.0;
    obrot_y(1, 1) = 1.0;
    obrot_y(1, 2) = 0.0;
    obrot_y(2, 0) = -sin(radiany);
    obrot_y(2, 1) = 0.0;
    obrot_y(2, 2) = cos(radiany);
    return obrot_y;
}

/*
 * Tworzy macierz obrotu wokol osi Z o zadany kat
 * Argumenty:
 *    kat - kat obrotu
 * Zwraca:
 *    obrot_z - macierz obrotu
 */
Macierz3x3 ObrotZ(double kat)
{
    Macierz3x3 obrot_z;
    double radiany = kat * M_PI/180;
    obrot_z(0, 0) = cos(radiany);
    obrot_z(0, 1) = -sin(radiany);
    obrot_z(0, 2) = 0.0;
    obrot_z(1, 0) = sin(radiany);
    obrot_z(1, 1) = cos(radiany);
    obrot_z(1, 2) = 0.0;
    obrot_z(2, 0) = 0.0;
    obrot_z(2, 1) = 0.0;
    obrot_z(2, 2) = 1.0;
    return obrot_z;
}

/*
 * Pobiera od uzytkownika dane na temat sekwencji obrotow
 * Argumenty:
 *    brak
 * Zwraca:
 *    lista_obrotow - kontener z informacjami o obrotach
 */
std::vector<Rotacja> Pobierz_dane()
{
    Rotacja rot;
    std::vector<Rotacja> lista_obrotow;
    char os;
    double kat;
    std::cout << "Os: ";
    std::cin >> os;
    while (os != '.')
    {
        switch (os)
        {
            case 'x':
            case 'y':
            case 'z':
                std::cout << "Kat: ";
                std::cin >> kat;
                while (std::cin.fail())
                {
                    std::cerr << "Niepoprawny zapis liczby, sprobuj jeszcze raz: " << std::endl;
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Kat: ";
                    std::cin >> kat;
                }
                rot.modyfikuj_os() = os;
                rot.modyfikuj_kat() = kat;
                lista_obrotow.push_back(rot);
                std::cout << "Os: ";
                std::cin >> os;
                break;
            case '.': 
                break;
            default:
                std::cout << "Nie rozpoznano osi, sprobuj jeszcze raz.\n";
                std::cout << "Os: ";
                std::cin >> os;
                break;
        }
    }
    return lista_obrotow;
}

/*
 * Przeciazenie operatora << w celu wyswietlenia obiektu rotacja, funkcja przydatna przy testach
 * Argumenty:
 *    Strm - strumien
 *    Rot - obiekt do wyswietlenia
 * Zwraca:
 *    Strm - strumien
 */
std::ostream& operator << ( std::ostream &Strm, const Rotacja &Rot)
{
    Strm << Rot.wez_os() << std::endl;
    Strm << Rot.wez_kat();
    return Strm;
}