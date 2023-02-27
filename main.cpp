#include  <SFML/Graphics.hpp> // replace quotes with less than and greater than symbols
#include "SpaceShooter.h"
#include <time.h>//pentru functia de randomizare
int main()
{
   // sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy burb");
    srand (static_cast<unsigned>(0));//apelam functia de randomizare cu seed ul corespunzator
    SpaceShooter game;
    game.ruleaza();

    return 0;
}