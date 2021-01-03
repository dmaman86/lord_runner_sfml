#include "Monster.h"
#include <time.h> 

Monster::Monster(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	Creature(pos, size, 100,txt)
{

}

void Monster::setDirection()
{
	srand((unsigned int)time(NULL));

	m_dircetion = rand() % 4;

	this->SaveLastPosition();
}

