#include "models/Coin.h"

int Coin::m_num_coins = 0;
int Coin::m_num_collected = 0;


Coin::Coin(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	StaticObject(pos, size, txt)
{
	++m_num_coins;
}

Coin::~Coin()
{
	--m_num_coins;
}

int Coin::getCount()
{
	return m_num_coins;
}

int Coin::getCollected()
{
	return m_num_collected;
}

void Coin::resetCollected()
{
	m_num_collected = 0;
}

void Coin::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}

void Coin::handleColision(Player& obj)
{
	this->m_isExist = false;
	this->m_num_collected++;
}

bool Coin::collisionWithStand(DynamicObject& obj, sf::Vector2f size)
{
	return false;
}
