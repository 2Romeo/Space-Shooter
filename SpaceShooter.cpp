#include "SpaceShooter.h"
#include <SFML/Graphics.hpp>
#include <sstream>



void SpaceShooter::DeseneazaFrame()// deseneaza ceilalti actori, Background etc.
{	this->getFereastra()->clear();//curata frame-ul anterior
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
	this->InitFereastra();
	this->InitTexturi();
	this->initGUI();
	this->initSpatiu();
	this->initActori();
	this->initInamic();
	this->initSistem();
	DeseneazaFrame();
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

}

void SpaceShooter::InitTexturi()
{
	this->texturi["Bullet"] = new sf::Texture();//adaugam in map o inregistrare de tip <"Bullet",new Texture()>
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
	//this->SpawnTimer += 1.f;
	//if (this->SpawnTimer >= MaxSpawnTimer)//daca timpul maxim de asteptare a fost atins
	//{
	//	inamici.push_back(new Inamici(rand()%fereastra->getSize().x, -100.f));//face, ramd()%500 pentru ca rand() e un nr foarte mare si avem nevoie de unul mai mic
	//	SpawnTimer = 0.f;//cronometrul de spawnare ajunge la 0 adica spawnam alt inamic
	//}
	for (int i = 0; i < inamici.size(); i++)

	{
		bool inamic_sters = false;
		//inamici[i]->UpdateInamici();//miscam sprite-ul

		for (int j = 0; j < gloante.size() && inamic_sters == false; j++) // daca inamicul nu a fost sters cautam alte proiectile cu care s-a intersectat, altfel trecem la alt inamic si nu mai continuam for-ul

			if (this->gloante[j]->getMargini().intersects(inamici[i]->getMargini()))
			{
				Puncte += inamici[i]->getValoare();
				delete inamici[i];
				delete gloante[j];
				gloante.erase(gloante.begin() + j);//stergem proiectilul din vectorul de gloante
				inamici.erase(inamici.begin() + i);//sterge inamicul din vectorul de inamici
				inamic_sters = true;
			}
	}
		//remove enemy at the bottom of the screen
		//if (inamic_sters == false && this->inamici[i]->getMargini().top > fereastra->getSize().y)//daca inamicul nnu a fost deja sters si daca latura de sus a inamicului este mai mare adica ma jos de fereastra noastra, comparat pe axa orizontala y
		//{
		//	inamici.erase(inamici.begin() + i);//stergem inamicul care iese din "sonar"
		//	std::cout << inamici.size();
		//}


	
}

void SpaceShooter::updateInamici()
{	//spawnam
	this->SpawnTimer += 1.f;
	if (this->SpawnTimer >= MaxSpawnTimer)//daca timpul maxim de asteptare a fost atins
	{
		inamici.push_back(new Inamici(rand() % fereastra->getSize().x, -100.f));//face, ramd()%500 pentru ca rand() e un nr foarte mare si avem nevoie de unul mai mic
		SpawnTimer = 0.f;//cronometrul de spawnare ajunge la 0 adica spawnam alt inamic
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
		jucator->setPozitie(0.f, jucator->getMargini().top);//il punem la loc pe axa X la coordonatat 0 adica fix marginea din stanga a consolei

	//coliziunea din partea de sus a consolei
	if (jucator->getMargini().top < 0.f)
		jucator->setPozitie( jucator->getMargini().left,0.f);

	//coliziunea din partea dreapta
	if (jucator->getMargini().left + jucator->getMargini().width >= fereastra->getSize().x) //marginea din stanga a jucatorului + latimea jucatorului = marginea din dreapta
		jucator->setPozitie(fereastra->getSize().x-jucator->getMargini().width, jucator->getMargini().top);//marginea din dreapta a ferestrei - latimea obiectului = marginea din dreapta suprapusa cu marginea din dreapta a ferestre,
		//daca nu scadeam latimea obiectului ramaneam cu marginea din stanga suprapusa cu marginea ferestrei si obiectul putea sa iasa din fereastra
	
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

void SpaceShooter::updateSpatiu()
{
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
	InputUpdate();
	jucator->updateJucator();
	updateColision();
	ProiectilUpdate();
	updateInamici();
	updateCombat();
	GUIupdate();
}