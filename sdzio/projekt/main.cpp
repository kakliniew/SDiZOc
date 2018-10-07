#include <iostream>
#include "lista.h"
#include "elementlisty.h"
#include "tablica.h"
#include "kopiec.h"
#include <math.h>
#include <cstdlib>
#include <fstream>
#include <windows.h>

LARGE_INTEGER startTimer()
{
LARGE_INTEGER start;
DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
QueryPerformanceCounter(&start);
 SetThreadAffinityMask(GetCurrentThread(), oldmask);
 return start;
}
LARGE_INTEGER endTimer()
{
LARGE_INTEGER stop;
DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
QueryPerformanceCounter(&stop);
SetThreadAffinityMask(GetCurrentThread(), oldmask);
return stop;
}

using namespace std;

int main()
{bool koniec = false;
int licznik;
Kopiec *kopiecObiekt = new Kopiec;
Lista *listaObiekt = new Lista;
Tablica *tablicaObiekt = new Tablica;
LARGE_INTEGER performanceCountStart,performanceCountEnd;
int pomoc1,pomoc2;
string pomoc3,pomoc4;
int menu, lista1,tablica1,kopiec1;
bool lista, tablica,kopiec;
    do{cout<<"MENU:"<<endl;
    cout<<"1. Lista"<<endl;
    cout<<"2. Tablica"<<endl;
    cout<<"3. Kopiec"<<endl;
    cout<<"4. Wyjscie"<<endl;
    cout<<"Podaj numer"<<endl;
    cin>>menu;
    system( "cls" );
    switch(menu)
    {   case 1: {   lista=true;

                        while(lista)
                                        {
                                            cout<<"Lista:"<<endl;
                                            cout<<"1. Utworz z pliku"<<endl;
                                            cout<<"2. Dodaj element"<<endl;
                                            cout<<"3. Dodaj element zamiast innego"<<endl;
                                            cout<<"4. Usun element(pozycja)"<<endl;
                                            cout<<"5. Usun element(wartosc)"<<endl;
                                            cout<<"6. Czy istnieje(wartosc)?"<<endl;
                                            cout<<"7. Wyswietl"<<endl;
                                            cout<<"8. Wroc"<<endl;
                                            cout<<"9. Usun wszystkie pokolei"<<endl;
                                            cin>>lista1;
                                            system( "cls" );
                                            switch(lista1)
                                            {
                                            case 1: {
                                                performanceCountStart = startTimer();

                                                ifstream wczytaj("dane.txt");
                                            wczytaj>>pomoc1;
                                            licznik =0;
                                            while(pomoc1>licznik)
                                            {
                                                wczytaj>>pomoc2;
                                                listaObiekt->dodaj_koniec(pomoc2);
                                            licznik ++;
                                            }
                                                performanceCountEnd = endTimer();
                                            double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
                                            cout<<"utworzono pomyslnie"<<endl;
                                            cout << endl << "Time:" <<tm <<endl;
                                            wczytaj.close();
                                            break;
                                            }

                                            case 2: {cout<<"Podaj wartosc, ktora chcesz dodac"<<endl;
                                            cin>>pomoc1;
                                            cout<<"Podaj miejsce w ktorym chcesz dodac(indeksy od 1)"<<endl;
                                            cin>>pomoc2;
                                            if(pomoc2<=listaObiekt->rozmiar+1){
                                            performanceCountStart = startTimer();
                                            listaObiekt->dodaj_srodek(pomoc1,pomoc2);
                                            performanceCountEnd = endTimer();
                                            double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
                                            cout << endl << "Time:" <<tm <<endl;}
                                            else cout<<"zly indeks, nie dodano"<<endl;
                                            break;}
                                            case 3: {cout<<"Podaj wartosc ktora zastepujesz(jak brak dodaje normalnie)"<<endl;
                                            cin>>pomoc1;
                                            cout<<"podaj wartosc nowa"<<endl;
                                            cin>>pomoc2;
                                             performanceCountStart = startTimer();
                                            listaObiekt->dodaj_za(pomoc1,pomoc2);
                                            performanceCountEnd = endTimer();
                                            double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;

                                            cout << endl << "Time:" <<tm <<endl;
                                            break;}
                                            case 4: {cout<<"Podaj pozycje do usuniecia(indeksowane od 1)"<<endl;
                                                    cin>>pomoc1;
                                                    performanceCountStart = startTimer();
                                                    listaObiekt->usun_srodek(pomoc1);
                                                    performanceCountEnd = endTimer();
                                            double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;

                                            cout << endl << "Time:" <<tm <<endl;
                                            break;}
                                            case 5:  {cout<<"Podaj wartosc, ktora chcesz usunac"<<endl;
                                                        cin>>pomoc1;
                                                        performanceCountStart = startTimer();
                                                        listaObiekt->usun_wartosc(pomoc1);
                                                        performanceCountEnd = endTimer();
                                            double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;

                                            cout << endl << "Time:" <<tm <<endl;
                                            break;}
                                            case 6: {cout<<"Podaj wartosc, ktorej szukasz"<<endl;
                                                    cin>>pomoc1;
                                                    performanceCountStart = startTimer();
                                                    listaObiekt->wyszukaj(pomoc1);
                                                    performanceCountEnd = endTimer();
                                            double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
                                             cout << endl << "Time:" <<tm <<endl;
                                                    if(listaObiekt->wyszukaj(pomoc1)==true)cout<<"Wartosc istnieje"<<endl;
                                                    else cout<<"Brak wartosci w liscie"<<endl;break;}
                                            case 7: {listaObiekt->wyswietl();break;}
                                            case 8:  {lista= false;break; }
                                            case 9:  { for(int i=listaObiekt->rozmiar;i>0;i--)
                                                listaObiekt->usun_koniec();break; }

                                            default: cout<<"Podano bledny numer"<<endl;
                                                        break;




                                            }

                                        }
                                        break;
                }

        case 2:
                {   tablica=true;

                        while(tablica)
                                        {
                                            cout<<"Tablica:"<<endl;
                                            cout<<"1. Utworz z pliku"<<endl;
                                            cout<<"2. Dodaj element"<<endl;

                                            cout<<"3. Usun element(pozycja)"<<endl;

                                            cout<<"4. Czy istnieje(wartosc)?"<<endl;
                                            cout<<"5. Wyswietl"<<endl;
                                            cout<<"6. Wroc"<<endl;
                                            cout<<"7. Usun calosc pokolei"<<endl;
                                            cin>>tablica1;
                                            system( "cls" );
                                            switch(tablica1)
                                            {
                                            case 1: {

                                            performanceCountStart = startTimer();
                                                ifstream wczytaj("dane.txt");
                                            wczytaj>>pomoc1;
                                                licznik =0;
                                            while(pomoc1>licznik)
                                            {
                                                wczytaj>>pomoc2;
                                                tablicaObiekt->dodaj_koniec(pomoc2);
                                                licznik++;
                                            }

                                            performanceCountEnd = endTimer();
                                            double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
                                            cout<<"utworzono pomyslnie"<<endl;
                                            cout << endl << "Time:" <<tm <<endl;

                                            wczytaj.close();
                                            break;
                                            }

                                            case 2: {cout<<"Podaj wartosc, ktora chcesz dodac"<<endl;
                                            cin>>pomoc1;
                                            cout<<"Podaj miejsce w ktorym chcesz dodac(indeksy od 0)"<<endl;
                                            cin>>pomoc2;
                                            performanceCountStart = startTimer();
                                            tablicaObiekt->dodaj_srodek(pomoc1,pomoc2);
                                            performanceCountEnd = endTimer();
                                            double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;

                                            cout << endl << "Time:" <<tm <<endl;
                                            break;}

                                            case 3: {cout<<"Podaj pozycje do usuniecia(indeksowane od 0)"<<endl;
                                                    cin>>pomoc1;
                                                    performanceCountStart = startTimer();
                                                    tablicaObiekt->usun_srodek(pomoc1);
                                                    performanceCountEnd = endTimer();
                                                    double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;

                                                    cout << endl << "Time:" <<tm <<endl;
                                                    break;}

                                            case 4: {cout<<"Podaj wartosc, ktorej szukasz"<<endl;
                                                    cin>>pomoc1;
                                                    performanceCountStart = startTimer();
                                                    tablicaObiekt->wyszukaj(pomoc1);
                                                    performanceCountEnd = endTimer();
                                                    double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;

                                                    cout << endl << "Time:" <<tm <<endl;
                                                    break;}
                                            case 5: {tablicaObiekt->wyswietl();break;}
                                            case 6:  {tablica= false;break; }
                                             case 7:  { for(int j=tablicaObiekt->rozmiar-1;j>=0;j--){
                                                tablicaObiekt->usun_poczatek();

                                                }
                                                break; }
                                            default: cout<<"Podano bledny numer"<<endl;
                                                        break;




                                            }

                                        }
                                        break;
                }



        case 3:
            {   kopiec=true;

                        while(kopiec)
                                        {
                                            cout<<"Kopiec:"<<endl;
                                            cout<<"1. Utworz z pliku"<<endl;
                                            cout<<"2. Dodaj element"<<endl;

                                            cout<<"3. Usun element(wartosc)"<<endl;

                                            cout<<"4. Czy istnieje(wartosc)?"<<endl;
                                            cout<<"5. Wyswietl"<<endl;
                                            cout<<"6. Wroc"<<endl;
                                            cin>>kopiec1;
                                            system( "cls" );
                                            switch(kopiec1)
                                            {
                                            case 1: {

                                                performanceCountStart = startTimer();
                                                ifstream wczytaj("dane.txt");
                                            wczytaj>>pomoc1;
                                            licznik =0;
                                            while(pomoc1>licznik)
                                            {
                                                wczytaj>>pomoc2;
                                                kopiecObiekt->dodaj_element(pomoc2);
                                                licznik++;
                                            }



                                             performanceCountEnd = endTimer();
                                            double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
                                            cout<<"utworzono pomyslnie"<<endl;
                                            cout << endl << "Time:" <<tm <<endl;
                                            wczytaj.close();
                                            break;
                                            }

                                            case 2: {cout<<"Podaj wartosc, ktora chcesz dodac"<<endl;
                                            cin>>pomoc1;
                                                performanceCountStart = startTimer();
                                           kopiecObiekt->dodaj_element(pomoc1);
                                           performanceCountEnd = endTimer();
                                            double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;

                                            cout << endl << "Time:" <<tm <<endl;


                                           break;
                                           }


                                            case 3: {cout<<"Podaj wartosc do usuniecia)"<<endl;
                                                    cin>>pomoc1;
                                                    performanceCountStart = startTimer();
                                                    kopiecObiekt->usun_element(pomoc1);
                                                      performanceCountEnd = endTimer();
                                            double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;

                                            cout << endl << "Time:" <<tm <<endl;

                                                    break;}

                                            case 4: {cout<<"Podaj wartosc, ktorej szukasz"<<endl;
                                                    cin>>pomoc1;
                                                    performanceCountStart = startTimer();
                                                    kopiecObiekt->wyszukaj(pomoc1);
                                                      performanceCountEnd = endTimer();
                                            double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;

                                            cout << endl << "Time:" <<tm <<endl;
                                                    if(kopiecObiekt->wyszukaj(pomoc1)==true)cout<<"wartosc isnieje w kopcu"<<endl;
                                                    else cout<<"brak wartosci w kopcu"<<endl;
                                                    break;}
                                            case 5: {cout<<"poprawne wyswietlanie wymaga odpowiednio duzego okna konsoli"<<endl;
                                                kopiecObiekt->wyswietl();break;}
                                            case 6:  {kopiec= false;break; }

                                            default: cout<<"Podano bledny numer"<<endl;
                                                        break;




                                            }

                                        }
                                        break;
                }


        case 4: koniec=true; break;
        default: cout<<"Podano bledny numer"<<endl;
                    break;
    }






    }while(koniec==false);



    return 0;
}
