#include "models/Ropes.h"

Ropes::Ropes(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	StaticObject(pos, size, txt)
{
	// that made ropes low
	this->m_rec->setScale(m_rec->getScale().x * 1, m_rec->getScale().y * 0.5);
}

void Ropes::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}

bool Ropes::collisionWithStand(DynamicObject& obj, sf::Vector2f size)
{
	return this->collisionWith(obj);
	//return this->m_rec->getGlobalBounds().intersects(obj.getGlobBounds());
}
/*
bool Ropes::collisionWithStand(const sf::Vector2f v2f, const sf::Vector2f)
{
	return this->m_rec->getGlobalBounds().contains(v2f);
}
*/