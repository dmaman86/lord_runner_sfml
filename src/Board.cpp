#include "Board.h"

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
	if (c == ' ' || c == '\n')
		return;
	if (c == '@')
	{

	    m_player = std::make_unique< Player >( pos, m_avgPix,
                                            &m_textures.GetTexture( "Player Texture" ) );
		// m_player = std::make_unique <Player>(pos, m_avgPix, m_pic.getTxt(0));
	}
	if (c == '%')
	{

	    m_monsters.push_back( std::make_unique< Monster >( pos, m_avgPix,
                                                        &m_textures.GetTexture( "Monster Texture" ) ) );
		// m_monsters.push_back(std::make_unique <Monster>(pos, m_avgPix, m_pic.getTxt(1)));
	}
	else if (c == '-')
	{
        m_static_obj.push_back( std::make_unique< Ropes >( pos, m_avgPix,
                                                           &m_textures.GetTexture( "Ropes Texture" ) ) );
		// m_static_obj.push_back(std::make_unique <Ropes>(pos, m_avgPix, m_pic.getTxt(4)));
	}
	else if (c == 'H')
	{
		// m_static_obj.push_back(std::make_unique <Ladder>(pos, m_avgPix, m_pic.getTxt(5)));
        m_static_obj.push_back( std::make_unique< Ladder >( pos, m_avgPix,
                                                           &m_textures.GetTexture( "Ladder Texture" ) ) );
	}
	else if (c == '#')
	{
		// m_static_obj.push_back(std::make_unique <Flor>(pos, m_avgPix, m_pic.getTxt(3)));
        m_static_obj.push_back( std::make_unique< Flor >( pos, m_avgPix,
                                                           &m_textures.GetTexture( "Floor Texture" ) ) );
	}
	else if (c == '*')
	{
		// m_static_obj.push_back(std::make_unique <Coin>(pos, m_avgPix, m_pic.getTxt(2)));
        m_static_obj.push_back( std::make_unique< Coin >( pos, m_avgPix,
                                                           &m_textures.GetTexture( "Coin Texture" ) ) );
	}

}

void Board::update(const float& dt)
{
	this->updateCreature(dt,*this->m_player);
	this->updateMonsters(dt);
}

void Board::collisionsStatic(Creature& creature)
{
	for (int i = 0; i < m_static_obj.size();i++)
	{
		if (m_static_obj[i]->collisionWith(creature))
			m_static_obj[i]->handleColision(creature);
	}
}

bool Board::HaveSomthingToStand(Creature& creacure)
{
	bool b = false;
	for (int i = 0; i < m_static_obj.size();i++)
	{
		if (m_static_obj[i]->collisionWithStand(creacure,m_avgPix))
			b = true;
	}
		
	return b;
}

/*
bool Board::HaveSomthingToStand(Creature* creacure)
{
	bool b = false;
	for (int i = 0; i < m_static_obj.size();i++)
	{	
		if (m_static_obj[i]->collisionWithStand
		(creacure->getPositionRec(), this->m_avgPix))
			b = true;
	}
	if(!b)
		creacure->setDir();
	return b;
}
*/
void Board::updateCreature(const float& dt, Creature& creacure)
{
	creacure.resetData();
	creacure.setDirection();

	if(!HaveSomthingToStand(creacure))
		creacure.setDir();
	creacure.move(dt);


	collisionsStatic(creacure);

	creacure.resetDirection();
}
/*
void Board::updateCreature(const float& dt, Creature* creacure)
{
	creacure->setDirection();

	sf::Sprite helper = creacure->getRecNextStep(dt);

	if (!collisionFlor(helper))
		creacure->move(dt);

	creacure->resetDirection();
}
*/



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
    m_textures.LoadTexture( "Player Texture", "hero.png" );
    m_textures.LoadTexture( "Monster Texture", "monster.png" );
    m_textures.LoadTexture( "Ropes Texture", "ropes.png" );
    m_textures.LoadTexture( "Coin Texture", "coin.png" );
    m_textures.LoadTexture( "Floor Texture", "wall.png" );
    m_textures.LoadTexture( "Ladder Texture", "ladder.png" );
}