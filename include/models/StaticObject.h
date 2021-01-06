#pragma once
#include "models/Object.h"
#include "models/Monster.h"
#include "models/Player.h"
//class Flor;

class StaticObject : public Object
{

public:

	StaticObject(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual render(sf::RenderWindow* window)override;
	
	bool virtual collisionWithStand(DynamicObject& obj, sf::Vector2f size) = 0;
	//bool virtual collisionWithStand(const sf::Vector2f, const sf::Vector2f) = 0;

	//void virtual handleColision(Object& obj) override;
	//void virtual handleColision(StaticObj& obj) override;
	void virtual handleColision(DynamicObject& obj) = 0;// override; // important
	//void virtual handleColision(Monster& obj) = 0;
	//void virtual handleColision(Player& obj) = 0;
	//void virtual handleColision(Flor& obj);

//   void  virtual render(sf::RenderWindow* target)override;
//	const sf::Vector2f& getPositionRec();

private:

};