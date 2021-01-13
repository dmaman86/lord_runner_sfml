#pragma once

#include "./Machine/State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameOverState : public State
{
public:
	GameOverState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(double dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Text			mGameOverText;
	double			mElapsedTime;
};