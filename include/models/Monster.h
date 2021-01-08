#pragma once

#include "models/DynamicObject.h"
//class Game;
class Monster : public DynamicObject
{

public:
	Monster(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual updateDirection() override;

private:

};