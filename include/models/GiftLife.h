#pragma once


#include "../models/Gift.h"

class GiftLife : public Gift
{
public:
	GiftLife(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	~GiftLife();

	void virtual update() override;


	void virtual handleColision(DynamicObject& obj) ;

	void virtual handleColision(Player& obj);// needed override


private:

};