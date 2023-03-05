#include "Proiectil.h"

Proiectil::Proiectil(sf::Texture* txtura, float pozX, float pozY, float _X, float _Y, float viteza)
{
	
	obiect.setTexture(*txtura);
	obiect.setPosition(pozX, pozY);
	obiect.setScale(0.1f, 0.1f);
	directie.x = _X;
	directie.y = _Y;
	this->viteza = viteza;
}

Proiectil::~Proiectil()
{
//	delete textura;
}

void Proiectil::deseneazaProiectil(sf::RenderTarget* fereastra)
{
	fereastra->draw(this->obiect);
	
}
const sf::FloatRect Proiectil::getMargini()
{
	return obiect.getGlobalBounds();
}
void Proiectil::updateProiectil()
{
	this->obiect.move(viteza * directie);

}
