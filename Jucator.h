#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Jucator
{
	float viteza;
	int hp, hpMax;
	sf::Sprite obiect;//obiect care se misca si are si texturi
	sf::Texture textura;
	void initObiect();
	void initTextura();
	float ClickCooldown;
	float ClickCooldownMax;

public:
	const sf::FloatRect& getMargini();
	const int& getHp();
	const int& getHpMax();
	void setHp(int);
	void pierdeHp(int);
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
	void setPozitie(float x, float y);
};

