#pragma once


#include "StaticObj.h"

class Ladder : public StaticObj
{

public:
	Ladder(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual handleColision(Creature& obj) override;
	bool collisionWithStand(Creature& obj, sf::Vector2f size) override;
	//bool collisionWithStand(const sf::Vector2f, const sf::Vector2f) override;

private:

};