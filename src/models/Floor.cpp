#include "models/Floor.h"

Floor::Floor(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	StaticObject(pos, size, txt), m_full(false)
{
	this->m_rec->setScale(m_rec->getScale().x * 1, m_rec->getScale().y * 0.8);
	m_t_deleted = sf::seconds(0);
}

void Floor::handleColision(DynamicObject& obj)
{
	//if(m_isExist)
		obj.handleColision(*this);
}

void Floor::handleColision(Monster& obj)
{
	m_full = true;
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
	if (m_isExist || m_full)
	{
		sf::Sprite helpRec(obj.getSprite());

		helpRec.move(sf::Vector2f(0, 4.5));

		return this->m_rec->getGlobalBounds().intersects(helpRec.getGlobalBounds());
	}
}

bool Floor::collisionWithDig(sf::Vector2f point)
{
	return this->m_rec->getGlobalBounds().contains(point);
}

void Floor::digMe(sf::Time time)
{
	this->m_isExist = false;
	this->m_t_deleted = sf::seconds(time.asSeconds());
}

bool Floor::digMeFree(sf::Time time, DynamicObject& obj)
{
	if (!m_isExist)
	{
		if (sf::seconds(m_t_deleted.asSeconds()) + sf::seconds(4) < sf::seconds(time.asSeconds()))
		{
			this->m_isExist = true;
			m_t_deleted = sf::seconds(0);
			this->m_full = false;
			if(this->collisionWith(obj))
				return true;
		}
	}
	return false;
}

void Floor::resetExist()
{
	this->m_isExist = true;
	this->m_full = false;
	m_t_deleted = sf::seconds(0);
}

bool Floor::isFull()
{
	return m_full;
}

