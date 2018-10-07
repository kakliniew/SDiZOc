
#include "DrzewoSpinajace.h"
#include "ElementListy.h"
#include "Krawedz.h"
#include <cstdlib>
#include<iostream>
using namespace std;

DrzewoSpinajace::DrzewoSpinajace(int wierzcholki, int krawedzi)
{
	drzewo = new ElementListy *[wierzcholki];
	for (int i = 0; i < wierzcholki; i++)
	{
		drzewo[i] = NULL;
	}
	rozmiar = wierzcholki - 1;
	waga = 0;
	krawedzie = krawedzi;
	krawedz = new Krawedz[krawedzie];
	liczbaKrawedzi = 0;
}


DrzewoSpinajace::~DrzewoSpinajace()
{
	ElementListy *pomocniczy1, *pomocniczy2;
	for (int i = 0; i <= rozmiar; i++)
	{
		pomocniczy1 = drzewo[i];
		while (pomocniczy1)
		{
			pomocniczy2 = pomocniczy1;
			pomocniczy1 = pomocniczy1->nastepny;
			delete pomocniczy2;
		}
	}

	delete[]drzewo;
}

void DrzewoSpinajace::dodajKrawedz(Krawedz nowa)
{
	ElementListy *pomocniczy;

	waga += nowa.waga;
	pomocniczy = new ElementListy;
	pomocniczy->wierzcholek = nowa.wkoncowy;
	pomocniczy->waga = nowa.waga;
	pomocniczy->nastepny = drzewo[nowa.wpoczatkowy];
	drzewo[nowa.wpoczatkowy] = pomocniczy;

	pomocniczy = new ElementListy;
	pomocniczy->wierzcholek = nowa.wpoczatkowy;
	pomocniczy->waga = nowa.waga;
	pomocniczy->nastepny = drzewo[nowa.wkoncowy];
	drzewo[nowa.wkoncowy] = pomocniczy;

	krawedz[liczbaKrawedzi] = nowa;
	liczbaKrawedzi++;
}

void DrzewoSpinajace::wyswietl()
{
	cout << endl;
	for (int i = 0; i < liczbaKrawedzi; i++)
	{

		cout <<  i + 1 << ": ";

		cout << krawedz[i].wpoczatkowy << "<->" << krawedz[i].wkoncowy << " [" << krawedz[i].waga << "] ";

		cout << endl;
	}
	cout << endl << endl << "Waga minimalnego drzewa rozpinajacego = " << waga << endl << endl;
}
