#pragma once
#include "DrzewoSpinajace.h"
#include "ElementListy.h"
#include "Krawedz.h"
class DrzewoSpinajace
{
private:
	ElementListy **drzewo;
	Krawedz *krawedz;
	int rozmiar;
	int waga, krawedzie;
	int liczbaKrawedzi;
public:
	void wyswietl();
	void dodajKrawedz(Krawedz k);
	DrzewoSpinajace(int wierzcholki, int krawedzie);
	~DrzewoSpinajace();
};

