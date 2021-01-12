#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <memory>

#include "models/StaticObject.h"
#include "models/Monster.h"
#include "models/Player.h"
#include "models/DynamicObject.h"
#include "models/Floor.h"
#include "models/Ladder.h"
#include "models/Coin.h"
#include "models/Ropes.h"
#include "Singleton/ResourceManager.h"

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
	std::vector<std::unique_ptr<DynamicObject>> m_monsters;

	
	//std::vector<StaticObj*> m_static_obj;
	std::vector<std::unique_ptr<StaticObject>> m_static_obj;

	
	//Player m_player;
	std::unique_ptr<DynamicObject> m_player;
	sf::Vector2f m_avgPix;

	void updateMonsters(const float& dt);
	void updateCreature(const float& dt, DynamicObject& creacure);
	//bool collisionFlor(sf::RectangleShape rec);
	void collisionsStatic(DynamicObject& rec);
	void collisionsDynamic(DynamicObject& rec);
	void playerCheckInjured();

	bool HaveSomthingToStand(DynamicObject& creacure);
	bool isInRange(DynamicObject& creacure);


	// void initTextures();


};