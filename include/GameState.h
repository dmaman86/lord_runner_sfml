#pragma once

#include "./Machine/State.h"
#include "Board.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

// enum ObjectType;


class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(double dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Sprite	mBackgroundSprite;
	sf::Sound m_sound;
	sf::Sound m_soundState;
	Board m_board;

	//std::unique_ptr<DynamicObject> m_player;
	Player* m_player;

	
	
	std::string getPath();

	void read_data(std::ifstream&);
	int m_numLevel = 1;
	bool m_isPause;

	sf::Clock m_clock;
};
