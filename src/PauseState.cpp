#include "PauseState.h"
#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
	, mBackgroundSprite()
	, mPausedText()
{
	m_isBackMenuSelected = false;
	m_isBackMenuPressed = false;
	m_isResetGameSelected = false;
	m_isResetGamePressed = false;
	m_backToGameSelected = false;
	m_backToGamePressed = false;
	m_pressed = false;

	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mPausedText.setFont(font);
	mPausedText.setString("Game Paused");
	mPausedText.setCharacterSize(100);
	mPausedText.setFillColor(sf::Color(76, 0, 153));
	centerOrigin(mPausedText);
	mPausedText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(55);
	text.setStyle(sf::Text::Bold);
	for (size_t i = 0; i < 3; i++)
	{
		m_buttons.push_back(text);
		m_buttons[i].setFillColor(sf::Color::White);
		m_buttons[i].setOrigin(m_buttons[i].getLocalBounds().width / 2,
			m_buttons[i].getLocalBounds().height / 2);
		m_buttons[i].setPosition(sf::Vector2f(windowSize.x / 2.5,
			(windowSize.y / 2) + (i * 100)));
	}
	m_buttons[0].setString("Back to Game");
	m_buttons[1].setString("Back Menu Game");
	m_buttons[2].setString("Restart Game");

	m_sound.setBuffer(context.sounds->get(SoundEffect::Button));
	m_soundState.setBuffer(context.sounds->get(SoundEffect::Menu));
	m_soundState.setLoop(true);
	m_soundState.play();
}

PauseState::~PauseState()
{
	m_soundState.stop();
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPausedText);

	for (auto button : m_buttons)
		window.draw(button);
}

bool PauseState::update(double dt)
{
	if (m_pressed)
	{
		updateColorButton();
		m_pressed = false;
		// m_clock.restart();
		if (m_clock.getElapsedTime().asSeconds() > 2.0)
		{
			if (m_backToGameSelected)
			{
				requestStackPop();
			}
			else if (m_isBackMenuSelected)
			{
				requestStateClear();
				requestStackPush(States::Menu);
			}
			else if (m_isResetGameSelected)
			{
				requestStackPop();
				requestStackPush(States::Game);
			}
		}
	}
	return true;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	sf::RenderWindow& window = *getContext().window;
	InputManager* input = getContext().input;
	if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_soundState.stop();
		requestStackPop();
	}

	if (event.MouseButtonPressed)
	{

		if (m_backToGamePressed = input->isSpriteClicked(m_buttons[0], sf::Mouse::Left, window))
		{
			m_backToGameSelected = true;
			m_isBackMenuSelected = false;
			m_isResetGameSelected = false;
			m_pressed = true;
			m_sound.play();
		}

		if (m_isBackMenuPressed = input->isSpriteClicked(m_buttons[1], sf::Mouse::Left, window))
		{
			m_backToGameSelected = false;
			m_isBackMenuSelected = true;
			m_isResetGameSelected = false;
			m_pressed = true;
			m_sound.play();
		}


		if (m_isResetGamePressed = input->isSpriteClicked(m_buttons[2], sf::Mouse::Left, window))
		{
			m_isBackMenuSelected = false;
			m_backToGameSelected = false;
			m_isResetGameSelected = true;
			m_pressed = true;
			m_sound.play();
		}
		return true;
	}
	return false;
}

void PauseState::centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
		std::floor(bounds.top + bounds.height / 2.f));
}

void PauseState::updateColorButton()
{
	if (m_backToGameSelected)
	{
		m_buttons[0].setFillColor(sf::Color::Black);
		m_buttons[1].setFillColor(sf::Color::White);
		m_buttons[2].setFillColor(sf::Color::White);
	}
	else if (m_isBackMenuSelected)
	{
		m_buttons[0].setFillColor(sf::Color::White);
		m_buttons[1].setFillColor(sf::Color::Black);
		m_buttons[2].setFillColor(sf::Color::White);
	}
	else if (m_isResetGameSelected)
	{
		m_buttons[0].setFillColor(sf::Color::White);
		m_buttons[1].setFillColor(sf::Color::White);
		m_buttons[2].setFillColor(sf::Color::Black);
	}
}
