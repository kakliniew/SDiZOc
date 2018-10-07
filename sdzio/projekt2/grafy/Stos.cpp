#include "stdafx.h"
#include "Stos.h"


Stos::Stos()
{
	element = NULL;
}


Stos::~Stos()
{
	while (element) usun();
}

void Stos::usun()
{
	if (element)
	{
		ElementListy * pomocniczy = element;
		element = element->nastepny;
		delete pomocniczy;
	}
}

bool Stos::pusty()
{
	return !element;
}

int Stos::top()
{
	return element->wierzcholek;
}

void Stos::dodaj(int nowy)
{
	ElementListy * pomocniczy = new ElementListy;
	pomocniczy->wierzcholek = nowy;
	pomocniczy->nastepny = element;
	element = pomocniczy;
}