#ifndef KOPIEC_H_INCLUDED
#define KOPIEC_H_INCLUDED

#include <iostream>
using namespace std;

class Kopiec
{public:
    int *wskaznikKorzenia;
    int rozmiar;

    Kopiec();

    void dodaj_element(int wartosc);
    void usun_element(int wartosc);

    bool wyszukaj(int wartosc);
    void wyswietl();
    double log_dwa(int liczba);
    void przywroc_kopiec();


};

#endif // KOPIEC_H_INCLUDED
