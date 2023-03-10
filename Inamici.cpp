#include "Inamici.h"


const int& Inamici::getDmg()
{
	return this->dmg;
}

const int& Inamici::getValoare()
{
	return this->valoare;
}

sf::FloatRect Inamici::getMargini()
{
	return obiect.getGlobalBounds();
}

void Inamici::InitInamici()
{
	this->obiect.setRadius(nrVf*6);
	this->obiect.setPointCount(nrVf);
	this->obiect.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1,255));// parametrii sunt urmatorii: Nuanta de rosu de la 0 la 255, nuanta de verde de la 0 la 255, nuanta de albastru de la 0 la 255,opacitatea 255= maxima
}

void Inamici::UpdateInamici()
{
	this->obiect.move(0.f, 5.f); 
}

void Inamici::InitVariabile()
{
	nrVf = rand() % 8 + 3; //valoare maxima va fi intre 0+3 si 7+3;
	viteza = (float)nrVf;//cu cat avem mai multe varfuri si marime ridicata cu atat scade viteza
	tip = 0;
	hpMax = nrVf;//scaleaza in functie de nr de vf
	hp = hpMax;//spawnam pawn-ul cu hpMax
	dmg = nrVf;//scaleaza in functie de nr de vf
	valoare = nrVf;//scaleaza in functie de nr de vf;
}

Inamici::Inamici(float X,float Y)
{	
	InitVariabile();
	InitInamici();
	obiect.setPosition(X, Y);
}
Inamici::~Inamici()
{

}
void Inamici::DeseneazaInamici(sf::RenderTarget* fereastra)
{
	fereastra->draw(obiect);
}
