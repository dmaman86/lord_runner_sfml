#pragma once

#include "./Machine/State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>


class FinalState : public State
{
public:
	FinalState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(double dt);
	virtual bool handleEvent(const sf::Event& event);

	virtual void pause() {}
	virtual void start() {}
private:
	sf::Sprite mBackgroundSprite;
	sf::Text m_title;
	sf::Text m_message;
	sf::Sound m_soundState;

	sf::String playerInput;
	sf::Texture playerText;

	double mElapsedTime;

	bool m_backToMenu;

	void centerOrigin(sf::Text&);
};