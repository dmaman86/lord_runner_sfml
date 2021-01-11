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
	//return this->collisionWith(obj);
	if ((this->m_rec->getPosition().x + size.x / 2 >= obj.getSprite().getPosition().x
		&& this->m_rec->getPosition().x - size.x / 2 <= obj.getSprite().getPosition().x)
		&& ( this->m_rec->getPosition().y + size.y / 2 - 5 <= obj.getSprite().getPosition().y
		&& this->m_rec->getPosition().y + size.y / 2 >= obj.getSprite().getPosition().y  )
		)
			return true;
	return false;
}
/*
bool Ropes::collisionWithStand(const sf::Vector2f v2f, const sf::Vector2f)
{
	return this->m_rec->getGlobalBounds().contains(v2f);
}
*/