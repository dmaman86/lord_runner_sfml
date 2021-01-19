#pragma once

#include "./Machine/State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <cmath>

class RecordsState : public State
{
public:
	RecordsState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(double dt);
	virtual bool handleEvent(const sf::Event& event);
	virtual void pause() {}
	virtual void start() {}

private:
	sf::Sprite mBackgroundSprite;
	sf::Text m_title;
	sf::Sound m_soundState;

	sf::Text m_userName;
	sf::Text m_userScore;
	std::string str;
	int score;

	bool m_backToMenu;

	double mElapsedTime;

	std::multimap<std::string, int> m_multimap;

	void centerOrigin(sf::Text&);
};