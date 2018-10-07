#pragma once
#include "ElementListy.h"
class Stos
{
public:
	ElementListy * element;
	void usun();
	bool pusty();
	int top();
	void dodaj(int w);
	Stos();
	~Stos();
};

