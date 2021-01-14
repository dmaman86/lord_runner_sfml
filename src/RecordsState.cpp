#include "RecordsState.h"
#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"

#include <SFML/Graphics/RenderWindow.hpp>


RecordsState::RecordsState(StateStack& stack, Context context)
	: State(stack, context)
{
	m_backToMenu = false;
	mBackgroundSprite.setTexture(context.textures->get(Textures::Menu));
	m_soundState.setBuffer(context.sounds->get(SoundEffect::Menu));

	m_soundState.play();
}

void RecordsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
}

bool RecordsState::update(double dt)
{
	if (m_backToMenu)
	{
		m_soundState.stop();
		requestStackPop();
		requestStackPush(States::Menu);
	}
	return true;
}

bool RecordsState::handleEvent(const sf::Event& event)
{
	if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_backToMenu = true;
	}
	return true;
}
