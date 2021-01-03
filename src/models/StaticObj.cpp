#include "models/StaticObj.h"


StaticObj::StaticObj
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

void StaticObj::render(sf::RenderWindow* window)
{
	this->Object::render(window);
}

/*
const sf::Vector2f& StaticObj::getPositionRec()
{
	return Object::getPositionRec();
}
*/

