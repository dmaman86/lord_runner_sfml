#include "models/MonsterHorizontal.h"

MonsterHorizontal::MonsterHorizontal(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	Monster(pos, size, txt), m_horizional_dir(1)
{
	this->m_rec->setScale(m_rec->getScale().x * (float)0.8,m_rec->getScale().y * (float)1.2);
}

void MonsterHorizontal::updateDirection(const float& dt)
{
	if (this->getLastPos() == this->m_rec->getPosition())
	{
		(m_horizional_dir == Object_Direction::Left) ?
			m_horizional_dir = Object_Direction::Right : m_horizional_dir = Object_Direction::Left;
	}

	m_dircetion = m_horizional_dir;
	this->SaveLastPosition();
}
