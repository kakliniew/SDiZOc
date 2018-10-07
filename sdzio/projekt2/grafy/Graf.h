#pragma once
#include "DrzewoSpinajace.h"
#include "ElementListy.h"
#include "Krawedz.h"
class Graf
{	
	bool *odwiedzone;
	int wierzcholki, krawedzie, gestosc, krawedzieOdwrotne;
	ElementListy *pomocniczy1, *pomocniczy2;
public:
	__int64 timer;
	Krawedz * K, *KO;
	int ** macierzIncydencji, ** grafNieskierowanyM;
	ElementListy ** listySasiedztwa, ** grafNieskierowanyL;
	long long * dojscia;                    
	int * poprzednicy;

	void startTimer();
	void endTimer();
	Graf(int wierzcholki, int krawedzie);
	~Graf();
	void grafNieskierowany();
	void losujKrawedzie();
	void losowyGraf();
	int getWierzcholki();
	int getKrawedzie();
	bool spojny();
	void DijkstraLista(int wierzcholek);
	void DijkstraMacierz(int wierzcholek);
	void primLista();
	void primMacierz();
	void kruskalMacierz();
	void kruskalLista();
	void fordLista(int v);
	void dikstral(int v);
	void wyswietl();
};

