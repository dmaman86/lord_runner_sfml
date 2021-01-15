#pragma once


#include "../models/Gift.h"

class GiftTime : public Gift
{
public:
	GiftTime(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~GiftTime();

	void virtual update() override;


//	void virtual handleColision(DynamicObject& obj) override;

	void virtual handleColision(Player& obj);// needed override


private:

};