#include "models/Ladder.h"

Ladder::Ladder(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	StaticObj(pos, size, txt)
{}

void Ladder::handleColision(Creature& obj)
{
	obj.handleColision(*this);
}

bool Ladder::collisionWithStand(Creature& obj, sf::Vector2f size)
{
	return this->m_rec->getGlobalBounds().intersects(obj.getGlobBounds());
}
/*
bool Ladder::collisionWithStand(const sf::Vector2f v2f, const sf::Vector2f b)
{
	return this->m_rec->getGlobalBounds().contains(v2f);
}
*/
