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
	m_soundState.setBuffer(context.sounds->get(SoundEffect::Menu));
	m_soundState.setLoop(true);

	sf::Text text;
	sf::Font& font = context.fonts->get(Fonts::Main);
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
	m_buttons[3].setString("Records Game");

	m_soundState.play();
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);

	for (auto button : m_buttons)
		window.draw(button);
}

bool MenuState::update(double dt)
{
	if (m_pressed)
	{
		updateColorButton();
		m_pressed = false;
		// m_clock.restart();
		if (m_clock.getElapsedTime().asSeconds() > 2.0)
		{
			if (m_isPlayButtonSelected)
			{
				requestStackPop();
				requestStackPush(States::Game);
			}
			else if (m_isSettingsButtonSelected)
			{
				std::cout << "Go to Setting Screen" << std::endl;
			}
			else if (m_isAboutOurSelected)
			{
				std::cout << "Go to About Out Screen" << std::endl;
			}
			else if (m_isRecordsSelected)
			{
				std::cout << "Go to Records Screen" << std::endl;
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
