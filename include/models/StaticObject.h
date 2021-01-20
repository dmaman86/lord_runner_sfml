#pragma once
#include "models/Object.h"
#include "models/Monster.h"
//#include "models/Player.h"
//class Flor;
class Player;
class StaticObject : public Object
{

public:

	StaticObject(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual render(sf::RenderWindow* window)override;
	void virtual resetExist();
	bool virtual collisionWithStand(DynamicObject& obj, sf::Vector2f size) = 0;
	bool virtual collisionWithDig(sf::Vector2f);
	void virtual digMe(sf::Time time) {};
	bool virtual digMeFree(sf::Time time, const sf::Vector2f) ;

	void virtual handleColision(Floor& obj) {};
	void virtual handleColision(Coin& obj) {};
	void virtual handleColision(Ladder& obj) {};
	void virtual handleColision(Ropes& obj) {};
	void virtual handleColision(Monster& obj) {};
	
	void virtual handleColision(DynamicObject& obj) = 0;//override; // important

protected:

private:

};