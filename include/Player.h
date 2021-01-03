#pragma once

#include "Creature.h"

class Player : public Creature
{
	
public:
	Player(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void initPlayer(sf::Vector2f pos, sf::Vector2f avgPix, sf::Texture* txt);
	void virtual setDirection() override;

private:
	int m_life;
	int m_score;


};