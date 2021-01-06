#pragma once


#include "StaticObject.h"

class Ladder : public StaticObject
{

public:
	Ladder(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual handleColision(DynamicObject& obj) override;
	bool collisionWithStand(DynamicObject& obj, sf::Vector2f size) override;
	//bool collisionWithStand(const sf::Vector2f, const sf::Vector2f) override;

private:

};