#pragma once

#include "./Machine/State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <cmath>

class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);
	~PauseState();

	virtual void		draw();
	virtual bool		update(double dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Sprite			mBackgroundSprite;
	sf::Text			mPausedText;
	std::vector<sf::Text> m_buttons;

	sf::Sound m_sound;
	sf::Sound m_soundState;

	sf::Clock m_clock;

	void centerOrigin(sf::Text&);
	void updateColorButton();

	bool m_isBackMenuSelected;
	bool m_isBackMenuPressed;

	bool m_isResetGameSelected;
	bool m_isResetGamePressed;

	bool m_backToGameSelected;
	bool m_backToGamePressed;

	bool m_pressed;
};