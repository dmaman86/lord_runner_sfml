#include "models/Floor.h"

Floor::Floor(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	StaticObject(pos, size, txt)
{
	this->m_rec->setScale(m_rec->getScale().x * 1, m_rec->getScale().y * 0.8);
	m_t_deleted = sf::seconds(0);
}

void Floor::handleColision(DynamicObject& obj)
{
	if(m_isExist)
		obj.handleColision(*this);
}
/*
bool Flor::collisionWithStand(const sf::Vector2f v2f, const sf::Vector2f size)
{
	return this->getGlobBounds().contains
	(v2f.x , v2f.y + size.y);
}
*/
bool Floor::collisionWithStand(DynamicObject& obj, sf::Vector2f size)
{
	if (m_isExist)
	{
		sf::Sprite helpRec(obj.getSprite());

		helpRec.move(sf::Vector2f(0, 4.5));

		return this->m_rec->getGlobalBounds().intersects(helpRec.getGlobalBounds());
	}
}

bool Floor::collisionWithDig(sf::Sprite& spr)
{
	return this->m_rec->getGlobalBounds().intersects(spr.getGlobalBounds());
}

void Floor::digMe(sf::Time time)
{
	this->m_isExist = false;
	this->m_t_deleted = sf::seconds(time.asSeconds());
}

void Floor::digMeFree(sf::Time time)
{
	if (!m_isExist)
	{
		if (sf::seconds(m_t_deleted.asSeconds()) + sf::seconds(4) < sf::seconds(time.asSeconds()))
		{
			this->m_isExist = true;
			m_t_deleted = sf::seconds(0);
		}
	}
}

void Floor::resetExist()
{
	this->m_isExist = true;
	m_t_deleted = sf::seconds(0);
}

