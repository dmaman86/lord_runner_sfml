#pragma once


#include "StaticObject.h"

class DynamicObject;
//class Player;
//#include "Player.h"

class Coin : public StaticObject
{

public:
	Coin(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual handleColision(DynamicObject& obj) override;

	void virtual handleColision(Player& obj) ;// needed override

	bool collisionWithStand(DynamicObject& obj, const sf::Vector2f) override ;

	//void virtual handleColision(Monster& obj) override;
	//void virtual handleColision(Player& obj) override;
private:

};