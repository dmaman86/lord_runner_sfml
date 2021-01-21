#include "models/Ladder.h"

// constructor
Ladder::Ladder(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	StaticObject(pos, size, txt)
{
	// made ladder Tall and narrow
	this->m_rec->setScale(m_rec->getScale().x * 0.75, m_rec->getScale().y * 1.15);
}

//========================================================================
void Ladder::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}

// do you stand on laddder
//========================================================================
bool Ladder::collisionWithStand(DynamicObject& obj, sf::Vector2f size)
{
	/*
	if ((this->m_rec->getPosition().x + size.x / 4 > obj.getSprite().getPosition().x
		&& this->m_rec->getPosition().x - size.x / 4 <= obj.getSprite().getPosition().x)
		&& (this->m_rec->getPosition().y + size.y / 2 - 5 > obj.getSprite().getPosition().y
			&& this->m_rec->getPosition().y - size.y  <= obj.getSprite().getPosition().y)
		)
		return true;
	return false;
	*/return this->collisionWith(obj);
}
