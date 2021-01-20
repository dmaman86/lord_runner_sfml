#include "StartGameState.h"
#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

int StartGameState::init = 0;

StartGameState::StartGameState(StateStack& stack, Context context)
	: State(stack, context)
	, mCounterTime(0.0f)
	, m_time(0.0f)
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mBackgroundSprite.setTexture(context.textures->get(Textures::Game));

	m_titleReady.setFont(font);
	m_titleReady.setCharacterSize(50);
	centerOrigin(m_titleReady);
	m_titleReady.setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 75);
	m_titleReady.setFillColor(sf::Color::Red);
	
	m_soundState.setBuffer(context.sounds->get(SoundEffect::Menu));
	m_soundState.setLoop(true);
	m_soundState.play();

	m_clock.restart();
	m_counterdown = 3;
}

StartGameState::~StartGameState()
{
	m_soundState.stop();
	StartGameState::init = 0;
}

void StartGameState::draw()
{
	for (; init < 3;)
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());

		sf::RectangleShape backgroundShape;
		backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
		backgroundShape.setSize(window.getView().getSize());
		window.draw(mBackgroundSprite);
		window.draw(backgroundShape);
		m_titleReady.setString("Get Ready!\n\t" + std::to_string(m_counterdown - init));
		m_time += m_clock.getElapsedTime().asSeconds();

		window.draw(m_titleReady);
		window.display();
		window.clear();

		if (m_time >= 50.0f)
		{
			init++;
			m_time = 0.0f;
			m_clock.restart();
		}
	}
}

bool StartGameState::update(double dt)
{
	if (init == 3)
	{
		m_soundState.pause();
		requestStackPop();
	}
	return true;
}

bool StartGameState::handleEvent(const sf::Event& event)
{
	sf::RenderWindow& window = *getContext().window;
	InputManager* input = getContext().input;
	if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		requestStateClear();
	}

	
	return false;
}

void StartGameState::centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
		std::floor(bounds.top + bounds.height / 2.f));
}

