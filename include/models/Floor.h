#pragma once

#include "StaticObject.h"
class DynamicObject;
class Floor : public StaticObject
{

public:
	Floor(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual handleColision(DynamicObject& obj) override;
	void handleColision(Monster& obj);

	//bool collisionWithStand(const sf::Vector2f, const sf::Vector2f) override;
	bool collisionWithStand(DynamicObject& obj, sf::Vector2f size) override;
	bool collisionWithDig(sf::Vector2f) override;
	void virtual digMe(sf::Time time) override;
	bool virtual digMeFree(sf::Time time, const sf::Vector2f) override;

	void virtual resetExist() override;

	bool isFull();

	//void virtual handleColision(Monster& obj) override;
	//void virtual handleColision(Player& obj) override;
private:
	sf::Time m_t_deleted;
	bool m_full;
};