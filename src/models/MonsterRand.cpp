#include "models/MonsterRand.h"

MonsterRand::MonsterRand(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	Monster(pos, size, txt)
{

}

void MonsterRand::updateDirection()
{
	srand((unsigned int)time(NULL));

	m_dircetion = rand() % 4;

	this->SaveLastPosition();
}
