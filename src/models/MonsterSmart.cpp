#include "models/MonsterSmart.h"

MonsterSmart::MonsterSmart
(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt, Player * p) :
	Monster(pos, size, txt), m_size(size)
{
	this->m_rec->setScale(m_rec->getScale().x * (float)0.8, m_rec->getScale().y * (float)1.2);
	m_copy_player = p ;
}

void MonsterSmart::updateDirection()
{
	// is in my row?
	if (isInMyRow())
	{
		if (m_copy_player->getPosition().x > this->getPosition().x)
			m_dircetion = 2;
		else if (m_copy_player->getPosition().x < this->getPosition().x)
			m_dircetion = 1;
	}


	this->SaveLastPosition();
}

bool MonsterSmart::isInMyRow()
{
	return (m_copy_player->getPosition().y < this->getPosition().y + m_size.y &&
		m_copy_player->getPosition().y >= this->getPosition().y - m_size.y);
}
