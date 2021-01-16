#include "GameState.h"
#include <Windows.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include "Resources/ResourceIdentifiers.h"
#include "Resources/ResourceHolder.h"



GameState::GameState(StateStack& stack, Context context)
	: State(stack, context),
	m_player( new Player(sf::Vector2f(0,0), sf::Vector2f(0,0) ,
	&context.textures->get(Textures::Player), &context.sounds->get(SoundEffect::PlayerCoin)) )
	, m_containerStatus(&context.textures->get(Textures::Heart), 
						&context.fonts->get(Fonts::Main)),
	m_is_race_time(true)
{
    m_isPause = false;
	m_gameover = false;
	m_gamewin = false;
	m_error = initLevel();

	m_stain.setTexture(context.textures->get(Textures::Stain));

	mBackgroundSprite.setTexture(context.textures->get(Textures::Game));
	m_soundState.setBuffer(context.sounds->get(SoundEffect::Game));
	m_soundState.setLoop(true);
	m_soundState.setVolume(100.0f);
	m_sound.setBuffer(context.sounds->get(SoundEffect::Button));

	m_soundState.play();

	m_sStartLevClock.setBuffer(context.sounds->get(SoundEffect::StartLevelClock));
	m_sStartLevClock.setVolume(40.0f);
	m_sEndLevClock.setBuffer(context.sounds->get(SoundEffect::EndTime));
	m_sEndLevClock.setVolume(40.0f);
	m_PmeetM.setBuffer(context.sounds->get(SoundEffect::PlayerDead));
	m_PmeetM.setVolume(40.0f);
	
}

GameState::~GameState()
{
	delete m_player;
}

void GameState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);

    m_board.renderStaticObj(&window);

    m_board.renderMonster(&window);

   // m_board.renderPlayer(&window);

	//m_board.renderStatus(&window);
	this->m_containerStatus.renderStatus
	(*m_player, &window, m_is_race_time,
		m_time_of_level.asSeconds() - m_level_clock.getElapsedTime().asSeconds());
	
	window.draw(m_player->getSprite());

	if (GiftStain::isActive())
		window.draw(this->m_stain);
}

void GameState::handeleDig()
{
	if (this->m_player->dig())
	{
		this->m_board.digIn(sf::Time(this->m_level_clock.getElapsedTime()),
			this->m_player->getMovementDig(m_board.getSize()), this->m_player->getSprite());
	}
	m_board.releaseDisappears(this->m_level_clock.getElapsedTime());
}

void GameState::handleRace()
{
	if (this->m_is_race_time)
	{
		// if get present that give player more time
		if (GiftTime::isActive())
			m_time_of_level += sf::seconds(5);
		else if (GiftMonster::isActive())
		{
			m_board.createObject(m_board.getPlaceToAddMon(), ObjectType::MonsterChar, *getContext().textures);
		}

		// if time end
		if (this->m_level_clock.getElapsedTime().asSeconds() > m_time_of_level.asSeconds())
		{
			m_sEndLevClock.play();

			m_player->injured();
			this->m_level_clock.restart();
			Sleep(2000);

		}
	}
}

void GameState::handleInjured()
{
	// 1.moved to func later
	if (m_player->isInjured())
	{
		if (!m_player->getLife())
		{
			m_gameover = true;
		}
		else
		{
			m_board.startLevelAgain();
			m_player->setFirstPos();
			m_PmeetM.play();
			this->m_level_clock.restart();
		}
	}
}

void GameState::handleNewLevel()
{
	if (Coin::getCount() == Coin::getCollected())
	{
		// next level
		Coin::resetCollected();
		this->m_player->newLevel();
		this->m_board.newLevel();

		if (!initLevel())
		{
			m_error = false;
		}
		else if (this->m_player->getLevel() > 6)
		{
			m_gamewin = true;
		}
		else
			this->m_level_clock.restart();

	}
}

bool GameState::update(double dt)
{
	if (!m_error)
	{
		// if something wrong with levels
		requestStackPop();
		requestStackPush(States::ErrorState);
	}
	else if (m_gamewin)
	{
		// if player win
		requestStackPop();
		requestStackPush(States::GameWin);
	}
	else if (m_gameover)
	{
		// if player lose
		requestStackPop();
		requestStackPush(States::GameOver);
	}
	else if (!m_isPause)
	{
		this->m_board.update(dt, m_player);
		this->handeleDig();
		this->handleRace();
		this->handleInjured();
		this->handleNewLevel();
	}

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        m_soundState.stop();
        getContext().window->close();
    }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		// if game pause
		pause();
		m_soundState.pause();
		requestStackPush(States::Pause);
	}
        

	return true;
}

void GameState::pause()
{
	m_isPause = true;
}

void GameState::start()
{
	m_isPause = false;
	m_soundState.play();
}

bool GameState::initLevel()
{
	std::ifstream fd_readLevel(getPath());

	if (!fd_readLevel.is_open())
		return false;
	read_data(fd_readLevel);

	return true;
}

//Private function
std::string GameState::getPath()
{
    std::string path = "Board" + std::to_string(m_player->getLevel()) + ".txt";
    return path;
}

void GameState::read_data(std::ifstream& fd_readLevel)
{
    size_t height, weidth,time;
    char c;

    fd_readLevel >> height;
    fd_readLevel >> weidth;
	fd_readLevel >> time;

	if (time != -1)
	{
		m_time_of_level = sf::seconds(time) + sf::seconds(0.5);
		m_is_race_time = true;
		m_sStartLevClock.play();
	}
	else
		m_is_race_time = false;

	this->m_board.initAvg(height, weidth);

    fd_readLevel.get(c);	//eat '\n'
    for (size_t i = 0; i < height; i++)
    {
		for (size_t j = 0; j < weidth; j++)
		{
			fd_readLevel.get(c);

			if (c == '@')
				m_player->newData(sf::Vector2f((float)j, (float)i), m_board.getSize() );
			else 
			{
				m_board.createObject(sf::Vector2f((float)j, (float)i), (ObjectType::ID)c, *getContext().textures);
			}
		}
		fd_readLevel.get(c);	//eat '\n'
    }
	
    fd_readLevel.close();
}


