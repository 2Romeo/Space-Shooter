#include "Inamici.h"


const int& Inamici::getDmg()
{
	return this->dmg;
}

const int& Inamici::getValoare()
{
	return this->valoare;
}

sf::FloatRect Inamici::getMargini()// nu folosim & deoarece marginile sunt temporare
{
	return obiect.getGlobalBounds();
}

void Inamici::InitInamici()
{
	this->obiect.setRadius(nrVf*6);//cu cat are mai multe varfuri cu atat e mai mare
	this->obiect.setPointCount(nrVf);// cu cat mai mic nr de varfuri
	this->obiect.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1,255));// parametrii sunt urmatorii: Nuanta de rosu de la 0 la 255, nuanta de verde de la 0 la 255,
																									//nuanta de albastru de la 0 la 255,opacitatea 255= maxima
}

void Inamici::UpdateInamici()
{
	this->obiect.move(0.f, 5.f);
}

void Inamici::InitVariabile()
{
	hpMax = 50;
	hp = hpMax;//spawnam jucatorul cu hpMaxim
	nrVf = rand() % 8 + 3; //valoare nr. varfurilor va fi intre 0+3 si 7+3
	viteza = (float)nrVf;//scaleaza in functie de nr de vf: scade viteza 
	tip = 0;
	hpMax = nrVf;//scaleaza in functie de nr de vf
	hp = hpMax;//un inamic se spawneaza cu hp max
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
