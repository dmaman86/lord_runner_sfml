#include "models/Coin.h"

Coin::Coin(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	StaticObject(pos, size, txt)
{}

void Coin::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}
/*
bool Coin::collisionWithStand(const sf::Vector2f v2f, const sf::Vector2f)
{
	return false;
}
*/
bool Coin::collisionWithStand(DynamicObject& obj, sf::Vector2f size)
{
	return false;
}

