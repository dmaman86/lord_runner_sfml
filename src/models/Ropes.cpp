#include "models/Ropes.h"

Ropes::Ropes(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	StaticObj(pos, size, txt)
{

}

void Ropes::handleColision(Creature& obj)
{
	obj.handleColision(*this);
}

bool Ropes::collisionWithStand(Creature& obj, sf::Vector2f size)
{
	return this->m_rec->getGlobalBounds().intersects(obj.getGlobBounds());
}
/*
bool Ropes::collisionWithStand(const sf::Vector2f v2f, const sf::Vector2f)
{
	return this->m_rec->getGlobalBounds().contains(v2f);
}
*/