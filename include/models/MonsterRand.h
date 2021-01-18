#pragma once

#include "models/Monster.h"

#include <time.h> // srand time

//class Game;
class MonsterRand : public Monster
{

public:
	MonsterRand(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual updateDirection() override;
private:
};