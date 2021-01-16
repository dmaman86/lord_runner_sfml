#pragma once


#include "Trophy.h"

class DynamicObject;

class Coin : public Trophy
{
public:
	Coin(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~Coin();

	void virtual handleColision(DynamicObject& obj) override;
	void resetExist() override;

	void virtual handleColision(Player& obj) override;// needed override

	// static member function
	static int getCount();  // return # objects instantiated
	static int getCollected();
	static void resetCollected();

private:
	static int m_num_coins;
	static int m_num_collected;
};