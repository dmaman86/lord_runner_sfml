#pragma once

#include "StaticObject.h"
class DynamicObject;
class Floor : public StaticObject
{

public:
	Floor(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual handleColision(DynamicObject& obj) override;
	//bool collisionWithStand(const sf::Vector2f, const sf::Vector2f) override;
	bool collisionWithStand(DynamicObject& obj, sf::Vector2f size) override;

	//void virtual handleColision(Monster& obj) override;
	//void virtual handleColision(Player& obj) override;
private:

};