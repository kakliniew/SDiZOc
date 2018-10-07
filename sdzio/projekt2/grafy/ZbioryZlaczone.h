#pragma once
#include "Krawedz.h"
struct DSNode
{
	int up, rank;
};
class ZbioryZlaczone
{
public:
		
		DSNode * Z;
		ZbioryZlaczone(int n);
		~ZbioryZlaczone();
		void MakeSet(int v);
		int FindSet(int v);
		void UnionSets(Krawedz e);
	
};

