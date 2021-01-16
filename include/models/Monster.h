#pragma once

#include "models/DynamicObject.h"

#include <time.h> // srand time

//class Game;
class Monster : public DynamicObject
{

public:
	Monster(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual updateDirection() override;
	void virtual handleColision(Player& obj) override;
	void virtual handleColision(DynamicObject& obj);
	void virtual handleColision(Monster& obj) {};
	void virtual handleColision(Coin& obj) {};
	void virtual handleColision(GiftLife& obj) {};
	void virtual handleColision(GiftTime& obj) {};



private:

};