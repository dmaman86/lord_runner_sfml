#pragma once

#include "models/Monster.h"
#include "models/Player.h"

class MonsterSmart : public Monster
{

public:
	MonsterSmart
	(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt ,Player * p);
	
	void virtual setGrid(char **,int,int) override;
	
	void virtual updateDirection() override;

private:
	Player* m_copy_player;
	sf::Vector2f m_size;
	char** m_grid;
	int m_height;
	int m_weidth;
	bool isInMyRow();
};