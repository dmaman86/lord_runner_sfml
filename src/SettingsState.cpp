#include "SettingsState.h"
#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"

#include <SFML/Graphics/RenderWindow.hpp>


SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context)
{
	m_backToMenu = false;
	mBackgroundSprite.setTexture(context.textures->get(Textures::Menu));
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
}

bool SettingsState::update(double dt)
{
	if (m_backToMenu)
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}
		
	return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_backToMenu = true;
	}
	return true;
}
