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
	std::ifstream fd_readLevel(getPath());
	if (fd_readLevel.is_open())
		read_data(fd_readLevel);

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
}

bool GameState::update(double dt)
{
	if (!m_isPause)
	{
		m_board.update(dt, m_player);



		if (this->m_is_race_time)
		{
			if (this->m_level_clock.getElapsedTime().asSeconds() > m_time_of_level.asSeconds())
			{
				m_sEndLevClock.play();

				m_player->injured();
				this->m_level_clock.restart();
				Sleep(2000);

			}
		}

		// 1.moved to func later
		if (m_player->isInjured())
		{
			// if(m_player->isDead())
			// gameoverState(false = lose)
			if (!m_player->getLife())
			{
				requestStackPush(States::GameOver);
			}
			m_board.startLevelAgain();
			m_player->setFirstPos();
			m_PmeetM.play();
			this->m_level_clock.restart();


		}

		// 2.moved to func later
		if (Coin::getCount() == Coin::getCollected())
		{
			// next level
			Coin::resetCollected();
			// if(m_numLevel
			// gameoverState(false = lose)
			this->m_player->newLevel();
			this->m_board.newLevel();
			std::ifstream fd_readLevel(this->getPath());
			if (fd_readLevel.is_open())
				read_data(fd_readLevel);

			this->m_level_clock.restart();

		}

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