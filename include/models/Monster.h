#pragma once

#include "models/Creature.h"
//class Game;
class Monster : public Creature
{

public:
	Monster(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual setDirection() override;

private:

};