#include "stdafx.h"
#include "ZbioryZlaczone.h"
#include "Krawedz.h"



ZbioryZlaczone::ZbioryZlaczone(int n)
{
	Z = new DSNode[n];             // Tworzymy tablic� dla element�w zbior�w
};

ZbioryZlaczone::~ZbioryZlaczone()
{
	delete[] Z;                    // Usuwamy tablic� ze zbiorami
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

	ru = FindSet(e.wpoczatkowy);             // Wyznaczamy korze� drzewa z w�z�em u
	rv = FindSet(e.wkoncowy);             // Wyznaczamy korze� drzewa z w�z�em v
	if (ru != rv)                    // Korzenie musz� by� r�ne
	{
		if (Z[ru].rank > Z[rv].rank)   // Por�wnujemy rangi drzew
			Z[rv].up = ru;              // ru wi�ksze, do��czamy rv
		else
		{
			Z[ru].up = rv;              // r�wne lub rv wi�ksze, do��czamy ru
			if (Z[ru].rank == Z[rv].rank) Z[rv].rank++;
		}
	}
}
