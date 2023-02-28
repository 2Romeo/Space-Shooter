#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Proiectil
{	
private:
	sf::Sprite obiect;
	sf::Texture* textura;
	sf::Vector2f directie;//f de la final vine de la float, i de la int etc.
	float viteza, pozitieX, pozitieY;
public:
	bool PoateTrage();
	Proiectil(sf::Texture* txtura,float pozitieX,float pozitieY,float X, float,float viteza);
	~Proiectil();
	void updateProiectil();
	void deseneazaProiectil(sf::RenderTarget*);
	void initProiectil();
	const sf::FloatRect getMargini();//desenam marginile proiectilului

};

