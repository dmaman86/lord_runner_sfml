#include "models\Gift.h"

Gift::Gift(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt):
	Trophy(pos, size, txt)
{
}

Gift::~Gift()
{
}

void Gift::resetExist()
{
}

void Gift::handleColision(Player& obj)
{
	this->m_isExist = false;
}

