#include "Board.h"

#include <ctype.h>

Board::Board()
{
    initTextures();
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

void Board::initData(sf::Vector2f pos, char c)
{
	if( isspace( c ) || iscntrl( c ) || c == '\0' )
	    return;
	if (c == '@')
	{
        m_player = std::make_unique< Player >( pos, m_avgPix,
                                               &m_textures.GetTexture( Textures::Player ) );
	}
	if (c == '%')
	{
        m_monsters.push_back( std::make_unique< Monster >( pos, m_avgPix,
                                                           &m_textures.GetTexture( Textures::Monster ) ) );
	}
	else if (c == '-')
	{
        m_static_obj.push_back( std::make_unique< Ropes >( pos, m_avgPix,
                                                           &m_textures.GetTexture( Textures::Ropes ) ) );
	}
	else if (c == 'H')
	{
        m_static_obj.push_back( std::make_unique< Ladder >( pos, m_avgPix,
                                                            &m_textures.GetTexture( Textures::Ladder ) ) );
	}
	else if (c == '#')
	{
        m_static_obj.push_back( std::make_unique< Floor >( pos, m_avgPix,
                                                           &m_textures.GetTexture( Textures::Floor ) ) );
	}
	else if (c == '*')
	{
        m_static_obj.push_back( std::make_unique< Coin >( pos, m_avgPix,
                                                          &m_textures.GetTexture( Textures::Coin ) ) );
	}
}

void Board::update(const float& dt)
{
	this->updateCreature(dt,*this->m_player);
	this->collisionsDynamic(*this->m_player);
	
	
	Player* p = dynamic_cast <Player*> (&*this->m_player);
	if (p->isInjured())
	{
		m_player->setFirstPos();
		for (int i = 0; i < m_monsters.size();i++)
		{
			m_monsters[i]->setFirstPos();
		}
	}


	this->updateMonsters(dt);
	//this->collisionsDynamic(*this->m_player);
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

bool Board::isInRange(DynamicObject& creacure)
{
	if ( 0 + m_avgPix.x / 2u < creacure.getPositionRec().x
		&& 0 + m_avgPix.y / 2u < creacure.getPositionRec().y
		&& COLL_GAME_SCREEN - ( m_avgPix.x / 2u  )> creacure.getPositionRec().x
	    && ROW_GAME_SCREEN - ( m_avgPix.y / 2u  )> creacure.getPositionRec().y )
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

void Board::renderStaticObj(sf::RenderWindow* target)
{
	for (int i = 0; i < m_static_obj.size();i++)
		m_static_obj[i]->render(target);
}

void Board::renderPlayer(sf::RenderWindow* target)
{
	m_player->render(target);
}


void Board::initTextures()
{
    m_textures.LoadTexture( Textures::Player, "hero.png" );
    m_textures.LoadTexture( Textures::Monster, "monster.png" );
    m_textures.LoadTexture( Textures::Ropes, "ropes.png" );
    m_textures.LoadTexture( Textures::Coin, "coin.png" );
    m_textures.LoadTexture( Textures::Floor, "wall.png" );
    m_textures.LoadTexture( Textures::Ladder, "ladder.png" );
}