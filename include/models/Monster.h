#pragma once

#include "models/DynamicObject.h"

#include <time.h> // srand time

//class Game;
class Monster : public DynamicObject
{

public:


	Monster(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual handleColision(Floor& obj)override;
	void virtual handleColision(Player& obj) override;
	void virtual handleColision(DynamicObject& obj);
	void virtual handleColision(Monster& obj) {};
	void virtual handleColision(Coin& obj) {};
	void virtual handleColision(GiftLife& obj) {};
	void virtual handleColision(GiftTime& obj) {};
	void virtual handleColision(GiftScore& obj) {};
	void virtual handleColision(GiftMonster& obj) {};
	void virtual handleColision(GiftStain& obj) {};

	void virtual goBack() override;


private:
	sf::Vector2f m_position_before_floor;
};