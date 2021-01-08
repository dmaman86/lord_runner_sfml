#include "models/DynamicObject.h"

DynamicObject::DynamicObject
(sf::Vector2f pos, sf::Vector2f size, size_t speed, sf::Texture* txt)
	: Object(pos, size, txt), m_moveSpeed(speed),m_dircetion(0)
{

}


DynamicObject::~DynamicObject()
{

}

void DynamicObject::move(const float& dt)
{
	this->m_rec->move
	(this->getMovement().x * this->m_moveSpeed * dt, this->getMovement().y * this->m_moveSpeed * dt);
}

void DynamicObject::update(const float& dt,int dir)
{

}

void DynamicObject::render(sf::RenderWindow* window)
{
	this->Object::render(window);
}

sf::Sprite DynamicObject::getRecNextStep()
{
	//sf::Vector2f movment = this->getMovement();
	sf::Sprite helper = *m_rec;
	helper.
		setPosition(m_rec->getPosition().x - m_rec->getScale().x
			, m_rec->getPosition().y - m_rec->getScale().y);
	return helper;
}
/*
sf::RectangleShape Creature::getRecNextStep(const float& dt)
{
	sf::Vector2f movment = this->getMovement();
	sf::RectangleShape helper = m_rec;
	helper.move
	(movment.x * this->m_moveSpeed * dt, movment.y * this->m_moveSpeed * dt);
	return helper;
}*/

sf::Vector2f DynamicObject::getMovement()
{
	switch (m_dircetion)
	{
	case 1:
		if (m_rec->getScale().x > 0 )
			this->m_rec->scale( -1, 1 );
		return (sf::Vector2f(-1.f, 0.f));
		break;
	case 2:
		if (m_rec->getScale().x < 0)
			this->m_rec->scale(-1, 1);
		return (sf::Vector2f(1.f, 0.f));
		break;
	case 3:
		return (sf::Vector2f(0.f, -1.f));
		break;
	case 4:
		return (sf::Vector2f(0.f, 1.f));
		break;
	default:
		return (sf::Vector2f(0.f, 0.f));
		break;
	}
}

void DynamicObject::SaveLastPosition()
{
	m_last_postion = this->getPositionRec();
}


void DynamicObject::resetDirection()
{
	this->m_dircetion = 6;
}
/*
void Creature::handleColision(StaticObj& obj)
{
	// just right mow
	// need handle
}

void Creature::handleColision(Creature& obj)
{
	// just right mow
	// need handle
}

void Creature::handleColision(Monster& obj)
{
	// just right mow
	// need handle
}

void Creature::handleColision(Player& obj)
{
	// just right mow
	// need handle
}
*/
void DynamicObject::handleColision(Floor& obj)
{
	this->goBack();
}

void DynamicObject::handleColision(Coin& obj)
{
	//
}

void DynamicObject::handleColision(Ladder& obj)
{
	//
}

void DynamicObject::handleColision(Ropes& obj)
{
	this->m_rec->setRotation(90.f);
}

void DynamicObject::setDirectionDown()
{
	this->m_dircetion = 4;
}


void DynamicObject::resetData()
{
	this->resetDirection();
	if(this->m_rec->getRotation() == 90.f)
		this->m_rec->setRotation( 0.f );
}

void DynamicObject::goBack()
{
	this->m_rec->setPosition(m_last_postion);
}

sf::Vector2f& DynamicObject::getLastPos()
{
	return this->m_last_postion;
}

