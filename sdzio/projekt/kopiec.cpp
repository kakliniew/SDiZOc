#include "kopiec.h"
#include <math.h>
using namespace std;

Kopiec::Kopiec()
{
    wskaznikKorzenia=0;
    rozmiar=0;

};



void Kopiec::dodaj_element(int wartosc)
{
    int *nowywskaznikKorzenia = new int[rozmiar+1];
    nowywskaznikKorzenia[rozmiar]=wartosc;
    for(int i=0;i<rozmiar;i++)
    nowywskaznikKorzenia[i]=wskaznikKorzenia[i];

    delete [] wskaznikKorzenia;
    wskaznikKorzenia = nowywskaznikKorzenia;
    rozmiar++;

    if(rozmiar>1)
    {
        int wysokosc=0;

        int pomoc2=rozmiar-1;
        wysokosc=floor(log_dwa(rozmiar));

        for(int i=wysokosc;i>0;i--)
        {
            int pomoc=0;
            if(wskaznikKorzenia[pomoc2]>wskaznikKorzenia[(pomoc2-1)/2])
            {
                pomoc=wskaznikKorzenia[pomoc2];
                wskaznikKorzenia[pomoc2]=wskaznikKorzenia[(pomoc2-1)/2];
                wskaznikKorzenia[(pomoc2-1)/2]=pomoc;
                pomoc2=(pomoc2-1)/2;
            }
            else break;

        }
    }
};

    void Kopiec::usun_element(int wartosc)
    {
        if(wyszukaj(wartosc))  //jesli istnieje to znajdz miejsce i usun z tego miejsca
        {
            int miejsce=0;
            for(int i=0;i<rozmiar;i++)
             {
                if(wskaznikKorzenia[i]==wartosc)
                {
                    miejsce=i;

                }
             }


             int *nowywskaznikKorzenia = new int[rozmiar-1];
            nowywskaznikKorzenia[miejsce]=wskaznikKorzenia[rozmiar-1];
            for(int i=0;i<miejsce;i++)
            nowywskaznikKorzenia[i]=wskaznikKorzenia[i];

            for(int i=miejsce+1;i<rozmiar-1;i++)
            nowywskaznikKorzenia[i]=wskaznikKorzenia[i];

            delete [] wskaznikKorzenia;
            wskaznikKorzenia = nowywskaznikKorzenia;
            rozmiar--;
            cout<<"pomyslnie usunieto"<<endl;
            int pomoc=0;

            bool naprawiono=false;
            while(naprawiono!=true)
            {

                if(wskaznikKorzenia[miejsce*2+1]>wskaznikKorzenia[miejsce] && (miejsce*2+1)<rozmiar)
                {  pomoc= wskaznikKorzenia[miejsce*2+1];
                wskaznikKorzenia[miejsce*2+1]=wskaznikKorzenia[miejsce];
                wskaznikKorzenia[miejsce]=pomoc;
                    miejsce=miejsce*2+1;
                }
                else naprawiono=true;
            }
        }
        else cout<<"nie udalo sie usunac"<<endl;

    };


void Kopiec::wyswietl()
{ int wysokosc=0;
    int licznik=0;
    bool koniec_wyswietlania=false;
    if(wskaznikKorzenia!=0)
    {
        wysokosc=floor(log_dwa(rozmiar));
        cout<<"Elementy kopca: "<<endl;
        int element=0;
        for(int i=0;i<=wysokosc;i++)  //kazdy wiersz
        {   int szerokosc=2;
                for(int l=0;l<wysokosc;l++)
                {
                    szerokosc=szerokosc*2;

                }
                int ele_wiersz=1; //ilosc elementow w wierszu
                for(int k=0;k<i;k++)
                {
                    ele_wiersz=ele_wiersz*2;        //liczenie faktycznej ilsoci elementow w wierszu
                }
                for(int k=0;k<ele_wiersz;k++)       //wyswietlanie w wierszu elementow
                {
                     for(int j=0;j<((szerokosc/(ele_wiersz)))/2;j++)
                        {
                            cout<<" ";
                        }



                    if(koniec_wyswietlania==false)
                     cout<<wskaznikKorzenia[element];

                         for(int j=0;j<(szerokosc/(ele_wiersz))-1;j++)
                        {
                            cout<<" ";
                        }

                    if(licznik==rozmiar-1)koniec_wyswietlania=true;
                        element++;
                        licznik++;
                }
                cout<<endl<<endl<<endl;





        }


    }
    else cout<<"kopiec jest pusty"<<endl;
};

double Kopiec::log_dwa(int liczba)
{
    return log(liczba)/log(2);

};

bool Kopiec::wyszukaj(int wartosc)
{
    bool istnieje=false;
     for(int i=0;i<rozmiar;i++)
     {

        if(wskaznikKorzenia[i]==wartosc) istnieje=true;
     }
        return istnieje;

};


void Kopiec::przywroc_kopiec(){};
