#pragma once
class Krawedz
{
public: 
	int wpoczatkowy, wkoncowy, waga;
		bool operator () (const Krawedz & k1, const Krawedz & k2)
		{
			if (k1.waga > k2.waga) return true;
			if (k1.waga < k2.waga) return false;
			return false;
		}

	Krawedz();
	~Krawedz();
};

