#include "models/Monster.h"

#include "models/Floor.h"


Monster::Monster(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	DynamicObject(pos, size, 100,txt)
{

}

void Monster::handleColision(Floor& obj)
{
	if (obj.isExsist())
		this->goBack();

	else if (this->m_isExist)
	{
		obj.handleColision(*this);
		this->m_isExist = false;
		m_position_before_floor = this->m_last_postion;
	}

	else
	{
		this->m_rec->setPosition(obj.getSprite().getPosition());
	}	
	
}

void Monster::goBack()
{
	if (this->m_isExist)
	{
		DynamicObject::goBack();
	}
	else
	{
		this->m_isExist = true;
		this->m_rec->setPosition(m_position_before_floor);
	}
}




void Monster::handleColision(Player& obj)
{
	//this->m_rec->setPosition(m_first_position);
}

void Monster::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}

