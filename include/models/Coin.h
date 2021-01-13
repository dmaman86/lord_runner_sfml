#pragma once


#include "StaticObject.h"

class DynamicObject;
//class Player;
//#include "Player.h"

class Coin : public StaticObject
{

public:
	Coin(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~Coin();

	void virtual handleColision(DynamicObject& obj) override;

	void virtual handleColision(Player& obj) ;// needed override

	bool collisionWithStand(DynamicObject& obj, const sf::Vector2f) override ;

	// static member function
	static int getCount();  // return # objects instantiated

	//void virtual handleColision(Monster& obj) override;
	//void virtual handleColision(Player& obj) override;
private:
	static int m_num_coins;

};