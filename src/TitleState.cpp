#include "TitleState.h"
#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"

#include <SFML/Graphics/RenderWindow.hpp>


TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
	, mText()
	, mShowText(true)
	, mTextEffectTime(0.0f)
{
	sf::Vector2u textureSize, windowSize;

	windowSize = context.window->getSize();
	textureSize = context.textures->get(Textures::TitleScreen).getSize();
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	mBackgroundSprite.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);

	mSound.setBuffer(context.sounds->get(SoundEffect::Open));
	mSound.play();
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	if (mShowText)
		window.draw(mText);
}

bool TitleState::update(double dt)
{
	mTextEffectTime += dt;
	if (mTextEffectTime >= 3.0f)
	{
		mSound.stop();
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
	

	return true;
}