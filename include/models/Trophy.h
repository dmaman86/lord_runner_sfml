#pragma once

#include "StaticObject.h"
#include "DynamicObject.h"

//class DynamicObject;
//class Player;
//#include "Player.h"

class Trophy : public StaticObject
{

public:
	Trophy(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	virtual ~Trophy();

	void virtual handleColision(DynamicObject& obj) {};

	void virtual handleColision(Player& obj) {};// needed go up in tree

	bool collisionWithStand(DynamicObject& obj, const sf::Vector2f) override;

	// static member function
//	static int getCount();  // return # objects instantiated
//	static int getCollected();
//	static void resetCollected();


	//void virtual handleColision(Monster& obj) override;
	//void virtual handleColision(Player& obj) override;
private:


};