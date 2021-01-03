#pragma once

#include "StaticObj.h"

class Flor : public StaticObj
{

public:
	Flor(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual handleColision(Creature& obj) override;
	//bool collisionWithStand(const sf::Vector2f, const sf::Vector2f) override;
	bool collisionWithStand(Creature& obj, sf::Vector2f size) override;

	//void virtual handleColision(Monster& obj) override;
	//void virtual handleColision(Player& obj) override;
private:

};