#include "lista.h"
using namespace std;

Lista::Lista(){
pierwszy = 0;
ostatni = 0;
rozmiar = 0; };

void Lista::dodaj_koniec(int wartosc){
    Elementlisty *nowy = new Elementlisty;
    nowy -> wartosc = wartosc;
    rozmiar++;
    if (pierwszy==0)
    {
        pierwszy = nowy;
        ostatni = nowy;
    }
    else {
            nowy->poprzedni = ostatni;
            ostatni->nastepny = nowy;
            nowy-> nastepny = 0;
            ostatni = nowy;
    }
};

void Lista::dodaj_poczatek(int wartosc){
    Elementlisty *nowy = new Elementlisty;
    nowy -> wartosc = wartosc;
    rozmiar++;
    if (pierwszy==0)
    {
        pierwszy = nowy;
        ostatni = nowy;
    }
    else {
            nowy->nastepny = pierwszy;
            pierwszy->poprzedni = nowy;
            nowy-> poprzedni = 0;
            pierwszy = nowy;
    }
};

void Lista::dodaj_srodek(int wartosc, int miejsce){
 bool dodano=false;
    if(miejsce==1)
    {
        dodaj_poczatek(wartosc);
    }
    if (miejsce == rozmiar + 1)
    {
        dodaj_koniec(wartosc);
    }


    if(miejsce>rozmiar+1/2 && miejsce<rozmiar+1)
        {
            pomoc = ostatni;
            for(int i=1;i<rozmiar-miejsce+1;i++)
            {
                pomoc = pomoc-> poprzedni;
            }


            rozmiar++;

            Elementlisty *nowy2 = new Elementlisty;
         nowy2->wartosc= wartosc;

            nowy2->poprzedni= pomoc;
            nowy2->nastepny=pomoc->nastepny;
            pomoc->nastepny->poprzedni= nowy2;
            pomoc->nastepny = nowy2;
        dodano=true;

        }

        if(miejsce<=rozmiar+1/2 && miejsce>1 && dodano==false)
        {
            pomoc = pierwszy;
            for(int i=1;i<miejsce-1;i++)
            {
                pomoc = pomoc-> nastepny;
            }


            rozmiar++;

            Elementlisty *nowy1 = new Elementlisty;
            nowy1->wartosc= wartosc;

            nowy1->poprzedni= pomoc;
            nowy1->nastepny=pomoc->nastepny;
            pomoc->nastepny = nowy1;

            pomoc->nastepny->poprzedni= nowy1;
        }






};


void Lista::usun_koniec(){
    if(rozmiar>1){
ostatni->poprzedni->nastepny=0;
ostatni=ostatni->poprzedni;
rozmiar--; }
else {pierwszy=0;
ostatni=0;
rozmiar=0;}
};

void Lista::usun_poczatek(){
if(rozmiar>1){
pierwszy->nastepny->poprzedni=0;
pierwszy=pierwszy->nastepny;
rozmiar--;
}
else {pierwszy=0;
ostatni=0;
rozmiar=0;}
};


void Lista::usun_srodek(int miejsce){
    if(rozmiar<miejsce || miejsce<1)
        cout<<"Nie ma takiego miejsca na liscie"<<endl;
    if(miejsce==1)usun_poczatek();
    if(miejsce==rozmiar){
            usun_koniec();
    }
    if(miejsce>rozmiar/2  && miejsce<rozmiar){
        pomoc = ostatni;
        for(int i=1; i<rozmiar-miejsce+1;i++)
        {
            pomoc = pomoc->poprzedni;
        }
        pomoc->poprzedni->nastepny=pomoc->nastepny;
        pomoc->nastepny->poprzedni=pomoc->poprzedni;

    }

    if(miejsce<=rozmiar/2  && miejsce>1){
        pomoc = pierwszy;
        for(int i=1; i<miejsce;i++)
        {
            pomoc = pomoc->nastepny;
        }
        pomoc->poprzedni->nastepny=pomoc->nastepny;
        pomoc->nastepny->poprzedni=pomoc->poprzedni;

    }


};

void Lista::wyswietl(){
    Elementlisty *nowy = pierwszy;
    while(nowy)
    {
        cout<<nowy->wartosc<<" ";
        nowy=nowy->nastepny;
    }
    cout<<endl;
};

bool Lista::wyszukaj(int wartosc){
    bool istnieje=false;
     pomoc=pierwszy;
     for(int i=1;i<rozmiar+1;i++)
     {
         if(pomoc->wartosc==wartosc)istnieje=true;
         pomoc= pomoc->nastepny;
     }
    return istnieje;

};

void Lista::usun_wartosc(int wartosc)
{
    if(Lista::wyszukaj(wartosc))
    {   pomoc= pierwszy;
        for(int i=1;i<rozmiar+1;i++)
         {
             if(pomoc->wartosc==wartosc)Lista::usun_srodek(i);
             pomoc= pomoc->nastepny;
         }

        cout<<"usunieto pomyslnie"<<endl;
    }

    else cout<<"Wartosc nie istnieje"<<endl;

};

void Lista::dodaj_za(int wartosc_zastepowana,int wartosc_nowa)
{
    if(Lista::wyszukaj(wartosc_zastepowana))
    {   pomoc=pierwszy;
        for(int i=1;i<rozmiar+1;i++)
         {
             if(pomoc->wartosc==wartosc_zastepowana)pomoc->poprzedni->nastepny->wartosc=wartosc_nowa;
             pomoc= pomoc->nastepny;
         }

    }
    else dodaj_poczatek(wartosc_nowa);

};

