#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Inamici
{
	sf::CircleShape obiect;
	int hp, hpMax, dmg,tip,nrVf;
	float viteza;
	unsigned int valoare;//nr de puncte daca este distrus
public:
	const int& getDmg();
	const int& getValoare();
	sf::FloatRect getMargini();
	void InitInamici();
	void UpdateInamici();
	void DeseneazaInamici(sf::RenderTarget* fereastra);//RenderWindow este derivata din RenderTarget
	void InitVariabile();
	Inamici(float pozX,float pozY);
	~Inamici();
};

