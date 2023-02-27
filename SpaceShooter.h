#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Jucator.h"
#include "Proiectil.h"
#include "Inamici.h"
#include <map>

class SpaceShooter
{	

public:
	SpaceShooter();
	~SpaceShooter();
	
	void ruleaza();
	void DeseneazaFrame();// desenam texturile frame-ului

	void initActori();
	void InitTexturi();//incarcam toate texturile in joc
	void InitFereastra();//initializam datele din frame in fereastra
	
	void UpdateGeneral();//updatam datele din fereastra la fiecare frame
	void EventsUpdate();//updatam stiva de event-uri
	void InputUpdate();
	void ProiectilUpdate();
	sf::RenderWindow* getFereastra();

private:
	
	sf::RenderWindow *fereastra;//fereastra in care apare aplicatia
	Jucator* jucator;

	Inamici* inamic;

	// resurse
	std::map<std::string, sf::Texture*> texturi;
	std::vector<Proiectil*> gloante;//sa tinem cont cate gloante sunt in joc
};

