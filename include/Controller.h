#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Board.h"

//const float COLL_GAME_SCREEN = 1920.f;
//const float ROW_GAME_SCREEN = 930.f;

class Controller {

public:
	//Concstructor/Distractor
	Controller();
	~Controller();
	
	//Function
	void updateSFMLEvnt();
	void updateDt();
	void update();
	void render();
	void run();

private:
	//Variabels
	sf::RenderWindow *m_window;
	sf::Event m_SFevnet;
	sf::Clock m_dtClock;
	
	float m_dt;//delta time
	Board m_board;
	int m_numLevel = 1;
	sf::Texture m_back;
	sf::Sprite m_sprite;
	bool m_open;

	//Private function

	std::string getPath();
	void read_data(std::ifstream&);

	//Initializer function
	void initWindow();
	void initbackground();

};