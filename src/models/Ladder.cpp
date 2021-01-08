#include "models/Ladder.h"

Ladder::Ladder(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	StaticObject(pos, size, txt)
{}

void Ladder::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}

bool Ladder::collisionWithStand(DynamicObject& obj, sf::Vector2f size)
{
	return this->collisionWith(obj);
}
/*
bool Ladder::collisionWithStand(const sf::Vector2f v2f, const sf::Vector2f b)
{
	return this->m_rec->getGlobalBounds().contains(v2f);
}
*/
