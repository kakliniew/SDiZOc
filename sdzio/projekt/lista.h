#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <iostream>
#include "elementlisty.h"



using namespace std;

class Lista{
public:
Elementlisty *pierwszy;
Elementlisty *ostatni;
Elementlisty *pomoc;

int rozmiar;


Lista();
void dodaj_poczatek(int wartosc);
void dodaj_koniec(int wartosc);
void dodaj_srodek(int wartosc,int miejsce);
void dodaj_za(int wartosc_zastepowana,int wartosc_nowa);

void usun_poczatek();
void usun_koniec();
void usun_srodek(int miejsce);
void usun_wartosc(int wartosc);

bool wyszukaj(int wartosc);
void wyswietl();

};



#endif // LISTA_H_INCLUDED
