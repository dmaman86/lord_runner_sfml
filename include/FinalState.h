#pragma once

#include "./Machine/State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <iostream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

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
	sf::Text playerText;
	std::string m_score_player;

	double mElapsedTime;

	bool m_backToMenu;

	void centerOrigin(sf::Text&);
	void inputLogic(int charTyped);
	void deleteLastChar();
	void saveString();
};