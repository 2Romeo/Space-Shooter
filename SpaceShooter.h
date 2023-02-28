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

	//inamici
	void initInamic();
	void updateInamici();
	void updateCombat();//daca un glont intra in coliziune cu un asteroid se despawbeaza ambii

	sf::RenderWindow* getFereastra();

	//gui
	void initGUI();
	void GUIupdate();
	void deseneazaGUI();
	void updateColision();
	void initSistem();

	//background joc
	void initSpatiu();
	void updateSpatiu();
	void deseneazaSpatiu();
	
	//PlayerGUI
	private:
		float SpawnTimer;
		float MaxSpawnTimer;

	sf::RectangleShape baraHp;
	sf::RectangleShape baraHpBackground;
	sf::Text GameOverText;
	// gui + Sistem
	sf::Font GUIfont;
	sf::Text GUItext;
	unsigned int Puncte;
	sf::Sprite SpatiuBackground;
	sf::Texture TexturaBackground;

	sf::RenderWindow *fereastra;//fereastra in care apare aplicatia
	Jucator* jucator;
	
	std::vector<Inamici*> inamici;

	// resurse
	std::map<std::string, sf::Texture*> texturi;
	std::vector<Proiectil*> gloante;//sa tinem cont cate gloante sunt prezente in fereastra
};

