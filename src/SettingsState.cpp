#include "SettingsState.h"
#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"

#include <SFML/Graphics/RenderWindow.hpp>


SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context)
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
}

bool SettingsState::update(double dt)
{
	return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;

	return false;
}

void SettingsState::updateLabels()
{
	
}

void SettingsState::addButtonLabel(float y, const std::string& text, Context context)
{
	
}
