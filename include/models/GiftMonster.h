#pragma once


#include "../models/Gift.h"

class GiftMonster : public Gift
{
public:
	GiftMonster(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~GiftMonster();

	void virtual update() override;


	void virtual handleColision(DynamicObject& obj);

	void virtual handleColision(Player& obj);// needed override

	static bool isActive();

private:
	static bool m_is_active;

};