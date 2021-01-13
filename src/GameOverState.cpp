#include "GameOverState.h"
#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


GameOverState::GameOverState(StateStack& stack, Context context)
	: State(stack, context)
	, mGameOverText()
	, mElapsedTime(0.0f)
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mGameOverText.setFont(font);

	mGameOverText.setCharacterSize(70);
	mGameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	// Create dark, semitransparent background
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mGameOverText);
}

bool GameOverState::update(double dt)
{
	// Show state for 3 seconds, after return to menu
	mElapsedTime += dt;
	if (mElapsedTime > 3.0f)
	{
		requestStateClear();
		requestStackPush(States::Menu);
	}
	return false;
}

bool GameOverState::handleEvent(const sf::Event&)
{
	return false;
}
