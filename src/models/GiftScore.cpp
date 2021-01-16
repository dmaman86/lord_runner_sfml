#include "..\..\include\models\GiftScore.h"


GiftScore::GiftScore(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	Gift(pos, size, txt)
{
}

GiftScore::~GiftScore()
{
}
/*
bool GiftLife::isActive()
{
}
*/

void GiftScore::update()
{
}
void GiftScore::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}
/*
void GiftLife::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}
*/
void GiftScore::handleColision(Player& obj)
{
	this->m_isExist = false;
}



/*
void Gift::resetExist()
{
}

void Gift::handleColision(Player& obj)
{
	this->m_isExist = false;
}

bool Gift::isActive(GiftType::ID type)
{
	if (this->m_type == type && m_is_active)
	{
		m_is_active = false;
		return true;
	}
	return false;
}
*/