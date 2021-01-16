#pragma once

#include "./Machine/State.h"
#include "Board.h"
#include "ContainerStatus.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "models/Gift.h"

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);
	~GameState();

	virtual void draw();
	virtual bool update(double dt);
	virtual bool handleEvent(const sf::Event& event);


	virtual void pause();
	virtual void start();
private:
	sf::Sprite	mBackgroundSprite;
	sf::Sprite	m_stain;

	sf::Sound m_sound;
	sf::Sound m_soundState;

	// new sound
	sf::Sound m_sStartLevClock;
	sf::Sound m_sEndLevClock;
	sf::Sound m_PmeetM;


	Board m_board;
	ContainerStatus m_containerStatus;
	Player* m_player;

	// new daniel 15/1 9:15
	sf::Time m_time_of_level;
	sf::Clock m_level_clock;
	bool m_is_race_time;


	std::string getPath();

	void read_data(std::ifstream&);
	bool m_isPause;

	void handeleDig();
	void handleRace();
	void handleInjured();
	void handleNewLevel();



	//sf::Clock m_clock;
};
