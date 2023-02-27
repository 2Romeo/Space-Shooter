#include "Inamici.h"

sf::FloatRect Inamici::getMargini()// nu folosim & deoarece marginile sunt temporare
{
	return obiect.getGlobalBounds();
}

void Inamici::InitInamici()
{
	this->obiect.setRadius(rand()%20 + 20);
	this->obiect.setPointCount(rand()%20 + 2);// cu cat mai mic nr de varfuri
	this->obiect.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1,255));// parametrii sunt urmatorii: Nuanta de rosu de la 0 la 255, nuanta de verde de la 0 la 255,
																									//nuanta de albastru de la 0 la 255,opacitatea 255= maxima
}

void Inamici::UpdateInamici()
{
	this->obiect.move(0.f, 5.f);
}

void Inamici::InitVariabile()
{
	tip = 0;
	hpMax = 10;
	hp = 0;
	dmg = 1;
	Puncte = 5;
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
