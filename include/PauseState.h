#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include <vector>

class PauseState : public State{
public:
    PauseState( GameDataRef data );

    void Init();

    void HandleInput();
    void Update( float dt );
    void Draw( float dt );

private:
    GameDataRef  m_data;
    sf::Sprite m_background;
    sf::Text m_paused_text;
    std::vector< sf::Text > m_buttons;

    void centerOrigin( sf::Text & );
};