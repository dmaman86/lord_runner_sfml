#pragma once

#include <fstream>
//#include <vector>
#include <experimental/vector>

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

#include "Resources/ResourceHolder.h"
#include "Resources/ResourceIdentifiers.h"

/*enum ObjectType
{
	PlayerChar = '@',
	MonsterChar = '%',
	FloorChar = '#',
	RopesChar = '-',
	LadderChar = 'H',
	CoinChar = '*'
};*/


class Board
{

public:
	Board();
	~Board();
	void initAvg(size_t, size_t);
	// void createObject(sf::Vector2f pos, ObjectType type, TextureHolder& textures );
	void createObject(sf::Vector2f pos, ObjectType::ID type, TextureHolder& textures);
	void update(const float& dt, Player* player);
	void newLevel();
	
	void startLevelAgain();

	void digIn(sf::Time time,sf::Vector2f pos, const  sf::Sprite&);
	void releaseDisappears(sf::Time time);

	sf::Vector2f getPlaceToAddMon();


	sf::Vector2f getSize();


	void renderMonster(sf::RenderWindow* window);
	void renderStaticObj(sf::RenderWindow* window);
	void renderPlayer(sf::RenderWindow* window);
	void renderStatus(sf::RenderWindow* window);


private:
	//std::vector<Monster*> m_monsters;
	std::vector<std::unique_ptr<DynamicObject>> m_monsters;

	bool m_level_one;

	sf::Vector2f m_location_add_monster;

	//std::vector<StaticObj*> m_static_obj;
	std::vector<std::unique_ptr<StaticObject>> m_static_obj;

	
	//Player* m_player2;

	std::unique_ptr<DynamicObject> m_player;
	sf::Vector2f m_avgPix;


	// std::unique_ptr<StaticObject> createStaticObject(ObjectType type, sf::Vector2f pos, sf::Vector2f size, TextureHolder& textures);
	std::unique_ptr<StaticObject> createStaticObject(ObjectType::ID type, sf::Vector2f pos, sf::Vector2f size, TextureHolder& textures);

	// std::unique_ptr<DynamicObject> createDynamicObject(ObjectType type, sf::Vector2f pos, sf::Vector2f size, TextureHolder& textures);
	std::unique_ptr<DynamicObject> createDynamicObject(ObjectType::ID type, sf::Vector2f pos, sf::Vector2f size, TextureHolder& textures);

	void updateMonsters(const float& dt);
	void updateCreature(const float& dt, DynamicObject& creacure);
	//bool collisionFlor(sf::RectangleShape rec);
	void collisionsStatic(DynamicObject& rec);
	void collisionsDynamic(DynamicObject& rec);


	bool HaveSomthingToStand(DynamicObject& creacure);
	bool isInRange(DynamicObject& creacure);


	// void initTextures();


};



