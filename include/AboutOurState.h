#pragma once

#include "./Machine/State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <cmath>

class AboutOurState : public State
{
public:
	AboutOurState(StateStack& stack, Context context);

	virtual void			draw();
	virtual bool			update(double dt);
	virtual bool			handleEvent(const sf::Event& event);

	virtual void pause(){}
	virtual void start(){}

private:
	sf::Sprite mBackgroundSprite;
	sf::Text m_title;

	sf::Sound m_soundState;

	bool m_backToMenu;

	void centerOrigin(sf::Text&);
};