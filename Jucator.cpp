#include "Jucator.h"


sf::Vector2f Jucator::GetPozJucator() const
{
	return this->obiect.getPosition();
}

void Jucator::initTextura()
{ 

	if (!textura.loadFromFile("Texturi/ship1.png"))
		std::cout << "eroare load file\n";
}

void Jucator::InitVariabile()
{
	hpMax = 50.f;
	hp = hpMax;
	viteza = 5.f;
	ClickCooldownMax = 10.f;
	ClickCooldown = ClickCooldownMax;

}

void Jucator::initObiect()
{ 
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

const int& Jucator::getHp()
{
	return this->hp;
}

const int& Jucator::getHpMax()
{
	return this->hpMax;
}

Jucator::Jucator()
{
	InitVariabile();
	initTextura();
	initObiect();
	obiect.setPosition(400.f, 300.f);
}

void Jucator::setHp(int aux)
{
	if (aux >= 0)
		hp = aux;
	else
		hp = 0;
}

Jucator::~Jucator()
{	
}

void Jucator::pierdeHp(int dmg)
{
	hp -= dmg;
	if (this->hp < 0)
		hp = 0;
}

bool Jucator::PoateTrage()
{
	if (ClickCooldown >= ClickCooldownMax)//daca am asteptat destul
	{
		ClickCooldown = 0.f;
		return true;
	}
	return false;
}

void Jucator::UpdateCooldown()
{
	if (ClickCooldown < ClickCooldownMax)
		ClickCooldown += 0.3f;//cooldown "de asteptat" se mareste cu 0.3 
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

void Jucator::setPozitie(float x, float y)
{	
	this->obiect.setPosition(x, y);
}
