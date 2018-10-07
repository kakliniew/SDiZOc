#include "tablica.h"
#include <iostream>
using namespace std;

Tablica::Tablica()
{
    wskaznikBazy=0;
    rozmiar=0;
};

Tablica::~Tablica()
{
    delete [] wskaznikBazy;
};


void Tablica::dodaj_poczatek(int wartosc)
{
    int *nowywskaznikBazy = new int[rozmiar+1];
    nowywskaznikBazy[0]=wartosc;
    for(int i=0;i<rozmiar;i++)
    nowywskaznikBazy[i+1]=wskaznikBazy[i];

    delete [] wskaznikBazy;
    wskaznikBazy = nowywskaznikBazy;
    rozmiar++;
};

void Tablica::dodaj_koniec(int wartosc)
{
    int *nowywskaznikBazy = new int[rozmiar+1];
    nowywskaznikBazy[rozmiar]=wartosc;
    for(int i=0;i<rozmiar;i++)
    nowywskaznikBazy[i]=wskaznikBazy[i];

    delete [] wskaznikBazy;
    wskaznikBazy = nowywskaznikBazy;
    rozmiar++;
};

void Tablica::wyswietl()
{
    if(wskaznikBazy!=0)
    {   cout<<"Elementy tablicy: ";
        for(int i=0;i<rozmiar;i++)
        {
            cout<<wskaznikBazy[i]<<" ";
        }
        cout<<endl;

    }
    else cout<<"tablica jest pusta"<<endl;
};

 void Tablica::dodaj_srodek(int wartosc,int miejsce)
 {
    bool dodano=false;
    if(miejsce==0)
    {
        dodaj_poczatek(wartosc);
        dodano=true;
    }
    if (miejsce == rozmiar)
    {
        dodaj_koniec(wartosc);
        dodano=true;

    }

    if(miejsce>0 && miejsce<rozmiar && dodano==false)
    {
    int *nowywskaznikBazy = new int[rozmiar+1];
    nowywskaznikBazy[miejsce]=wartosc;
    for(int i=0;i<miejsce;i++)
    nowywskaznikBazy[i]=wskaznikBazy[i];

    for(int i=miejsce+1;i<rozmiar+1;i++)
    nowywskaznikBazy[i]=wskaznikBazy[i-1];

    delete [] wskaznikBazy;
    wskaznikBazy = nowywskaznikBazy;
    rozmiar++;
    dodano=true;

    }
    if(dodano==false)cout<<"Nie dodano, z powodu podania zlej pozycji"<<endl;
 };

 void Tablica::usun_poczatek()
 { if(rozmiar>0) {
     int *nowywskaznikBazy = new int[rozmiar-1];

    for(int i=0;i<rozmiar-1;i++)
    nowywskaznikBazy[i]=wskaznikBazy[i+1];
    delete [] wskaznikBazy;
    wskaznikBazy = nowywskaznikBazy;

    rozmiar--;
    }
    else cout<<"tablica pusta, nie mozna usunac"<<endl;
 };

 void Tablica::usun_koniec()
 {
        if(rozmiar>0) {
     int *nowywskaznikBazy = new int[rozmiar-1];

    for(int i=0;i<rozmiar-1;i++)
    nowywskaznikBazy[i]=wskaznikBazy[i];
    delete [] wskaznikBazy;
    wskaznikBazy = nowywskaznikBazy;

    rozmiar--;
    }
    else cout<<"tablica pusta, nie mozna usunac"<<endl;

 };

 void Tablica::usun_srodek(int miejsce)
 {  bool usunieto=false;
     if(miejsce==0)
     {
         usun_poczatek();
         usunieto=true;
     }
     if(miejsce==rozmiar-1)
     {
         usun_koniec();
         usunieto=true;
     }
     if(usunieto==false && miejsce>0 && miejsce<rozmiar-1)
     {
        int *nowywskaznikBazy = new int[rozmiar-1];
        for(int i=0;i<miejsce;i++)
        nowywskaznikBazy[i]=wskaznikBazy[i];

        for(int i=miejsce;i<rozmiar-1;i++)
        nowywskaznikBazy[i]=wskaznikBazy[i+1];

        delete [] wskaznikBazy;
        wskaznikBazy = nowywskaznikBazy;
        rozmiar--;
        usunieto=true;
     }
     if(usunieto==false)cout<<"Nie udalo sie usunac, zle miejsce"<<endl;
 };

 void Tablica::wyszukaj(int wartosc)
 {
     bool istnieje=false;
     for(int i=0;i<rozmiar;i++)
     {

        if(wskaznikBazy[i]==wartosc) istnieje=true;
     }
     if(istnieje)cout<<"wartosc istnieje w tablicy"<<endl;
     else cout<<"wartosc nie istnieje w tablicy"<<endl;
 };
