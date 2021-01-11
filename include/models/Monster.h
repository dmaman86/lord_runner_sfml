#pragma once

#include "models/DynamicObject.h"

#include <time.h> // srand time

//class Game;
class Monster : public DynamicObject
{

public:
	Monster(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual updateDirection() override;
	void virtual handleColision(DynamicObject& obj);

private:

};