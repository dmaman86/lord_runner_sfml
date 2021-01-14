#include "models/Monster.h"


Monster::Monster(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	DynamicObject(pos, size, 100,txt)
{

}

void Monster::updateDirection()
{
	srand((unsigned int)time(NULL));

	m_dircetion = rand() % 4;

	this->SaveLastPosition();
}

void Monster::handleColision(Player& obj)
{
	//this->m_rec->setPosition(m_first_position);
}

void Monster::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}

