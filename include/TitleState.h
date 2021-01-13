#pragma once

#include "./Machine/State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>


class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(double dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Sprite			mBackgroundSprite;
	sf::Text			mText;
	sf::Sound mSound;
	sf::Clock mClock;

	bool				mShowText;
	double			mTextEffectTime;
};