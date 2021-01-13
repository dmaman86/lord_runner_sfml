#include "Board.h"

#include <ctype.h>

Board::Board()
{
    // initTextures();
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


void Board::initAvg(size_t y, size_t x )
{
	m_avgPix.x = (COLL_GAME_SCREEN / (float)x);
	m_avgPix.y = (ROW_GAME_SCREEN / (float)y);
}

void Board::initData(sf::Vector2f pos, char c, TextureHolder& textures)
{
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
}


void Board::playerCheckInjured()
{
	Player* p = dynamic_cast <Player*> (&*this->m_player);
	if (p) {
		if (p->isInjured())
		{
			m_player->setFirstPos();
			for (int i = 0; i < m_monsters.size();i++)
			{
				m_monsters[i]->setFirstPos();
			}
			for (int i = 0;i < m_static_obj.size();i++)
			{
				m_static_obj[i]->resetExist();
			}
		}
	}
}

void Board::update(const float& dt)
{
	this->updateCreature(dt,*this->m_player);
	this->collisionsDynamic(*this->m_player);
	this->playerCheckInjured();
	this->updateMonsters(dt);
	//this->collisionsDynamic(*this->m_player);
}

int Board::getCoinCount()
{
	Player* p = dynamic_cast <Player*> (&*this->m_player);
	if (p) {
		return p->getCoinCollected();
	}
	return 0;
}
void Board::newLevel()
{
	this->m_monsters.clear();
	this->m_static_obj.clear();
//	Player* p = dynamic_cast <Player*> (&*this->m_player);
//	if (p) {
//		p->newLevel();
//	}
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


bool Board::HaveSomthingToStand(DynamicObject& creacure)
{
	bool b = false;
	for (int i = 0; i < m_static_obj.size();i++)
	{
		if (m_static_obj[i]->collisionWithStand(creacure,m_avgPix))
			b = true;
	}
		
	return b;
}

bool Board::isInRange(DynamicObject& dynObj)
{
	if (m_avgPix.x / 2u - 4.5 < dynObj.getSprite().getPosition().x
		&&m_avgPix.y / 2u  - 4.5 < dynObj.getSprite().getPosition().y
		&& 
		COLL_GAME_SCREEN - (m_avgPix.x / 2u) > dynObj.getSprite().getPosition().x
		&& ROW_GAME_SCREEN - (m_avgPix.y / 2u) > dynObj.getSprite().getPosition().y)
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
	m_player->render(window);
}

void Board::renderStatus(sf::RenderWindow* window)
{
	sf::Texture txt;
	txt.loadFromFile("heart.png");
	sf::Sprite heart;
	heart.setTexture(txt);

	heart.setScale(0.15,0.15);

	heart.setPosition(0 , ROW_GAME_SCREEN + (m_avgPix.y / 2u));

	Player* p = dynamic_cast <Player*> (&*this->m_player);
	if (p) {

		for (int i = 0; i < p->getLife();i++)
		{
			heart.setPosition(i * 100, ROW_GAME_SCREEN + (m_avgPix.y / 2u) );
			window->draw(heart);
		}
	}
}
