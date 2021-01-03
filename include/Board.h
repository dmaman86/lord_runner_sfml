#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <memory>

#include "Picture.h"
#include "StaticObj.h"
#include "Monster.h"
#include "Player.h"
#include "Creature.h"
#include "Flor.h"
#include "Ladder.h"
#include "Coin.h"
#include "Ropes.h"



class Board
{

public:
	Board();
	~Board();
	void initAvg(size_t, size_t);
	void initData(sf::Vector2f pos, char c);
	void update(const float& dt);

	
	void renderMonster(sf::RenderWindow* window);
	void renderStaticObj(sf::RenderWindow* window);
	void renderPlayer(sf::RenderWindow* window);


private:
	//std::vector<Monster*> m_monsters;
	std::vector<std::unique_ptr<Creature>> m_monsters;

	
	//std::vector<StaticObj*> m_static_obj;
	std::vector<std::unique_ptr<StaticObj>> m_static_obj;

	
	Picture m_pic;

	
	//Player m_player;
	std::unique_ptr<Creature> m_player;
	sf::Vector2f m_avgPix;

	void updateMonsters(const float& dt);
	void updateCreature(const float& dt, Creature& creacure);
	//bool collisionFlor(sf::RectangleShape rec);
	void collisionsStatic(Creature& rec);
	bool HaveSomthingToStand(Creature& creacure);


};