#include  <SFML/Graphics.hpp> 
#include "SpaceShooter.h"
#include <string>
#include <sstream>
#include <time.h>//pentru functia de randomizare
int main()
{
   
    srand (static_cast<unsigned>(0));//apelam functia de randomizare cu seed ul corespunzator
    SpaceShooter game;
    game.ruleaza();

    return 0;
}