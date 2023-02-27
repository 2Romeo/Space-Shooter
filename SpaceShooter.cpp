#include "SpaceShooter.h"
#include <SFML/Graphics.hpp>



void SpaceShooter::DeseneazaFrame()// deseneaza ceilalti actori, backround etc.
{
	this->getFereastra()->clear();//curata frame-ul anterior
	for (auto* bullet : this->gloante)
	{
		bullet->deseneazaProiectil(this->fereastra);
	}
	for (auto* inamic: this->inamici)
	{
		inamic->DeseneazaInamici(this->fereastra);
	}
	this->jucator->deseneazaJucator(*fereastra);
	this->fereastra->display();//afiseaza
}

SpaceShooter::SpaceShooter()
{
	this->InitTexturi();
	this->initActori();
	this->InitFereastra();
	this->initInamic();
};

SpaceShooter::~SpaceShooter()
{
	for (auto i : this->texturi)
		delete i.second;//stergem elementul sf:wad*

	for (auto *i : this->gloante)
		delete i;
	
	for (auto *i : this->inamici)
		delete i;

	delete[] this->fereastra;
	delete this->jucator;

};


void SpaceShooter::InitTexturi()
{
	this->texturi["Bullet"] = new sf::Texture();//adaugam in map o inregistrare de tip <"Bullet",new Texture()>
	this->texturi["Bullet"]->loadFromFile("Texturi/proiectil.png");
}

void SpaceShooter::initActori()
{
	jucator = new Jucator();
}

void SpaceShooter::initInamic()
{
	MaxSpawnTimer = 50.f;
	SpawnTimer = MaxSpawnTimer;
}

void SpaceShooter::updateInamici()
{
	this->SpawnTimer += 1.f;
	if (this->SpawnTimer >= MaxSpawnTimer)//daca timpul maxim de asteptare a fost atins
	{
		inamici.push_back(new Inamici(rand()%fereastra->getSize().x, -100.f));//face, ramd()%500 pentru ca rand() e un nr foarte mare si avem nevoie de unul mai mic
		SpawnTimer = 0.f;//cronometrul de spawnare ajunge la 0 adica spawnam alt inamic
	}
	for (int i=0;i<inamici.size();i++)
	{
		inamici[i]->UpdateInamici();
		//remove enemy at the bottom of the screen
		if (this->inamici[i]->getMargini().top > fereastra->getSize().y)//daca latura de sus a inamicului este mai mare adica ma jos de fereastra noastra, comparat pe axa orizontala y
		{
			inamici.erase(inamici.begin() + i);//stergem inamicul care iese din "sonar"
			std::cout << inamici.size();
		}
	}
}

sf::RenderWindow* SpaceShooter::getFereastra()
{
	return this->fereastra;
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
	unsigned counter = 0;//cate proiectile sunt eliberate la activ si apoi eliminate adica cate proiectile sunt trase si sunt "in aer"
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
	   gloante.push_back(new Proiectil(texturi["Bullet"],
		   jucator->GetPozJucator().x + jucator->getMargini().width/7100,//adaugam la pozitia pe orizontala unde se spawneaza proiectilul si marimea texturii/2 ca sa se spawneze fix in centrul sprite-ului
		   jucator->GetPozJucator().y
		   , 0.f, -1.f, 5.f));

	}
}
void SpaceShooter::InitFereastra()
{
	fereastra = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Shooter", sf::Style::Close | sf::Style::Titlebar);
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
	updateInamici();
}