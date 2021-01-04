#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include <vector>

class PauseState : public State{
public:
    PauseState( GameDataRef data );
    ~PauseState();

    void Init() override;
    void PlaySound() override;
    void HandleInput() override;
    void Update( float dt ) override;
    void Draw( float dt ) override;

private:
    GameDataRef  m_data;
    sf::Sprite m_background;
    sf::Text m_paused_text;
    std::vector< sf::Text > m_buttons;

    void centerOrigin( sf::Text & );

    bool m_isReturnGameSelected;
    bool m_isReturnGamePressed;

    bool m_isBackMenuSelected;
    bool m_isBackMenuPressed;

    bool m_isResetGameSelected;
    bool m_isResetGamePressed;
};