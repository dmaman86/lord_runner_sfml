#include "models/StaticObject.h"


StaticObject::StaticObject
(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	Object(pos, size, txt)
{
	
}


// NOT DELEATED !!!!!
/*
void StaticObj::handleColision(Object& obj)
{
	// IGNORE - We do not want to create an object
}

*/


/*
void StaticObj::handleColision(StaticObj& obj)
{
	// IGNORE - static can't move!
}
void StaticObj::handleColision(Flor& obj)
{
	// IGNORE - static can't move!
}


void StaticObj::handleColision(Monster& obj)
{
	obj.handleColision(*this);
}

void StaticObj::handleColision(Player& obj)
{
	obj.handleColision(*this);
}
*/
/*
void StaticObj::handleColision(Creature& obj)
{
	obj.handleColision(*this);
}
*/

void StaticObject::render(sf::RenderWindow* window)
{
	if(m_isExist)
		this->Object::render(window);
}

void StaticObject::resetExist()
{
	this->m_isExist = true;
}

bool StaticObject::collisionWithDig(sf::Sprite& spr)
{
	return false;
}


