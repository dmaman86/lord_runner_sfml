#include "Board.h"
#include <ctype.h>

Board::Board() : m_level_one(true)
{
    // initTextures();
	m_player = nullptr;
	srand((unsigned int)time(NULL));
}

Board::~Board() 
{
	// unice ptr :
	// no new - no delete data 

	/*for (int i = 0; i < m_monsters.size();i++)
	{
		delete m_monsters[i];
	}*/
}


std::unique_ptr<DynamicObject> Board::createDynamicObject
(ObjectType::ID type, sf::Vector2f pos, sf::Vector2f size, TextureHolder& textures,Player * player)
{
	switch (type)
	{
		// case ObjectType::PlayerChar:
			// return std::make_unique<Player>(pos, size, &textures.get(Textures::Player));
	case ObjectType::MonsterChar:
		int r = rand() % 3;
		switch (2)
		{
		case 0:
			return std::make_unique<MonsterRand>(pos, size, &textures.get(Textures::MonsterRand));
		case 1:
			return std::make_unique<MonsterHorizontal>(pos, size, &textures.get(Textures::MonsterRL));
		case 2:
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
		int r = rand() % 5;
		switch (r)
		{
		case 0:
			return std::make_unique<GiftLife>(pos, size, &textures.get(Textures::Gifts));
		case 1:
			return std::make_unique<GiftTime>(pos, size, &textures.get(Textures::Gifts));
		case 2:
			return std::make_unique<GiftScore>(pos, size, &textures.get(Textures::Gifts));
		case 3:
			return std::make_unique<GiftMonster>(pos, size, &textures.get(Textures::Gifts));
		case 4:
			return std::make_unique<GiftStain>(pos, size, &textures.get(Textures::Gifts));
		}
	}
	return nullptr;
}


void Board::initAvg(size_t y, size_t x )
{
	m_avgPix.x = (COLL_GAME_SCREEN / (float)x);
	m_avgPix.y = (ROW_GAME_SCREEN / (float)y);
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

void Board::releaseDisappears(sf::Time time)
{	
	for (int i = 0;i < m_static_obj.size();i++)
	{
		m_static_obj[i]->digMeFree(time);
	}
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
	if ( m_avgPix.x / 2u - 4.5 < dynObj.getSprite().getPosition().x
	  && m_avgPix.y / 2u  - 4.5 < dynObj.getSprite().getPosition().y
	  && COLL_GAME_SCREEN - ( m_avgPix.y / 2u) > dynObj.getSprite().getPosition().x
	  && ROW_GAME_SCREEN - (m_avgPix.x / 4u) > dynObj.getSprite().getPosition().y )
		return true;
	return false;
}

void Board::updateCreature(const float& dt, DynamicObject& creacure)
{
	creacure.resetData();
	creacure.updateDirection();

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

void Board::renderPlayer(sf::RenderWindow* window)
{
	//m_player->render(window);
}

void Board::renderStatus(sf::RenderWindow* window)
{
	/*
	sf::Texture txt;
	txt.loadFromFile("heart.png");
	sf::Sprite heart;
	heart.setTexture(txt);

	heart.setScale(0.15,0.15);

	heart.setPosition(0 , ROW_GAME_SCREEN + (m_avgPix.y / 2u));

		for (int i = 0; i < m_player2->getLife();i++)
		{
			heart.setPosition(i * 100, ROW_GAME_SCREEN + (m_avgPix.y / 2u) );
			window->draw(heart);
		}
		*/
}
