#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Game.h"
#include <vector>

class MainMenuState : public State{
public:
    MainMenuState( GameDataRef data );

    void Init();

    void HandleInput();
    void Update( float dt );
    void Draw( float dt );

private:
    GameDataRef  m_data;
    sf::Sprite m_background;
    std::vector< sf::Text > m_buttons;

    sf::SoundBuffer m_soundBuffer;
    sf::Sound m_sound;
};