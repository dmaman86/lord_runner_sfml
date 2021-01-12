#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Game.h"
#include <vector>

class PauseState : public State{
public:
    PauseState( GameDataRef& data );

    void Init() override;
    void HandleInput() override;
    void Update( float dt ) override;
    void Draw( float dt ) override;

private:
    GameDataRef  m_data;
    sf::Sprite m_background;
    sf::Text m_paused_text;
    std::vector< sf::Text > m_buttons;
    // std::unique_ptr<sf::Music> m_music;
    sf::Music* m_music;
    std::unique_ptr<sf::Sound> m_sound;
    sf::Clock m_clock;

    void centerOrigin( sf::Text & );

    bool m_isBackMenuSelected;
    bool m_isBackMenuPressed;

    bool m_isResetGameSelected;
    bool m_isResetGamePressed;

    bool m_pressed;
};