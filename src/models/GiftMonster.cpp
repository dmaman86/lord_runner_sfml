#include "..\..\include\models\GiftMonster.h"

bool GiftMonster::m_is_active = false;

GiftMonster::GiftMonster(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	Gift(pos, size, txt)
{
}

GiftMonster::~GiftMonster()
{
}
void GiftMonster::update()
{
}
bool GiftMonster::isActive()
{
	if (m_is_active)
	{
		m_is_active = false;
		return true;
	}
	return false;
}


void GiftMonster::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}

/*
void GiftTime::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}
*/
void GiftMonster::handleColision(Player& obj)
{
	this->m_isExist = false;
	this->m_is_active = true;
}

