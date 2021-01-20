#pragma once

#include "models/Monster.h"

class MonsterRand : public Monster
{

public:
	MonsterRand(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual updateDirection(const float& dt) override;
private:
};