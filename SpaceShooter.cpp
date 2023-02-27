#include "SpaceShooter.h"
#include <SFML/Graphics.hpp>



SpaceShooter::SpaceShooter()
{
	this->InitTexturi();
	this->initActori();
	this->InitFereastra();
	
};

SpaceShooter::~SpaceShooter()
{
	for (auto &i : this->texturi)
		delete i.second;//stergem elementul sf:wad*

	delete[] this->fereastra;
	delete this->jucator;

	for (auto i : this->gloante)
		delete i;
};


void SpaceShooter::InitTexturi()
{
	this->texturi["Bullet"] = new sf::Texture();//adaugam in map o inregistrare de tip <"Bullet",new Texture()>
	this->texturi["Bullet"]->loadFromFile("Texturi/proiectil.png");
}

void SpaceShooter::initActori()
{
	jucator = new Jucator();
	inamic
}

sf::RenderWindow* SpaceShooter::getFereastra()
{
	return this->fereastra;
}

void SpaceShooter::DeseneazaFrame()// deseneaza actori backround etc.
{
	this->getFereastra()->clear();//curata frame-ul anterior
	for (auto* bullet : this->gloante)
	{
		bullet->deseneazaProiectil(this->fereastra);
	}
	this->jucator->deseneazaJucator(*fereastra);
	this->fereastra->display();//afiseaza
}

void SpaceShooter::ruleaza()
{	
	while (this->getFereastra()->isOpen())
	{
		UpdateGeneral();
		this->DeseneazaFrame();// cele doua apeluri se realizeaza standard la orice joc 
	}
}

void SpaceShooter::ProiectilUpdate()
{
	unsigned counter = 0;//cate proiectile sunt eliberate la activ apoi eliminate adica cate proiectile sunt trase si sunt "in aer"
	//cate proiectile eliminam
	for (auto* i : gloante)
	{	
		i->updateProiectil();
		//eliminam proiectilele care nu sunt in fereastra(partea de sus a ferestrei)
		if (i->MarginiReale().top + i->MarginiReale().height < 0.f)
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
	   gloante.push_back(new Proiectil(texturi["Bullet"], jucator->GetPozJucator().x, jucator->GetPozJucator().y, 0.f, -1.f, 5.f));

	}
}
void SpaceShooter::InitFereastra()
{
	fereastra = new sf::RenderWindow(sf::VideoMode(800, 600), "Baboon dog", sf::Style::Close | sf::Style::Titlebar);
	//																					^          ^         ^
	//							        												|          |         |
	//							  ce butoane apar la fereastra noastra de joc: buton de inchidere si buton de titlu jocului
	fereastra->setFramerateLimit(120);//framerate dependent
	fereastra->setVerticalSyncEnabled(0);//nu ne place V-Sync
}
void SpaceShooter::EventsUpdate()
{
	sf::Event x;//orice eveniment ce se intampal cu fereastra de ex: inchidere fereastra, miscare mouse
	while (this->fereastra->pollEvent(x));//metoda pollEvent returneaza evenimentul din varful stivei de evenimente,daca exista, si il salveaza in variabila sf::event data ca parametru
	//verificam ce eveniment am salvat in variabila
	{
		if (x.type == sf::Event::Closed)//verificam daca evenimentul a fost inchiderea ferestrei, impropriu spus, deoarece evenimentul se refera doar la apasarea butonului de inchidere
			fereastra->close();//implementam inchiderea reala a ferestrei
		if (x.KeyPressed != 0 && x.Event::key.code == sf::Keyboard::Escape)//daca evenimentul este de apasare a butonului si butonul apasat este ESC
			fereastra->close();
	}
}
void SpaceShooter::UpdateGeneral()
{
	EventsUpdate();
	InputUpdate();
	jucator->updateJucator();
	ProiectilUpdate();
}