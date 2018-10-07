#include "stdafx.h"
#include "ZbioryZlaczone.h"
#include "Krawedz.h"



ZbioryZlaczone::ZbioryZlaczone(int n)
{
	Z = new DSNode[n];             // Tworzymy tablicê dla elementów zbiorów
};

ZbioryZlaczone::~ZbioryZlaczone()
{
	delete[] Z;                    // Usuwamy tablicê ze zbiorami
};

void ZbioryZlaczone::MakeSet(int v)
{
	Z[v].up = v;
	Z[v].rank = 0;
}

int ZbioryZlaczone::FindSet(int v)
{
	if (Z[v].up != v) Z[v].up = FindSet(Z[v].up);
	return Z[v].up;
}

void ZbioryZlaczone::UnionSets(Krawedz e)
{
	int ru, rv;

	ru = FindSet(e.wpoczatkowy);             // Wyznaczamy korzeñ drzewa z wêz³em u
	rv = FindSet(e.wkoncowy);             // Wyznaczamy korzeñ drzewa z wêz³em v
	if (ru != rv)                    // Korzenie musz¹ byæ ró¿ne
	{
		if (Z[ru].rank > Z[rv].rank)   // Porównujemy rangi drzew
			Z[rv].up = ru;              // ru wiêksze, do³¹czamy rv
		else
		{
			Z[ru].up = rv;              // równe lub rv wiêksze, do³¹czamy ru
			if (Z[ru].rank == Z[rv].rank) Z[rv].rank++;
		}
	}
}
