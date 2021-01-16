#include "..\..\include\models\GiftTime.h"


GiftTime::GiftTime(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	Gift(pos, size, txt, GiftType::addTime)
{
}

GiftTime::~GiftTime()
{
}
void GiftTime::update()
{
}

void GiftTime::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}

/*
void GiftTime::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}
*/
void GiftTime::handleColision(Player& obj)
{
	this->m_isExist = false;
	this->m_is_active = true;
}

