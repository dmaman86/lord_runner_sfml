#include "GameState.h"

#include <SFML/Graphics/RenderWindow.hpp>


GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
{
    m_isPause = false;
	std::ifstream fd_readLevel(getPath());
	if (fd_readLevel.is_open())
		read_data(fd_readLevel);

    mBackgroundSprite.setTexture(context.textures->get(Textures::Game));
    m_soundState.setBuffer(context.sounds->get(SoundEffect::Game));
    m_soundState.setLoop(true);
    m_sound.setBuffer(context.sounds->get(SoundEffect::Button));

    m_soundState.play();
}

void GameState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);

    m_board.renderStaticObj(&window);

    m_board.renderMonster(&window);

    m_board.renderPlayer(&window);

	m_board.renderStatus(&window);
}

bool GameState::update(double dt)
{
    m_board.update(dt); 

	// NEW - GAMESTATE.CPP
	if (Coin::getCount() == this->m_board.getCoinCount())
	{
		// next level

		this->m_numLevel++;
		this->m_board.newLevel();
		std::ifstream fd_readLevel(this->getPath());
		if (fd_readLevel.is_open())
			read_data(fd_readLevel);
	}

    if (m_isPause)
    {
        m_isPause = false;
        m_soundState.pause();
        requestStackPush(States::Pause);
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
        m_isPause = true;

	return true;
}

//Private function
std::string GameState::getPath()
{
    std::string path = "Board" + std::to_string(m_numLevel) + ".txt";
    return path;
}

void GameState::read_data(std::ifstream& fd_readLevel)
{
    size_t height, weidth;
    char c;

    fd_readLevel >> height;
    fd_readLevel >> weidth;
    this->m_board.initAvg(height, weidth);

    fd_readLevel.get(c);	//eat '\n'
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < weidth; j++)
        {
            fd_readLevel.get(c);
            m_board.initData(sf::Vector2f((float)j, (float)i), c, *getContext().textures);
        }
        fd_readLevel.get(c);	//eat '\n'
    }

    fd_readLevel.close();
}