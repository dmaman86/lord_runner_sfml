#include "models/DynamicObject.h"

// Constractor / Distactor

/*/ Constractor :  
/*   position ,size and texture - send to Object constractor.
/*   speed , direction initialized here
/*/
DynamicObject::DynamicObject
(sf::Vector2f pos, sf::Vector2f size, size_t speed, sf::Texture* txt)
	: Object(pos, size , txt), m_moveSpeed(speed),m_dircetion(0)
{
	// that made dynamic Object can move betwwen two static Object
	this->m_rec->setScale(m_rec->getScale() * (float)0.95);
	m_first_position = this->m_rec->getPosition();
}

// virual distructor
DynamicObject::~DynamicObject()
{
	// Empty - no memory allocation
}

/* ===================================== *
 * ######### Public Functions ########## *
 * ===================================== */

void DynamicObject::setDirectionDown()
{
	this->m_dircetion = 4;
}


void DynamicObject::resetData()
{
	this->resetDirection();
	if (this->m_rec->getRotation() == 90.f)
		this->m_rec->setRotation(0.f);
}


void DynamicObject::move(const float& dt)
{
	this->m_rec->move
	(this->getMovement().x * this->m_moveSpeed * dt, this->getMovement().y * this->m_moveSpeed * dt);
}

void DynamicObject::goBack()
{
	this->m_rec->setPosition(getLastPos());
}

void DynamicObject::setFirstPos()
{
	this->m_rec->setPosition(getFirstPos());
}

/* ######### Virual Functions ########## */

void DynamicObject::handleColision(Floor& obj)
{
	this->goBack();
}
/*
void DynamicObject::handleColision(Coin& obj)
{
	//
}
*//**/
void DynamicObject::handleColision(Ladder& obj)
{
	// change texture !
}

void DynamicObject::handleColision(Ropes& obj)
{
	// change texture !


	// para rotate on ropes - maybe change texture?
	//this->m_rec->setRotation(90.f);
}

/* ===================================== *
 * ######### Private Functions ########## *
 * ===================================== */

// ############### Auxiliary Functions : ############ //

void DynamicObject::resetDirection()
{
	this->m_dircetion = 6;
}

void DynamicObject::SaveLastPosition()
{
	m_last_postion = this->getSprite().getPosition();
}

// ############### Get Functions : ############ //

const sf::Vector2f& DynamicObject::getMovement() const
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

const sf::Vector2f& DynamicObject::getLastPos() const
{
	return this->m_last_postion;
}

const sf::Vector2f& DynamicObject::getFirstPos() const
{
	return this->m_first_position;
}

