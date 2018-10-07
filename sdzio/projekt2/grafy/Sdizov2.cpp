// Sdizov2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DrzewoSpinajace.h"
#include "ElementListy.h"
#include "Krawedz.h"
#include "Graf.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <stdio.h>
#include<iostream>
#include <climits>
#include <cmath>
using namespace std;



int wybor, wierzcholki, gestosc, b;
Graf *graf;
bool naPoczatek = true;

void menu()
{
	cout << "Graf " << endl << "Liczba wierzcholkow: " << graf->getWierzcholki() << endl << "Krawedzie: " << graf->getKrawedzie() << endl << "Gestosc: " << gestosc << endl
		<< "1. Wyswietl" << endl << "2. Algorytm Dijkstra dla macierzy incydencji" << endl << "3. Algorytm Dijkstra dla listy sasiedztwa" << endl << "4. Algorytm Prima dla macierzy incydencji " << endl << "5. Algorytm Prima dla listy sasiedztwa" << endl << "6. Algorytm Kruskala dla macierzy incyndencji" << endl << "7. Algorytm Kruskala dla listy sasiedztwa " << endl << "8. Stworz nowy graf " << endl;
	cin >> wybor;
	switch (wybor)
	{
	case 1: {
		graf->wyswietl();

	}break;
	case 2: {
		while (true)
		{
			cout << "Od ktorego wierzcholka zaczac szukac najkrotszych sciezek?" << endl;
			cin >> b;
			if (b < graf->getWierzcholki()) break;
			else cout << "Niema takiego wierzcholka!" << endl;
		}
		cout << endl;

		graf->DijkstraMacierz(b);

	}break;
	case 3: {
		while (true)
		{
			cout << "Od ktorego wierzcholka zaczac szukac najkrotszych sciezek?" << endl;
			cin >> b;
			if (b < graf->getWierzcholki()) break;
			else cout << "Niema takiego wierzcholka!" << endl;
		}
		cout << endl;
		graf->DijkstraLista(b);

	}break;
	case 4: {
		graf->primMacierz();
	}break;
	case 5: {
		graf->primLista();
	}break;
	case 6: {
		graf->kruskalMacierz();
	}break;
	case 7: {
		graf->kruskalLista();
	}break;
	case 8: {
		delete graf;
		system("cls");
		naPoczatek = true;
	}break;

	}
}

int main()
{
	srand(time(NULL));
	while (naPoczatek)
	{
		cout << "Stworz graf:" << endl << "1. Zbuduj graf z pliku" << endl << "2. Stworz losowy graf" << endl;
		cin >> wybor;
		system("cls");
		switch (wybor)
		{
		case 1:
		{
			naPoczatek = false;
			ElementListy *pomocniczy1;
			string s;
			int a = 0;
			int krawedzie, wierzcholki;
			ifstream plik("Graf.txt");
			if (!plik)
			{
				cout << "Nie mozna otworzyc pliku" << endl;
				naPoczatek = true;

			}

			else
			{

				{
					plik >> krawedzie >> wierzcholki;
					if (!plik || krawedzie < wierzcholki - 1 || wierzcholki <= 1 || krawedzie >(wierzcholki*(wierzcholki - 1)))
					{
						cout << "Dane w pliku s¹ Ÿle zapisane" << endl << "Liczba wierzcholkow lub krawedzi nie jest prawidlowa." << endl;

						naPoczatek = true;
					}

					else
					{
						graf = new Graf(wierzcholki, krawedzie);
						while (!plik.eof())
						{

							plik >> graf->K[a].wpoczatkowy >> graf->K[a].wkoncowy >> graf->K[a].waga;
							if (graf->K[a].wpoczatkowy >= wierzcholki || graf->K[a].wkoncowy >= wierzcholki || graf->K[a].waga < 1)
							{
								cout << "Wyst¹pi³ b³¹d. Podano z³e krawêdzie" << endl;
								naPoczatek = true;
								break;
							}
							if (plik)
								a++;

							else
							{
								cout << "Wyst¹pi³ b³¹d. Podano z³e krawêdzie" << endl;
								naPoczatek = true;
								break;
							}
						}
						if (a == krawedzie)
						{
							for (int i = 0; i < wierzcholki; i++)
								graf->macierzIncydencji[i] = new int[krawedzie];
							for (int i = 0; i < wierzcholki; i++)
								for (int j = 0; j < krawedzie; j++)
								{
									graf->macierzIncydencji[i][j] = 0;
								}

							for (int i = 0; i < wierzcholki; i++)
								graf->listySasiedztwa[i] = NULL;

							for (int i = 0; i < krawedzie; i++)
							{
								int wpoczatkowy = graf->K[i].wpoczatkowy;
								int wkoncowy = graf->K[i].wkoncowy;
								pomocniczy1 = new ElementListy;
								pomocniczy1->wierzcholek = wkoncowy;
								pomocniczy1->waga = graf->K[i].waga;
								pomocniczy1->nastepny = graf->listySasiedztwa[wpoczatkowy];
								graf->listySasiedztwa[wpoczatkowy] = pomocniczy1;
								graf->macierzIncydencji[wpoczatkowy][i] = 1;
								graf->macierzIncydencji[wkoncowy][i] = -1;
							}
							plik.close();
							graf->grafNieskierowany();
							if (!(graf->spojny()))
							{
								cout << "Graf, zbudowany z pliku jest niespojny, " << endl << "nie mozna kontynuowac!" << endl;
								naPoczatek = true;
								delete graf;
							}
							else
								system("cls");
							while (!naPoczatek)
							{
								menu();
							}
						}
						else if (naPoczatek == false)
						{
							naPoczatek = true;
							cout << "Wyst¹pi³ b³¹d, podano za ma³o danych w porównaniu do liczby krawedzi" << endl;
						}
					}
				}
			}
		}break;
		case 2: {
			naPoczatek = false;
			while (true)
			{
				cout << "Podaj liczbe wierzcholkow:" << endl;
				cin >> wierzcholki;
				if (wierzcholki > 1) break;
				else cout << "Podano za ma³¹ liczbê wierzcho³ków!! Liczba wierzcho³ków musi byæ wiêksza od 1" << endl;
			}


			int maxK = wierzcholki*(wierzcholki - 1);
			double minG = ceil((((double)wierzcholki - 1) * 100) / (double)maxK);

			while (true)
			{

				cout << "Podaj gestosc - co najmniej " << minG << " %" << endl;
				cin >> gestosc;
				if (gestosc < minG || gestosc > 100) cout << "Podaj prawidlowa wartosc w %!"
					<< endl << "Aby graf byl spojny, gestosc musi wynosic przynajmniej " << minG << " %" << endl;
				else
					break;
			}
			double krawedzie = ceil((maxK*gestosc) / 100);
			graf = new Graf(wierzcholki, krawedzie);
			graf->losowyGraf();
			system("cls");

			while (!naPoczatek)
			{
				menu();
			}

		}break;
		}
	}
	system("pause");
	return 0;
}

