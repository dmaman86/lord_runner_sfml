#include "Board.h"
#include <ctype.h>

Board::Board() : m_level_one(true)
{
    // initTextures();
	m_player = nullptr;
}

Board::~Board() 
{
}

std::unique_ptr<DynamicObject> Board::createDynamicObject
(ObjectType::ID type, sf::Vector2f pos, sf::Vector2f size, TextureHolder& textures,Player * player)
{
	switch (type)
	{
	case ObjectType::MonsterChar:
		int r = rand() % KindMonsters::Max;
		switch (KindMonsters::Rand)
		{
		case KindMonsters::Rand:
			return std::make_unique<MonsterRand>(pos, size, &textures.get(Textures::MonsterRand));
		case KindMonsters::Horizontal:
			return std::make_unique<MonsterHorizontal>(pos, size, &textures.get(Textures::MonsterRL));
		case KindMonsters::Smart:
			return std::make_unique<MonsterSmart>
				(pos, size, &textures.get(Textures::MonsterSmart),player);
		}
	}
	return nullptr;
}

std::unique_ptr<StaticObject> Board::createStaticObject(ObjectType::ID type, sf::Vector2f pos, sf::Vector2f size, TextureHolder& textures)
{
	switch (type)
	{
	case ObjectType::FloorChar:
		return std::make_unique<Floor>(pos, size, &textures.get(Textures::Wall));
	case ObjectType::RopesChar:
		return std::make_unique<Ropes>(pos, size, &textures.get(Textures::Ropes));
	case ObjectType::LadderChar:
		return std::make_unique<Ladder>(pos, size, &textures.get(Textures::Ladder));
	case ObjectType::CoinChar:
		m_location_add_monster = pos;
		return std::make_unique<Coin>(pos, size, &textures.get(Textures::Coin));
	case ObjectType::GiftChar:
		int r = rand() % KindGifts::Max;
		switch (r)
		{
		case KindGifts::Life:
			return std::make_unique<GiftLife>(pos, size, &textures.get(Textures::Gifts));
		case KindGifts::Time:
			return std::make_unique<GiftTime>(pos, size, &textures.get(Textures::Gifts));
		case KindGifts::Score:
			return std::make_unique<GiftScore>(pos, size, &textures.get(Textures::Gifts));
		case KindGifts::Monster:
			return std::make_unique<GiftMonster>(pos, size, &textures.get(Textures::Gifts));
		case KindGifts::Stain:
			return std::make_unique<GiftStain>(pos, size, &textures.get(Textures::Gifts));
		}
	}
	return nullptr;
}


void Board::initSizeData(size_t y, size_t x )
{
	m_avgPix.x = (COLL_GAME_SCREEN / (float)x);
	m_avgPix.y = (ROW_GAME_SCREEN / (float)y);
	
	m_height = y;
	m_weidth = x;

	m_grid.resize(y);

	for (int i = 0; i < y;i++)
		m_grid[i].resize(x);
}

void Board::createObject(sf::Vector2f pos, ObjectType::ID type, TextureHolder& textures, Player* player)
{
	/*if (type == ObjectType::PlayerChar)
	{
		// to do - level one only!
		m_player = createDynamicObject(type, pos, m_avgPix, textures);
		return;
	}*/

	std::unique_ptr<DynamicObject> movable = createDynamicObject(type,pos, m_avgPix, textures,player);
	if (movable)
	{
		m_monsters.push_back(std::move(movable));
	//	if (!m_player2 )
	//		m_player2 = (Player*)m_monsters[m_monsters.size() - 1].get();
		
		return;
	}

	std::unique_ptr<StaticObject> unmovable = createStaticObject(type, pos, m_avgPix, textures);
	if (unmovable)
	{
		m_grid[(int)pos.y][(int)pos.x] = (char)type;
		m_static_obj.push_back(std::move(unmovable));
		return;
	}

//	std::cerr << "Unrecognized char in the file: " << type << std::endl;
//	exit(EXIT_FAILURE);

	/*
	if( isspace( c ) || iscntrl( c ) || c == '\0' )
	    return;
	if (c == '@')
	{
		if (m_player)
		{
			Player* p = dynamic_cast <Player*> (&*this->m_player);
			if (p) {
				p->newData(pos, m_avgPix);
			}
		}
		else {
			m_player = std::make_unique< Player >(pos, m_avgPix, &textures.get(Textures::Player));
		}
	}
	if (c == '%')
	{
		m_monsters.push_back(std::make_unique< Monster >(pos, m_avgPix, &textures.get(Textures::Monster)));
	}
	else if (c == '-')
	{
		m_static_obj.push_back(std::make_unique< Ropes >(pos, m_avgPix, &textures.get(Textures::Ropes)));
	}
	else if (c == 'H')
	{
		m_static_obj.push_back(std::make_unique< Ladder >(pos, m_avgPix, &textures.get(Textures::Ladder)));
	}
	else if (c == '#')
	{
		m_static_obj.push_back(std::make_unique< Floor >(pos, m_avgPix, &textures.get(Textures::Wall)));
	}
	else if (c == '*')
	{
		m_static_obj.push_back(std::make_unique< Coin >(pos, m_avgPix, &textures.get(Textures::Coin)));
	}
	*/
}

void Board::startLevelAgain()
{
	for (int i = 0; i < m_monsters.size();i++)
	{
		m_monsters[i]->setFirstPos();
	}
	for (int i = 0;i < m_static_obj.size();i++)
	{
		m_static_obj[i]->resetExist();
	}
}

void Board::digIn(sf::Time time, sf::Vector2f pos,const sf::Sprite & spr)
{
	/*
	sf::Sprite sHelper(spr);
	sHelper.setPosition(pos);
	sHelper.setScale(0.05,0.05);
	*/
	for (int i = 0;i < m_static_obj.size();i++)
	{
		if (m_static_obj[i]->collisionWithDig(pos))
		{
			m_static_obj[i]->digMe(time);
		}
	}
}

bool Board::releaseDisappears(sf::Time time,const sf::Vector2f pos)
{	
	bool dead = false;
	for (int i = 0;i < m_static_obj.size();i++)
	{
		if (m_static_obj[i]->digMeFree(time, pos))
			dead = true;
	}
	return dead;
}

void Board::update(const float& dt,Player* player)
{
	this->updateCreature(dt, *player);
	this->updateMonsters(dt);
	this->collisionsDynamic(*player);
}

void Board::newLevel()
{
	this->m_monsters.clear();
	this->m_static_obj.clear();
}

void Board::updateMonsterData()
{
	for (int i = 0; i < m_monsters.size();i++)
	{
		m_monsters[i]->setGrid(m_grid);
	}
}
sf::Vector2f Board::getSize()
{
	return this->m_avgPix;
}

void Board::collisionsStatic(DynamicObject& creature)
{
	for (int i = 0; i < m_static_obj.size();i++)
	{
		if (m_static_obj[i]->collisionWith(creature))
			m_static_obj[i]->handleColision(creature);
	}
}

void Board::collisionsDynamic(DynamicObject& creature)
{
	for (int i = 0; i < m_monsters.size();i++)
	{
		if (m_monsters[i]->collisionWith(creature))
			m_monsters[i]->handleColision(creature);
	}
}

sf::Vector2f Board::getPlaceToAddMon()
{
	return m_location_add_monster;
}


bool Board::HaveSomthingToStand(DynamicObject& creacure)
{
	for (int i = 0; i < m_static_obj.size();i++)
	{
		if (m_static_obj[i]->collisionWithStand(creacure,m_avgPix))
			return true;
	}
		
	return false;
}

bool Board::isInRange(DynamicObject& dynObj)
{
/*
	if ( m_avgPix.x / 2u - 4.5 < dynObj.getSprite().getPosition().x
	  && m_avgPix.y / 2u  - 4.5 < dynObj.getSprite().getPosition().y
	  && COLL_GAME_SCREEN - ( m_avgPix.y / 2u) > dynObj.getSprite().getPosition().x
	  && ROW_GAME_SCREEN - (m_avgPix.x / 4u) > dynObj.getSprite().getPosition().y )
		return true;
	return false;
	*/
	if (m_avgPix.x / 2u - 4.5 < dynObj.getSprite().getPosition().x
		&& m_avgPix.y / 2u - 4.5 < dynObj.getSprite().getPosition().y
		&& COLL_GAME_SCREEN - (m_avgPix.y / 2u) > dynObj.getSprite().getPosition().x
		&& ROW_GAME_SCREEN  > dynObj.getSprite().getPosition().y)
		return true;
	return false;
}


void Board::updateCreature(const float& dt, DynamicObject& creacure)
{
	creacure.resetData();
	creacure.updateDirection(dt);

	if(!HaveSomthingToStand(creacure))
		creacure.setDirectionDown();

	creacure.move(dt);

	if (!isInRange(creacure))
		creacure.goBack();

//	collisionsDynamic(creacure);
	collisionsStatic(creacure);
}

void Board::updateMonsters(const float& dt)
{
	for (int i = 0; i < m_monsters.size();i++)
	{
		this->updateCreature(dt, *m_monsters[i]);
	}
}

void Board::renderMonster(sf::RenderWindow* target)
{
	for (int i = 0; i < m_monsters.size();i++)
		m_monsters[i]->render(target);
}

void Board::renderStaticObj(sf::RenderWindow* window)
{
	for (int i = 0; i < m_static_obj.size();i++)
		m_static_obj[i]->render(window);
}