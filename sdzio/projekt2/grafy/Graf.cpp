#include "stdafx.h"
#include "Graf.h"
#include "Krawedz.h"
#include "ZbioryZlaczone.h"
#include "ElementListy.h"
#include "DrzewoSpinajace.h"
#include "Stos.h"
#include <windows.h>
#include <algorithm>
#include<iostream>
#include <cstdlib>
#include <iomanip>
#include <queue>
#include <fstream>
#include <stdint.h>
 #include <limits>
using namespace std;
void Graf::startTimer()
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	timer = start.QuadPart;
}

void Graf::endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	timer = stop.QuadPart - timer;
	cout << "Wykonanie tej funkcji zajelo: " << timer<< " taktow procesora" << endl;
}

Graf::Graf(int wierzcholki, int krawedzie)
{
	this->krawedzie = krawedzie;
	this->wierzcholki = wierzcholki;
	macierzIncydencji = new int *[wierzcholki];
	grafNieskierowanyM = new int *[wierzcholki];
	listySasiedztwa = new ElementListy *[wierzcholki];
	grafNieskierowanyL = new ElementListy *[wierzcholki];
	K = new Krawedz[krawedzie];
	KO = new Krawedz[krawedzie];
	krawedzieOdwrotne = 0;
}

/*!!!!!!!!!!*/
Graf::~Graf()
{

	for (int i = 0; i < wierzcholki; i++)
	{
		pomocniczy1 = listySasiedztwa[i];
		while (pomocniczy1)
		{
			pomocniczy2 = pomocniczy1;
			pomocniczy1 = pomocniczy1->nastepny;
			delete pomocniczy2;
		}
	}
	delete[] listySasiedztwa;


	for (int i = 0; i < wierzcholki; i++) delete[] macierzIncydencji[i];
	delete[] macierzIncydencji;
}

void Graf::grafNieskierowany()
{
	int i, j;
	for (i = 0; i < wierzcholki; i++)
		grafNieskierowanyM[i] = new int[krawedzie];
	for (i = 0; i < wierzcholki; i++)
		for (j = 0; j < krawedzie; j++)
		{
			grafNieskierowanyM[i][j] = 0;
		}

	for (i = 0; i < wierzcholki; i++)
		grafNieskierowanyL[i] = NULL;

	for (i = 0; i < krawedzie; i++)
	{
		j = 0;
		while (j < krawedzieOdwrotne)
		{

			if (KO[j].wpoczatkowy == K[i].wpoczatkowy && KO[j].wkoncowy == K[i].wkoncowy)
			{
				break;
			}
			else j++;
		}
		if (j == krawedzieOdwrotne)
		{
			KO[krawedzieOdwrotne].wpoczatkowy = K[i].wkoncowy;
			KO[krawedzieOdwrotne].wkoncowy = K[i].wpoczatkowy;
			KO[krawedzieOdwrotne].waga = K[i].waga;
			krawedzieOdwrotne++;
		}
	}

	int wpoczatkowy, wkoncowy, waga;
	for (int i = 0; i < krawedzieOdwrotne; i++)
	{
		wpoczatkowy = KO[i].wpoczatkowy;
		wkoncowy = KO[i].wkoncowy;
		waga = KO[i].waga;
		pomocniczy1 = new ElementListy;
		pomocniczy1->wierzcholek = wkoncowy;
		pomocniczy1->waga = waga;
		pomocniczy1->nastepny = grafNieskierowanyL[wpoczatkowy];
		grafNieskierowanyL[wpoczatkowy] = pomocniczy1;
		pomocniczy2 = new ElementListy;
		wpoczatkowy = KO[i].wkoncowy;
		wkoncowy = KO[i].wpoczatkowy;
		waga = KO[i].waga;
		pomocniczy2->wierzcholek = wkoncowy;
		pomocniczy2->waga = waga;
		pomocniczy2->nastepny = grafNieskierowanyL[wpoczatkowy];
		grafNieskierowanyL[wpoczatkowy] = pomocniczy2;

		grafNieskierowanyM[KO[i].wpoczatkowy][i] = 1;
		grafNieskierowanyM[KO[i].wkoncowy][i] = 1;
	}
}

	void Graf::losujKrawedzie()
	{
		int c = 0;
		int * T;
		int b, doDodania1, doDodania2, a, i, j;
		int liczStopien = 0;
		int * wDrzewie;
		int * nieWDrzewie;
		a = wierzcholki;
		nieWDrzewie = new int[a];
		for (i = 0; i < a; i++)
		{
			nieWDrzewie[i] = i;
		}
		wDrzewie = new int[a];
		b = rand() % a;
		doDodania1 = nieWDrzewie[b];
		nieWDrzewie[b] = nieWDrzewie[a - 1];
		a--;
		wDrzewie[c] = doDodania1;
		c++;

		for (i = 0; i < (wierzcholki - 1); i++)
		{
			b = rand() % c;
			doDodania1 = wDrzewie[b];

			b = rand() % a;
			doDodania2 = nieWDrzewie[b];
			nieWDrzewie[b] = nieWDrzewie[a - 1];
			a--;
			wDrzewie[c] = doDodania2;
			c++;
			K[i].wpoczatkowy = doDodania1;
			K[i].wkoncowy = doDodania2;
		}
		for (i = 0; i < (wierzcholki - 1); i++)
		{

			b = rand() % wierzcholki;
			swap(K[b].wkoncowy, K[b].wpoczatkowy);

		}

		for (i = wierzcholki - 1; i < krawedzie; i++)
		{
			a = wierzcholki;
			T = new int[a];
			for (int k = 0; k < a; k++)
			{
				T[k] = k;
			}

			b = rand() % a;
			doDodania1 = T[b];
			T[b] = T[a - 1];
			a--;
			while (true)
			{

				liczStopien = 0;
				for (j = 0; j < i; j++)
				{
					if (K[j].wpoczatkowy == doDodania1)
						liczStopien++;
					if (liczStopien == wierzcholki - 1) break;
				}

				if (liczStopien == wierzcholki - 1)
				{
					b = rand() % a;
					doDodania1 = T[b];
					T[b] = T[a - 1];
					a--;
				}

				else break;
			}

			a = wierzcholki;
			for (int k = 0; k < a; k++)
			{
				T[k] = k;
			}

			T[doDodania1] = T[a - 1];
			a--;

			b = rand() % a;
			doDodania2 = T[b];
			T[b] = T[a - 1];
			a--;

			for (j = 0; j < i; j++)
			{
				while (doDodania1 == K[j].wpoczatkowy && doDodania2 == K[j].wkoncowy)
				{
					b = rand() % a;
					doDodania2 = T[b];
					T[b] = T[a - 1];
					a--;
					j = 0;
				}
			}
			K[i].wpoczatkowy = doDodania1;
			K[i].wkoncowy = doDodania2;
			delete[]T;
		}

		for (i = 0; i < krawedzie; i++)
			K[i].waga = (rand() % 9) + 1;

		delete[] nieWDrzewie;
		delete[] wDrzewie;
	}

	void Graf::losowyGraf()
	{
		int i, j;
		for (i = 0; i < wierzcholki; i++)
			macierzIncydencji[i] = new int[krawedzie];
		for (i = 0; i < wierzcholki; i++)
			for (j = 0; j < krawedzie; j++)
			{
				macierzIncydencji[i][j] = 0;
			}

		for (i = 0; i < wierzcholki; i++)
			listySasiedztwa[i] = NULL;

		losujKrawedzie();
		grafNieskierowany();
		for (i = 0; i < krawedzie; i++)
		{
			int wp = K[i].wpoczatkowy;
			int wk = K[i].wkoncowy;
			int waga = K[i].waga;
			pomocniczy1 = new ElementListy;
			pomocniczy1->wierzcholek = wk;
			pomocniczy1->waga = waga;
			pomocniczy1->nastepny = listySasiedztwa[wp];
			listySasiedztwa[wp] = pomocniczy1;

			macierzIncydencji[wp][i] = 1;
			macierzIncydencji[wk][i] = -1;
		}

	}

	int Graf::getWierzcholki()
	{
		return wierzcholki;
	}

	int Graf::getKrawedzie()
	{
		return krawedzie;
	}

	/*Zmiana !!!!!!! odwiedzone*/
	bool Graf::spojny()
	{
		Stos stos;
		int w, u, i;
		int licz = 0;

		odwiedzone = new bool[wierzcholki];
		for (i = 0; i < wierzcholki; i++)
		{
			odwiedzone[i] = false;
		}

		stos.dodaj(0);
		odwiedzone[0] = true;

		while (!stos.pusty())
		{
			w = stos.top();
			stos.usun();
			licz++;
			for (pomocniczy1 = grafNieskierowanyL[w]; pomocniczy1; pomocniczy1 = pomocniczy1->nastepny)
			{
				u = pomocniczy1->wierzcholek;
				if (!odwiedzone[u])
				{
					odwiedzone[u] = true;
					stos.dodaj(u);
				}
			}
		}
		delete[]odwiedzone;
		if (licz == wierzcholki)
			return true;

		else return false;
	}

	void Graf::DijkstraLista(int wierzcholek)
	{
		int korzen, wezel, rozmiarKopca, ojciec, lewySyn, prawySyn, kosztMin, synMin, syn, *koszta, *poprzednicy, *kopiec, *pozycjaKopiec;
		Stos stos;
		int szerokosc, i, j;
		koszta = new int[wierzcholki];
		poprzednicy = new int[wierzcholki];
		odwiedzone = new bool[wierzcholki];
		kopiec = new int[wierzcholki];
		pozycjaKopiec = new int[wierzcholki];

		for (i = 0; i < wierzcholki; i++)
		{
			koszta[i] = INT_MAX;
			poprzednicy[i] = -1;
			odwiedzone[i] = false;
			kopiec[i] = pozycjaKopiec[i] = i;
		}
		startTimer();
		rozmiarKopca = wierzcholki;

		koszta[wierzcholek] = 0;
		wezel = kopiec[0];
		kopiec[0] = kopiec[wierzcholek];
		kopiec[wierzcholek] = wezel;
		pozycjaKopiec[wierzcholek] = 0;
		pozycjaKopiec[0] = wierzcholek;

		for (i = 0; i < wierzcholki; i++)
		{
			korzen = kopiec[0];

			kopiec[0] = kopiec[--rozmiarKopca];
			pozycjaKopiec[kopiec[0]] = ojciec = 0;
			while (true)
			{
				lewySyn = ojciec + ojciec + 1;
				prawySyn = lewySyn + 1;
				if (lewySyn >= rozmiarKopca) break;
				kosztMin = koszta[kopiec[lewySyn]];
				synMin = lewySyn;
				if ((prawySyn < rozmiarKopca) && (kosztMin > koszta[kopiec[prawySyn]]))
				{
					kosztMin = koszta[kopiec[prawySyn]];
					synMin = prawySyn;
				}
				if (koszta[kopiec[ojciec]] <= kosztMin)
					break;
				wezel = kopiec[ojciec];
				kopiec[ojciec] = kopiec[synMin];
				kopiec[synMin] = wezel;
				pozycjaKopiec[kopiec[ojciec]] = ojciec;
				pozycjaKopiec[kopiec[synMin]] = synMin;
				ojciec = synMin;
			}

			odwiedzone[korzen] = true;

			if (listySasiedztwa[korzen] != NULL)
				for (pomocniczy1 = listySasiedztwa[korzen]; pomocniczy1; pomocniczy1 = pomocniczy1->nastepny)
					if (!odwiedzone[pomocniczy1->wierzcholek] && (koszta[pomocniczy1->wierzcholek] > koszta[korzen] + pomocniczy1->waga))
					{
						koszta[pomocniczy1->wierzcholek] = koszta[korzen] + pomocniczy1->waga;
						poprzednicy[pomocniczy1->wierzcholek] = korzen;

						for (syn = pozycjaKopiec[pomocniczy1->wierzcholek]; syn; syn = ojciec)
						{
							ojciec = syn / 2;
							if (koszta[kopiec[ojciec]] <= koszta[kopiec[syn]])
								break;
							wezel = kopiec[ojciec];
							kopiec[ojciec] = kopiec[syn];
							kopiec[syn] = wezel;
							pozycjaKopiec[kopiec[ojciec]] = ojciec;
							pozycjaKopiec[kopiec[syn]] = syn;
						}
					}
		}
		endTimer();
		cout << endl;

		cout << "Najkrotsza droga z wierzcholka nr " << wierzcholek << " do wierzcholka nr: " << endl;
		for (i = 0; i < wierzcholki; i++)
		{
			szerokosc = -2;

			cout << i << ": ";


			if (koszta[i] == INT_MAX || koszta[i]<0)
				cout << "Brak sciezki" << endl;
			else

			{
				for (j = i; j > -1; j = poprzednicy[j])
				{
					stos.dodaj(j);
					szerokosc = szerokosc + 2;
				}

				while (!stos.pusty())
				{
					cout << stos.top() << " ";
					stos.usun();
				}
				for (j = 0; j < wierzcholki - szerokosc; j++)
					cout << " ";
				cout << setw(5) << "(" << koszta[i] << ")" << endl;
			}
		}
		cout << endl << endl;
	}

	void Graf::DijkstraMacierz(int wierzcholek)
	{
		int korzen, wezel, rozmiarKopca, ojciec, lewySyn, prawySyn, kosztMin, synMin, syn, *koszta, *poprzednicy, *kopiec, *pozycjaKopiec;
		Stos stos;
		int szerokosc, i, j, l;
		koszta = new int[wierzcholki];
		poprzednicy = new int[wierzcholki];
		odwiedzone = new bool[wierzcholki];
		kopiec = new int[wierzcholki];
		pozycjaKopiec = new int[wierzcholki];

		for (i = 0; i < wierzcholki; i++)
		{
			koszta[i] = INT_MAX;
			poprzednicy[i] = -1;
			odwiedzone[i] = false;
			kopiec[i] = pozycjaKopiec[i] = i;
		}


		startTimer();
		rozmiarKopca = wierzcholki;

		koszta[wierzcholek] = 0;
		wezel = kopiec[0];
		kopiec[0] = kopiec[wierzcholek];
		kopiec[wierzcholek] = wezel;
		pozycjaKopiec[wierzcholek] = 0;
		pozycjaKopiec[0] = wierzcholek;

		for (i = 0; i < wierzcholki; i++)
		{
			korzen = kopiec[0];

			kopiec[0] = kopiec[--rozmiarKopca];
			pozycjaKopiec[kopiec[0]] = ojciec = 0;
			while (true)
			{
				lewySyn = ojciec + ojciec + 1;
				prawySyn = lewySyn + 1;
				if (lewySyn >= rozmiarKopca) break;
				kosztMin = koszta[kopiec[lewySyn]];
				synMin = lewySyn;
				if ((prawySyn < rozmiarKopca) && (kosztMin > koszta[kopiec[prawySyn]]))
				{
					kosztMin = koszta[kopiec[prawySyn]];
					synMin = prawySyn;
				}
				if (koszta[kopiec[ojciec]] <= kosztMin)
					break;
				wezel = kopiec[ojciec];
				kopiec[ojciec] = kopiec[synMin];
				kopiec[synMin] = wezel;
				pozycjaKopiec[kopiec[ojciec]] = ojciec;
				pozycjaKopiec[kopiec[synMin]] = synMin;
				ojciec = synMin;
			}

			odwiedzone[korzen] = true;

			for (l = 0; l < krawedzie; l++)
			{
				if (macierzIncydencji[korzen][l] != 0)
					for (j = 0; j < wierzcholki; j++)
						if (j != korzen && macierzIncydencji[j][l] == -1 && !odwiedzone[j] && (koszta[j] > koszta[korzen] + K[l].waga))
						{
							koszta[j] = koszta[korzen] + K[l].waga;
							poprzednicy[j] = korzen;

							for (syn = pozycjaKopiec[j]; syn; syn = ojciec)
							{
								ojciec = syn / 2;
								if (koszta[kopiec[ojciec]] <= koszta[kopiec[syn]])
									break;
								wezel = kopiec[ojciec];
								kopiec[ojciec] = kopiec[syn];
								kopiec[syn] = wezel;
								pozycjaKopiec[kopiec[ojciec]] = ojciec;
								pozycjaKopiec[kopiec[syn]] = syn;
							}
						}
			}
		}
		endTimer();
		cout << endl;

		cout << "Najkrotsza droga z wierzcholka nr " << wierzcholek << " do wierzcholka nr: " << endl;
		for (i = 0; i < wierzcholki; i++)
		{
			szerokosc = -2;

			cout << i << ": ";


			if (koszta[i] == INT_MAX || koszta[i]<0)
				cout << "Brak sciezki" << endl;
			else

			{
				for (j = i; j > -1; j = poprzednicy[j])
				{
					stos.dodaj(j);
					szerokosc = szerokosc + 2;
				}

				while (!stos.pusty())
				{
					cout << stos.top() << " ";
					stos.usun();
				}
				for (j = 0; j < wierzcholki - szerokosc; j++)
					cout << " ";
				cout << setw(5) << "(" << koszta[i] << ")" << endl;
			}
		}
		cout << endl << endl;
	}

	void Graf::primLista()
	{
		int w, i;
		Krawedz k;
		priority_queue <Krawedz, vector<Krawedz>, Krawedz> kolejka;
		DrzewoSpinajace *drzewo = new DrzewoSpinajace(wierzcholki, krawedzie);
		odwiedzone = new bool[wierzcholki];
		for (i = 0; i < wierzcholki; i++)
		{
			odwiedzone[i] = false;
		}
		cout << endl << "Graf nieskierowany na podstawie ktorego zbudowano drzewo: " << endl << endl;
		for (i = 0; i < wierzcholki; i++)
		{
			cout << "[" << i << "] =";
			pomocniczy1 = grafNieskierowanyL[i];
			while (pomocniczy1)
			{
				cout << setw(3) << pomocniczy1->wierzcholek << "(" << pomocniczy1->waga << ") ";
				pomocniczy1 = pomocniczy1->nastepny;
			}
			cout << endl;
		}
		cout << endl;
		startTimer();
		w = 0;
		odwiedzone[w] = true;

		for (i = 1; i < wierzcholki; i++)
		{

			for (pomocniczy1 = grafNieskierowanyL[w]; pomocniczy1; pomocniczy1 = pomocniczy1->nastepny)
			{
				if (!odwiedzone[pomocniczy1->wierzcholek])
				{
					k.wpoczatkowy = w;
					k.wkoncowy = pomocniczy1->wierzcholek;
					k.waga = pomocniczy1->waga;
					kolejka.push(k);
				}
			}
			do
			{
				k = kolejka.top();
				kolejka.pop();

			} while (odwiedzone[k.wkoncowy]);

			drzewo->dodajKrawedz(k);
			odwiedzone[k.wkoncowy] = true;
			w = k.wkoncowy;

		}

		endTimer();
		cout << endl;
		cout << "Minimalne drzewo rozpinajace:";
		drzewo->wyswietl();
		delete drzewo;
	}


	void Graf::primMacierz()
	{

		int w, i, j, g;
		Krawedz krawedz;
		priority_queue <Krawedz, vector<Krawedz>, Krawedz> kolejka;
		DrzewoSpinajace *drzewo = new DrzewoSpinajace(wierzcholki, krawedzie);
		odwiedzone = new bool[wierzcholki];
		for (i = 0; i < wierzcholki; i++)
		{
			odwiedzone[i] = false;
		}

		cout << "Graf nieskierowany na podstawie ktorego budowano drzewo: " << endl << endl;
		cout << setw(3) << "  K";
		for (i = 0; i < krawedzieOdwrotne; i++)
		{
			cout << setw(3) << i;

		}
		cout << endl;
		cout << setw(3) << "W" << endl;
		for (i = 0; i < wierzcholki; i++)
		{
			cout << setw(3) << i;
			for (int j = 0; j < krawedzieOdwrotne; j++)
				cout << setw(3) << grafNieskierowanyM[i][j];
			cout << endl;
		}
		cout << endl;
		cout << "   ";
		for (i = 0; i < krawedzieOdwrotne; i++)
		{
			cout << setw(3) << KO[i].waga;
		}
		cout << " " << "<- wagi";
		cout << endl << endl;


		w = 0;
		odwiedzone[w] = true;
		startTimer();
		for (i = 1; i < wierzcholki; i++)
		{
			for (g = 0; g < krawedzieOdwrotne; g++)
			{

				if (grafNieskierowanyM[w][g] != 0)
					for (j = 0; j < wierzcholki; j++)
						if (j != w && grafNieskierowanyM[j][g] != 0 && !odwiedzone[j])
						{
							krawedz.wpoczatkowy = w;
							krawedz.wkoncowy = j;
							krawedz.waga = KO[g].waga;
							kolejka.push(krawedz);

						}
			}
			do
			{
				krawedz = kolejka.top();
				kolejka.pop();

			} while (odwiedzone[krawedz.wkoncowy]);

			drzewo->dodajKrawedz(krawedz);
			odwiedzone[krawedz.wkoncowy] = true;
			w = krawedz.wkoncowy;

		}
		endTimer();
		cout << endl << endl;
		cout << "Minimalne drzewo rozpinajace:";
		drzewo->wyswietl();
		delete drzewo;
	}


	void Graf::wyswietl()
	{
		int i;
		cout << "Macierz incydencji:" << endl;
		cout << setw(3)<<"  K";
		for (i = 0; i < krawedzie; i++)
		{
			cout << setw(3) << i;

		}
		cout << endl;
		cout << setw(3)<<"W" << endl;
		for (i = 0; i < wierzcholki; i++)
		{
			cout << setw(3) << i;
			for (int j = 0; j < krawedzie; j++)
				cout << setw(3) << macierzIncydencji[i][j];
			cout << endl;
		}
		cout << endl;
		cout << "   ";
		for (i = 0; i < krawedzie; i++)
		{
			cout << setw(3) << K[i].waga;
		}

		cout << " " << "<- wagi";
		cout << endl << endl << endl;
		cout << "Lista sasiedztwa:" << endl;
		for (i = 0; i < wierzcholki; i++)
		{
			cout << "[" << i << "] =";
			pomocniczy1 = listySasiedztwa[i];
			while (pomocniczy1)
			{
				cout << setw(3) << pomocniczy1->wierzcholek << "(" << pomocniczy1->waga << ") ";
				pomocniczy1 = pomocniczy1->nastepny;
			}
			cout << endl;
		}
		cout << endl;
	}

	void Graf::kruskalMacierz()
	{
		int i,g,j;
		Krawedz krawedz;
		priority_queue <Krawedz, vector<Krawedz>, Krawedz> kolejka;
		DrzewoSpinajace *drzewo = new DrzewoSpinajace(wierzcholki, krawedzie);


		cout << "Graf nieskierowany na podstawie ktorego budowano drzewo: " << endl << endl;
		cout << setw(3) << "  K";
		for (i = 0; i < krawedzieOdwrotne; i++)
		{
			cout << setw(3) << i;

		}
		cout << endl;
		cout << setw(3) << "W" << endl;
		for (i = 0; i < wierzcholki; i++)
		{
			cout << setw(3) << i;
			for (int j = 0; j < krawedzieOdwrotne; j++)
				cout << setw(3) << grafNieskierowanyM[i][j];
			cout << endl;
		}
		cout << endl;
		cout << "   ";
		for (i = 0; i < krawedzieOdwrotne; i++)
		{
			cout << setw(3) << KO[i].waga;
		}
		cout << " " << "<- wagi";
		cout << endl;


		ZbioryZlaczone Z(wierzcholki);

		for (i = 0; i < wierzcholki; i++)
			Z.MakeSet(i);

		for (i = 0; i < wierzcholki; i++)
		{
			for (g = 0; g < krawedzieOdwrotne; g++)
			{

				if (grafNieskierowanyM[i][g] == 1)
					for (j = 0; j < wierzcholki; j++)
						if (grafNieskierowanyM[j][g] == 1)
						{
							krawedz.wpoczatkowy = i;
							krawedz.wkoncowy = j;
							krawedz.waga = K[g].waga;
							kolejka.push(krawedz);
						}
			}
		}
		startTimer();
		for (i = 1; i < wierzcholki; i++)          // Pêtla wykonuje siê n - 1 razy !!!
		{
			do
			{
				krawedz = kolejka.top();

				kolejka.pop();
			} while (Z.FindSet(krawedz.wpoczatkowy) == Z.FindSet(krawedz.wkoncowy));
			drzewo->dodajKrawedz(krawedz);                // Dodajemy krawêdŸ do drzewa
			Z.UnionSets(krawedz);
		}
		endTimer();
		cout << endl;
		cout << "Minimalne drzewo rozpinajace:";
		drzewo->wyswietl();
		delete drzewo;
	}

	void Graf::kruskalLista()
	{
		int i;
		Krawedz krawedz;
		priority_queue <Krawedz, vector<Krawedz>, Krawedz> kolejka;
		DrzewoSpinajace *drzewo = new DrzewoSpinajace(wierzcholki, krawedzie);

		cout << endl << "Graf nieskierowany na podstawie ktorego zbudowano drzewo: " << endl << endl;
		for (i = 0; i < wierzcholki; i++)
		{
			cout << "[" << i << "] =";
			pomocniczy1 = grafNieskierowanyL[i];
			while (pomocniczy1)
			{
				cout << setw(3) << pomocniczy1->wierzcholek << "(" << pomocniczy1->waga << ") ";
				pomocniczy1 = pomocniczy1->nastepny;
			}
			cout << endl;
		}
		cout << endl;



		for (i = 1; i < wierzcholki; i++)
		{

			for (pomocniczy1 = grafNieskierowanyL[i]; pomocniczy1; pomocniczy1 = pomocniczy1->nastepny)
			{
				krawedz.wpoczatkowy = i;
				krawedz.wkoncowy = pomocniczy1->wierzcholek;
				krawedz.waga = pomocniczy1->waga;
				kolejka.push(krawedz);
			}
		}



			ZbioryZlaczone Z(wierzcholki);

			for (i = 0; i < wierzcholki; i++)
				Z.MakeSet(i);


			startTimer();
			for (i = 1; i < wierzcholki; i++)          // Pêtla wykonuje siê n - 1 razy !!!
			{
				do
				{
					krawedz = kolejka.top();
					kolejka.pop();
				} while (Z.FindSet(krawedz.wpoczatkowy) == Z.FindSet(krawedz.wkoncowy));
				drzewo->dodajKrawedz(krawedz);                // Dodajemy krawêdŸ do drzewa
				Z.UnionSets(krawedz);
		}

		endTimer();
		cout << endl;
		cout << "Minimalne drzewo rozpinajace:";
		drzewo->wyswietl();
		delete drzewo;
	}

	void Graf::fordLista(int v)
	{
		int i,x,sptr,szerokosc,*S;
		dojscia = new long long[wierzcholki];
		poprzednicy = new int[wierzcholki];
		S = new int[wierzcholki];              // Tworzymy prosty stos
		sptr = 0;

		for (i = 0; i < wierzcholki; i++)          // Inicjujemy struktury danych
		{
			dojscia[i] = INT_MAX;
			poprzednicy[i] = -1;
		}


		bool test;
		bool test2 = true;

		startTimer();
		dojscia[v] = 0;                       // Zerujemy koszt dojœcia do v
		for (i = 1; i < wierzcholki; i++)          // Pêtla relaksacji
		{
			test = true;                  // Oznacza, ¿e algorytm nie wprowadzi³ zmian do d i p
			for (x = 0; x < wierzcholki; x++)        // Przechodzimy przez kolejne wierzcho³ki grafu
				for (pomocniczy1 = listySasiedztwa[x]; pomocniczy1; pomocniczy1 = pomocniczy1->nastepny) // Przegl¹damy listê s¹siadów wierzcho³ka x
					if (dojscia[pomocniczy1->wierzcholek] > dojscia[x] + pomocniczy1->waga) // Sprawdzamy warunek relaksacji
					{
						test = false;           // Jest zmiana w d i p
						dojscia[pomocniczy1->wierzcholek] = dojscia[x] + pomocniczy1->waga; // Relaksujemy krawêdŸ z x do jego s¹siada
						poprzednicy[pomocniczy1->wierzcholek] = x;           // Poprzednikiem s¹siada bêdzie x
					}
			if (test) test2=true;         // Jeœli nie by³o zmian, to koñczymy
		}

		// Sprawdzamy istnienie ujemnego cyklu

		for (x = 0; x < wierzcholki; x++)
			for (pomocniczy1 = listySasiedztwa[x]; pomocniczy1; pomocniczy1 = pomocniczy1->nastepny)
				if (dojscia[pomocniczy1->wierzcholek] > dojscia[x] + pomocniczy1->waga) test2=true; // ujemny cykl!!


		endTimer();
		cout << endl;
		if (test2)
		{

			cout << "Najkrotsza droga z wierzcholka nr " << v << " do wierzcholka nr: " << endl;
			for (int i = 0; i < wierzcholki; i++)
			{
				szerokosc = -2;
				cout << i << ": ";
				for (x = i; x != -1; x = poprzednicy[x])
				{// Wierzcho³ki œcie¿ki umieszczamy na stosie
					S[sptr++] = x;            // w kolejnoœci od ostatniego do pierwszego
					szerokosc = szerokosc + 2;
				}

				if (dojscia[i] != INT_MAX)
				{

					while (sptr)                 // Wierzcho³ki ze stosu drukujemy
						cout << S[--sptr] << " "; // w kolejnoœci od pierwszego do ostatniego
				}
				if (dojscia[i] != INT_MAX)
				{
					for (int j = 0; j < wierzcholki - szerokosc; j++)
						cout << " ";
					cout << setw(5) << "(" << dojscia[i] << ")" << endl;
				}
				else cout << "Brak sciezki" << endl;
			}
			                  // Usuwamy stos
		}
		else cout << "Negative Cycle found!" << endl;
		cout << endl;
		delete[] S;
		// Usuwamy struktury dynamiczne

		delete[] dojscia;
		delete[] poprzednicy;


	}

	void Graf::dikstral(int v)
	{
		int i, j,u,sptr, *d, *p, *S;
		bool *QS;                       // Zbiory Q i S




		d = new int[wierzcholki];                // Tablica kosztów dojœcia
		p = new int[wierzcholki];                // Tablica poprzedników
		QS = new bool[wierzcholki];              // Zbiory Q i S
		S = new int[wierzcholki];                // Stos
		sptr = 0;                       // WskaŸnik stosu



		for (i = 0; i < wierzcholki; i++)
		{
			d[i] = INT_MAX;
			p[i] = -1;
			QS[i] = false;

		}

		startTimer();
		d[v] = 0;                       // Koszt dojœcia v jest zerowy
		for (i = 0; i < wierzcholki; i++)
		{
			// Szukamy wierzcho³ka w Q o najmniejszym koszcie d

			for (j = 0; QS[j]; j++);
			for (u = j++; j < wierzcholki; j++)
				if (!QS[j] && (d[j] < d[u])) u = j;

			// Znaleziony wierzcho³ek przenosimy do S

			QS[u] = true;

			// Modyfikujemy odpowiednio wszystkich s¹siadów u, którzy s¹ w Q

			for (pomocniczy1 = grafNieskierowanyL[u]; pomocniczy1; pomocniczy1 = pomocniczy1->nastepny)
				if (!QS[pomocniczy1->wierzcholek] && (d[pomocniczy1->wierzcholek] > d[u] + pomocniczy1->waga))
				{
					d[pomocniczy1->wierzcholek] = d[u] + pomocniczy1->waga;
					p[pomocniczy1->wierzcholek] = u;
				}
		}
		endTimer();
		// Gotowe, wyœwietlamy wyniki

		for (i = 0; i < wierzcholki; i++)
		{
			cout << i << ": ";

			// Œcie¿kê przechodzimy od koñca ku pocz¹tkowi,
			// Zapisuj¹c na stosie kolejne wierzcho³ki

			for (j = i; j > -1; j = p[j]) S[sptr++] = j;

			// Wyœwietlamy œcie¿kê, pobieraj¹c wierzcho³ki ze stosu

			while (sptr) cout << S[--sptr] << " ";

			// Na koñcu œcie¿ki wypisujemy jej koszt

			cout << "$" << d[i] << endl;
		}

		// Usuwamy tablice dynamiczne

		delete[] d;
		delete[] p;
		delete[] QS;
		delete[] S;
	}




