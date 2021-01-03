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

#include "State.h"
#include "Game.h"
#include "Board.h"

class GameState : public State
{
public:
    GameState( GameDataRef data );

    void Init();
    void HandleInput();
    void Update( float dt );
    void Draw( float dt );

private:
    GameDataRef  m_data;
    Board m_board;
    sf::Sprite m_background;

    std::string getPath();
    void read_data( std::ifstream & );

    int m_numLevel = 1;
};