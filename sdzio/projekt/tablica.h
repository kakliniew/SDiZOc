#ifndef TABLICA_H_INCLUDED
#define TABLICA_H_INCLUDED

#include <iostream>
using namespace std;

class Tablica {
public:
    int *wskaznikBazy;
    int rozmiar;

    Tablica();
    ~Tablica();
    void dodaj_poczatek(int wartosc);
    void dodaj_koniec(int wartosc);
    void dodaj_srodek(int wartosc,int miejsce);

    void usun_poczatek();
    void usun_koniec();
    void usun_srodek(int miejsce);

    void wyszukaj(int wartosc);
    void wyswietl();




};


#endif // TABLICA_H_INCLUDED
