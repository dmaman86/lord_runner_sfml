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

    void Init() override;
    void PlaySound() override;
    void HandleInput() override;
    void Update( float dt ) override;
    void Draw( float dt ) override;

private:
    GameDataRef  m_data;
    Board m_board;
    sf::Sprite m_background;

    std::string getPath();
    void read_data( std::ifstream & );

    int m_numLevel = 1;

    sf::SoundBuffer m_soundBuffer;
    sf::Sound m_sound;

    sf::Music m_music;

    bool m_isPause;
};