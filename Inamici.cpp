#include "Inamici.h"

void Inamici::InitInamici()
{
	this->obiect.setRadius(rand() + 20);
	this->obiect.setPointCount(rand() + 3);
}

void Inamici::InitVariabile()
{
	tip = 0;
	hpMax = 10;
	hp = 0;
	dmg = 1;
	Puncte = 0;
}

Inamici::Inamici(float X,float Y)
{	
	InitVariabile();
	InitInamici();
	obiect.setPosition(X, Y);
}