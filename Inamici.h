#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Inamici
{
	sf::CircleShape obiect;
	int hp, hpMax, dmg, Puncte,tip;
public:
	sf::FloatRect getMargini();
	void InitInamici();
	void UpdateInamici();
	void DeseneazaInamici(sf::RenderTarget* fereastra);//RenderWindow este derivata din RenderTarget
	void InitVariabile();
	Inamici(float pozX,float pozY);
	~Inamici();
};

