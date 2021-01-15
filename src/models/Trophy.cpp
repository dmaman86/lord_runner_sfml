#include "models\Trophy.h"

Trophy::Trophy(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	StaticObject(pos, size, txt)
{
}

Trophy::~Trophy()
{
}


bool Trophy::collisionWithStand(DynamicObject& obj, sf::Vector2f size)
{
	return false;
}
