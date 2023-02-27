#include "Jucator.h"


sf::Vector2f Jucator::GetPozJucator() const
{
	return this->obiect.getPosition();
}

void Jucator::initTextura()
{ //incarcam textura din fisier

	if (!textura.loadFromFile("Texturi/ship1.png"))
		std::cout << "eroare load file\n";
}
void Jucator::InitVariabile()
{
	viteza = 1.f;
	ClickCooldownMax = 10.f;
	ClickCooldown = ClickCooldownMax;
}
void Jucator::initObiect()
{ //setam textura incarcata
	obiect.setTexture(textura);	
	obiect.setScale(0.1f, 0.1f);
}

void Jucator::miscaObiectul(const float X, const float Y)
{
	obiect.move(viteza * X  , viteza * Y );
}

float Jucator::getviteza()
{
	return viteza;
}

Jucator::Jucator()
{
	InitVariabile();
	initTextura();
	initObiect();
}

Jucator::~Jucator()
{	
}
bool Jucator::PoateTrage()
{
	if (ClickCooldown >= ClickCooldownMax)//daca am asteptat destul pana sa facem din nou click
	{
		ClickCooldown = 0.f;
		return true;
	}
	return false;
}

void Jucator::UpdateCooldown()
{
	if (ClickCooldown < ClickCooldownMax)//daca am asteptat sub sau egal timpul de asteptare creste
		ClickCooldown += 0.3f;//la fiecare click val cooldown se mareste cu 0.3 si cand ajunge la valMax se face din nou 0
}
void Jucator::updateJucator()
{
	UpdateCooldown();
}
const sf::FloatRect& Jucator::getMargini()
{
	return obiect.getGlobalBounds();
}
void Jucator::deseneazaJucator(sf::RenderTarget& x)
{
	x.draw(this->obiect);
}