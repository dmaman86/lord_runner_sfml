#include "models/MonsterRand.h"

MonsterRand::MonsterRand(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	Monster(pos, size, txt)
{

}

void MonsterRand::updateDirection(const float& dt)
{
	static float time = 4;

	time += dt;

	if (time > 2.f)
	{
		time = 0;
		m_dircetion = rand() % 4;
	}
	this->SaveLastPosition();
}
