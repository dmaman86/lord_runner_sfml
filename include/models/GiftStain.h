#pragma once


#include "../models/Gift.h"
#include <SFML/System.hpp>

class GiftStain : public Gift
{
public:
	GiftStain(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~GiftStain();

	void virtual update() override;


	void virtual handleColision(DynamicObject& obj);

	void virtual handleColision(Player& obj);// needed override

	static bool isActive();

private:
	static bool m_is_active;
	static sf::Clock m_clock;
};