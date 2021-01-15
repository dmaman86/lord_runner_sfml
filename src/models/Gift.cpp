#include "models\Gift.h"

bool Gift::m_is_active = false;

Gift::Gift(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt, GiftType::ID type):
	Trophy(pos, size, txt)
{
	m_type = type;
}

Gift::~Gift()
{
}

void Gift::resetExist()
{
}

void Gift::handleColision(Player& obj)
{
	this->m_isExist = false;
}

bool Gift::isActive(GiftType::ID type)
{
	if (m_type == type && m_is_active)
	{
		m_is_active = false;
		return true;
	}
	return false;
}
