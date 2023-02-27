#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Jucator
{
	float viteza=10.f;
	sf::Sprite obiect;//obiect care se misca si are si texturi
	sf::Texture textura;
	void initObiect();
	void initTextura();
	float ClickCooldown;
	float ClickCooldownMax;

public:
	const sf::FloatRect& getMargini();
	sf::Vector2f GetPozJucator() const;
	float getviteza();
	bool PoateTrage();
	Jucator();
	~Jucator();
	void InitVariabile();
	void UpdateCooldown();
	void miscaObiectul(const float,const float);//animatie
	void updateJucator();
	void deseneazaJucator(sf::RenderTarget&);
};

