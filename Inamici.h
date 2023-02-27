#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Inamici
{
	sf::CircleShape obiect;
	int hp, hpMax, dmg, Puncte,tip;
public:
	void InitInamici();
	void InitVariabile();
	Inamici(float pozX,float pozY);
	~Inamici();
};

