#include "AboutOurState.h"

#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"
#include "InputManager.h"
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

AboutOurState::AboutOurState(StateStack& stack, Context context)
	: State(stack, context), m_backToMenu(false)
{
	sf::Vector2u textureSize, windowSize;

	windowSize = context.window->getSize();
	textureSize = context.textures->get(Textures::Menu).getSize();

	sf::Texture& texture = context.textures->get(Textures::Menu);
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale((float)windowSize.x / textureSize.x,
		(float)windowSize.y / textureSize.y);

	m_soundState.setBuffer(context.sounds->get(SoundEffect::Menu));
	m_soundState.setLoop(true);
	
	sf::Font& font = context.fonts->get(Fonts::Main);
	m_title.setFont(font);
	m_title.setString("About Our");
	m_title.setFillColor(sf::Color(76, 0, 153));
	m_title.setCharacterSize(100);
	centerOrigin(m_title);
	m_title.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

	m_soundState.play();
}

void AboutOurState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);

	window.draw(m_title);
}

bool AboutOurState::update(double dt)
{
	if (m_backToMenu)
	{
		m_backToMenu = false;
		m_soundState.stop();
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}

bool AboutOurState::handleEvent(const sf::Event& event)
{
	if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_backToMenu = true;
	}
	return true;
}

void AboutOurState::centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
		std::floor(bounds.top + bounds.height / 2.f));
}

