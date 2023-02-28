#include "SpaceShooter.h"
#include <SFML/Graphics.hpp>
#include <sstream>



void SpaceShooter::DeseneazaFrame()
{	this->getFereastra()->clear();
	this->deseneazaSpatiu();
	this->deseneazaGUI();
	for (auto* bullet : this->gloante)
	{
		bullet->deseneazaProiectil(this->fereastra);
	}
	for (auto* inamic: this->inamici)
	{
		inamic->DeseneazaInamici(this->fereastra);
	}
	this->jucator->deseneazaJucator(*fereastra);
	if (jucator->getHp() <= 0)
		fereastra->draw(GameOverText);
	this->fereastra->display();//afiseaza
}

SpaceShooter::SpaceShooter()
{
	this->initSistem();
	this->initSpatiu();
	this->InitTexturi();
	this->initActori();
	this->InitFereastra();
	this->initInamic();
	this->initGUI();
};

SpaceShooter::~SpaceShooter()
{
	for (auto i : this->texturi)
		delete i.second;//stergem doar textura

	for (auto *i : this->gloante)
		delete i;
	
	for (auto *i : this->inamici)
		delete i;

	delete[] this->fereastra;
	delete this->jucator;

}

void SpaceShooter::InitTexturi()
{
	this->texturi["Bullet"] = new sf::Texture();
	this->texturi["Bullet"]->loadFromFile("Texturi/proiectil.png");
}

void SpaceShooter::initActori()
{
	jucator = new Jucator();
}//init jucator default pawn

void SpaceShooter::initInamic()
{
	MaxSpawnTimer = 50.f;
	SpawnTimer = MaxSpawnTimer;
}

void SpaceShooter::updateCombat()
{
	
	for (int i = 0; i < inamici.size(); i++)

	{
		bool inamic_sters = false;
		//miscam sprite-ul

		for (int j = 0; j < gloante.size() && inamic_sters == false; j++) // daca inamicul nu a fost sters cautam alte proiectile cu care s-a intersectat, altfel trecem la alt inamic si nu mai continuam for-ul

			if (this->gloante[j]->getMargini().intersects(inamici[i]->getMargini()))
			{
				Puncte += inamici[i]->getValoare();
				delete inamici[i];
				delete gloante[j];
				gloante.erase(gloante.begin() + j);
				inamici.erase(inamici.begin() + i);
				inamic_sters = true;
			}
	}
		


	
}

void SpaceShooter::updateInamici()
{	//spawnam
	this->SpawnTimer += 1.f;
	if (this->SpawnTimer >= MaxSpawnTimer)//daca timpul maxim de asteptare a fost atins
	{
		inamici.push_back(new Inamici(rand() % fereastra->getSize().x, -100.f));
		SpawnTimer = 0.f;// spawnam alt inamic
	}

	//updatam
	unsigned counter = 0;//cati inamici avem spawnati
	for (auto* i : inamici)
	{
		i->UpdateInamici();
		//eliminam inamicii care nu sunt in fereastra(ating partea de jos a ferestrei) adica partea de sus are coordonate mai mare decat coordonata y a consolei adica de verticala
		if (i->getMargini().top > fereastra->getSize().y)
		{	//delete i;	delete this->inamici.at(counter);
			this->inamici.erase(inamici.begin() + counter);
			--counter;
		}
		else//daca inca sunt in consola//interactiune jucator-inamic
			if (jucator->getMargini().intersects(i->getMargini()))//daca se intersecteaza cu jucatorul nostru
			{
				int aux = jucator->getHp();
				jucator->setHp(aux - i->getDmg());
				//jucator->pierdeHp(inamici.at(counter)->getDmg());
				this->inamici.erase(inamici.begin() + counter);
				--counter;
			}
		
		counter++;
		//std::cout << counter << " \n";
	}
	
}

sf::RenderWindow* SpaceShooter::getFereastra()
{
	return this->fereastra;
}

void SpaceShooter::GUIupdate()
{
	std::stringstream ss;
	ss <<" Puncte: "<< this->Puncte;
	GUItext.setString(ss.str());
	//update player GUI~ hp

	float ProcentHp = static_cast<float>(jucator->getHp()) / jucator->getHpMax();
	this->baraHp.setSize(sf::Vector2f(300.f* ProcentHp, baraHp.getSize().y));
}

void SpaceShooter::deseneazaGUI()
{
	fereastra->draw(GUItext);
	fereastra->draw(baraHpBackground);
	fereastra->draw(baraHp);

}

void SpaceShooter::updateColision()
{	//coliziunea din partea stanga: jucatorul nu poate iesi prin partea stanga a consolei
	if (jucator->getMargini().left < 0.f)
		jucator->setPozitie(0.f, jucator->getMargini().top);

	//coliziunea din partea de sus a consolei
	if (jucator->getMargini().top < 0.f)
		jucator->setPozitie( jucator->getMargini().left,0.f);

	//coliziunea din partea dreapta
	if (jucator->getMargini().left + jucator->getMargini().width >= fereastra->getSize().x) 
		jucator->setPozitie(fereastra->getSize().x-jucator->getMargini().width, jucator->getMargini().top);
		
	//coliziunea din partea de jos
	if (jucator->getMargini().top + jucator->getMargini().height >= fereastra->getSize().y) //marginea din stanga a jucatorului + latimea jucatorului = marginea din dreapta
		jucator->setPozitie(jucator->getMargini().left,fereastra->getSize().y - jucator->getMargini().height);//marginea din dreapta a ferestrei - latimea obiectului = marginea din dreapta suprapusa cu marginea din dreapta a ferestre,

}

void SpaceShooter::initSistem()
{
	Puncte = 0;
}

void SpaceShooter::initSpatiu()
{ 
	if (this->TexturaBackground.loadFromFile("Texturi/Background.jpg") == false)
		std::cout << "textura background couldnt load\n";
	else
		SpatiuBackground.setTexture(TexturaBackground);
}

void SpaceShooter::deseneazaSpatiu()
{
	this->fereastra->draw(SpatiuBackground);
}

void SpaceShooter::ruleaza()
{
	//updatam aici deoarece chiar daca avem game over trebuie sa putem inchide fereastra
	while (this->getFereastra()->isOpen())
	{   EventsUpdate();
		if(jucator->getHp()>0)
			UpdateGeneral();
		this->DeseneazaFrame();
	}
}

void SpaceShooter::ProiectilUpdate()
{
	unsigned counter = 0;//cate proiectile sunt eliberate la activ si apoi eliminate adica cate proiectile sunt trase si sunt "in aer"
	//cate proiectile eliminam
	for (auto* i : gloante)
	{	
		i->updateProiectil();
		//eliminam proiectilele care nu sunt in fereastra(partea de sus a ferestrei)
		if (i->getMargini().top + i->getMargini().height < 0.f)
		{	//eliminam un proiectil din vector
			//delete i;//nu putem sterge orice proiectil asa ca folosim functia .at()
			delete this->gloante.at(counter);
			this->gloante.erase(gloante.begin() + counter);
			--counter;
			
		}
		counter++;
		std::cout << counter << " \n";
	}
}

void SpaceShooter::initGUI()
{
	if (this->GUIfont.loadFromFile("Fonturi/Karma Future.ttf") == false)
		std::cout << "font error not loaded\n";
	//puncte
	GUItext.setPosition(600.f, 25.f);
	GUItext.setFont(GUIfont);
	GUItext.setCharacterSize(30);
	GUItext.setFillColor(sf::Color::White);
	//game over
	GameOverText.setFont(GUIfont);
	GameOverText.setCharacterSize(60);
	GameOverText.setFillColor(sf::Color::Red);
	GameOverText.setString("GAME OVER Romeo");
	GameOverText.setPosition
	(
		fereastra->getSize().x / 2.f - GameOverText.getGlobalBounds().width/2.f,
		fereastra->getSize().y / 2.f - GameOverText.getGlobalBounds().height/2.f
	);

	//initializa playerGUI ~hp bar
	baraHp.setSize(sf::Vector2f(300.f, 25.f));
	baraHp.setFillColor(sf::Color::Red);
	baraHp.setPosition(sf::Vector2f(10.f, 25.f));
	

	baraHpBackground = baraHp;
	baraHpBackground.setFillColor(sf::Color(25,25,25,200));
}

void SpaceShooter::InputUpdate()
{		//misca jucator
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->jucator->miscaObiectul(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->jucator->miscaObiectul(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->jucator->miscaObiectul(0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->jucator->miscaObiectul(1.f, 0.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&jucator->PoateTrage())
	{
	   gloante.push_back(new Proiectil(texturi["Bullet"],
		   jucator->GetPozJucator().x + jucator->getMargini().width/7100,//adaugam la pozitia pe orizontala unde se spawneaza proiectilul si marimea texturii/2 ca sa se spawneze fix in centrul sprite-ului
		   jucator->GetPozJucator().y
		   , 0.f, -1.f, 5.f));

	}
}

void SpaceShooter::InitFereastra()
{
	fereastra = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Shooter", sf::Style::Close | sf::Style::Titlebar);
	fereastra->setFramerateLimit(120);//framerate dependent
	fereastra->setVerticalSyncEnabled(0);//nu ne place V-Sync
}

void SpaceShooter::EventsUpdate()
{
	sf::Event x;
	while (this->fereastra->pollEvent(x));//metoda pollEvent returneaza evenimentul din varful stivei de evenimente,daca exista, si il salveaza in variabila sf::event data ca parametru
	//verificam ce eveniment am salvat in variabila
	{
		if (x.type == sf::Event::Closed)
			fereastra->close();
		if (x.KeyPressed != 0 && x.Event::key.code == sf::Keyboard::Escape)
			fereastra->close();
	}
}

void SpaceShooter::UpdateGeneral()
{
	InputUpdate();
	jucator->updateJucator();
	updateColision();
	ProiectilUpdate();
	updateInamici();
	updateCombat();
	GUIupdate();
}