#pragma once

#include "../models/Gift.h"
/* ================================================
class GiftLife 

	Adds to the player a life
*/
class GiftLife : public Gift
{
public:
	// Constractor / Distactor
	GiftLife(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~GiftLife();
	// virtual functions
	void virtual update() override;
	void virtual handleColision(DynamicObject& obj) override;
	void virtual handleColision(Player& obj) override;
private:
}; // end gift life