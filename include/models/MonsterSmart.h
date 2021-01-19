#pragma once

#include "models/Monster.h"
#include "models/Player.h"
#include "models/Ladder.h"
#include "models/Ropes.h"

#include "../macros.h"
#include <vector>

class MonsterSmart : public Monster
{

public:
	MonsterSmart
	(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt ,Player * p);
	
	void virtual setGrid(std::vector<std::vector<char>>) override;
	//void virtual handleColision(Ladder& obj) override;
	//void virtual handleColision(Ropes& obj) override;
	void virtual updateDirection() override;

private:
	Player* m_copy_player;
	sf::Vector2f m_size;
	std::vector<std::vector<char>> m_grid;
	std::vector<std::vector<int>> m_visited;

	int m_height;
	int m_weidth;

	// private func
	sf::Vector2f getPosOnMat(DynamicObject*);
	size_t getDirectionSmart(sf::Vector2f, sf::Vector2f);
	void buildVisited();
	
	//bool isInMyRow();
};