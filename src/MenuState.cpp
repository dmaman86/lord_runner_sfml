#include "MenuState.h"
#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"
#include "InputManager.h"
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
{
	m_isPlayButtonSelected = false;
	m_isPlayButtonPressed = false;
	m_isSettingsButtonSelected = false;
	m_isSettingsButtonPressed = false;
	m_isAboutOurSelected = false;
	m_isAboutOurPressed = false;
	m_isRecordsPressed = false;
	m_isRecordsSelected = false;

	sf::Vector2u textureSize, windowSize;

	windowSize = context.window->getSize();
	textureSize = context.textures->get(Textures::Menu).getSize();

	sf::Texture& texture = context.textures->get(Textures::Menu);
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale((float)windowSize.x / textureSize.x,
								(float)windowSize.y / textureSize.y);

	m_sound.setBuffer(context.sounds->get(SoundEffect::Button));
	m_sound.setPlayingOffset(sf::seconds(2.f));
	m_soundState.setBuffer(context.sounds->get(SoundEffect::Menu));
	m_soundState.setLoop(true);

	sf::Text text;
	sf::Font& font = context.fonts->get(Fonts::Main);
	m_title.setFont(font);
	m_title.setString("Lord Runner Game");
	m_title.setFillColor(sf::Color(76,0,153));
	m_title.setCharacterSize(100);
	centerOrigin(m_title);
	m_title.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
	text.setFont(font);
	text.setCharacterSize(55);
	text.setStyle(sf::Text::Bold);

	for (size_t i = 0; i < 4; i++)
	{
		m_buttons.push_back(text);
		m_buttons[i].setFillColor(sf::Color::White);

		m_buttons[i].setOrigin(m_buttons[i].getLocalBounds().width / 2,
			m_buttons[i].getLocalBounds().height / 2);
		m_buttons[i].setPosition(sf::Vector2f(windowSize.x / 2.5,
			(windowSize.y / 2) + (i * 100)));
	}

	m_buttons[0].setString("Play Game");
	m_buttons[1].setString("Settings Game");
	m_buttons[2].setString("About Our");
	m_buttons[3].setString("Top Scores");

	m_soundState.play();
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);

	window.draw(m_title);

	for (auto button : m_buttons)
		window.draw(button);
}

bool MenuState::update(double dt)
{
	if (m_pressed)
	{
		updateColorButton();
		// m_clock.restart();
		if (m_clock.getElapsedTime().asSeconds() > 3.0)
		{
			m_pressed = false;
			if (m_isPlayButtonSelected)
			{
				requestStackPop();
				requestStackPush(States::Game);
			}
			else if (m_isSettingsButtonSelected)
			{
				requestStackPop();
				requestStackPush(States::Settings);
			}
			else if (m_isAboutOurSelected)
			{
				requestStackPop();
				requestStackPush(States::AboutOur);
			}
			else if (m_isRecordsSelected)
			{
				requestStackPop();
				requestStackPush(States::Records);
			}
		}
	}
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
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

		if (m_isPlayButtonPressed = input->isSpriteClicked(m_buttons[0], sf::Mouse::Left, window))
		{
			m_isPlayButtonSelected = true;
			m_isSettingsButtonSelected = false;
			m_isAboutOurSelected = false;
			m_isRecordsSelected = false;
			m_pressed = true;
			m_sound.play();
		}

		if (m_isSettingsButtonPressed = input->isSpriteClicked(m_buttons[1], sf::Mouse::Left, window))
		{
			m_isSettingsButtonSelected = true;
			m_isPlayButtonSelected = false;
			m_isAboutOurSelected = false;
			m_isRecordsSelected = false;
			m_pressed = true;
			m_sound.play();
		}


		if (m_isAboutOurPressed = input->isSpriteClicked(m_buttons[2], sf::Mouse::Left, window))
		{
			m_isAboutOurSelected = true;
			m_isPlayButtonSelected = false;
			m_isSettingsButtonSelected = false;
			m_isRecordsSelected = false;
			m_pressed = true;
			m_sound.play();
		}

		if (m_isRecordsPressed = input->isSpriteClicked(m_buttons[3], sf::Mouse::Left, window))
		{
			m_isAboutOurSelected = false;
			m_isPlayButtonSelected = false;
			m_isSettingsButtonSelected = false;
			m_isRecordsSelected = true;
			m_pressed = true;
			m_sound.play();
		}
		return true;
	}
	return false;
}

void MenuState::centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
		std::floor(bounds.top + bounds.height / 2.f));
}

void MenuState::updateColorButton()
{
	if (m_isPlayButtonSelected)
	{
		m_buttons[0].setFillColor(sf::Color::Black);
		m_buttons[1].setFillColor(sf::Color::White);
		m_buttons[2].setFillColor(sf::Color::White);
		m_buttons[3].setFillColor(sf::Color::White);

	}
	else if (m_isSettingsButtonSelected)
	{
		m_buttons[0].setFillColor(sf::Color::White);
		m_buttons[1].setFillColor(sf::Color::Black);
		m_buttons[2].setFillColor(sf::Color::White);
		m_buttons[3].setFillColor(sf::Color::White);

	}
	else if (m_isAboutOurSelected)
	{
		m_buttons[0].setFillColor(sf::Color::White);
		m_buttons[1].setFillColor(sf::Color::White);
		m_buttons[2].setFillColor(sf::Color::Black);
		m_buttons[3].setFillColor(sf::Color::White);
	}
	else if (m_isRecordsSelected)
	{
		m_buttons[0].setFillColor(sf::Color::White);
		m_buttons[1].setFillColor(sf::Color::White);
		m_buttons[2].setFillColor(sf::Color::White);
		m_buttons[3].setFillColor(sf::Color::Black);
	}
}
