#include "models/Coin.h"

Coin::Coin(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	StaticObj(pos, size, txt)
{}

void Coin::handleColision(Creature& obj)
{
	obj.handleColision(*this);
}
/*
bool Coin::collisionWithStand(const sf::Vector2f v2f, const sf::Vector2f)
{
	return false;
}
*/
bool Coin::collisionWithStand(Creature& obj, sf::Vector2f size)
{
	return false;
}

