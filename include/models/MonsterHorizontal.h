#pragma once

#include "Monster.h"
#include "../macros.h"

#include <time.h> // srand time

class MonsterHorizontal : public Monster
{

public:
	MonsterHorizontal(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual updateDirection(const float& dt) override;
private:
	int m_horizional_dir;
};