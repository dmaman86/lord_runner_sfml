#pragma once

#include "./Machine/State.h"
#include "Board.h"
#include "ContainerStatus.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(double dt);
	virtual bool handleEvent(const sf::Event& event);


private:
	sf::Sprite	mBackgroundSprite;
	sf::Sound m_sound;
	sf::Sound m_soundState;
	Board m_board;
	ContainerStatus m_containerStatus;
	Player* m_player;

	std::string getPath();

	void read_data(std::ifstream&);
	int m_numLevel = 1;
	bool m_isPause;

	sf::Clock m_clock;
};
