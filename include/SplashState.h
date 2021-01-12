#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Game.h"

class SplashState : public State{
public:
    SplashState( GameDataRef& data );

    void Init() override;
    void HandleInput() override;
    void Update( float dt ) override;
    void Draw( float dt ) override;
    void PlaySound() override;

private:
    GameDataRef  m_data;
    sf::Clock m_clock;
    sf::Sprite m_background;
    // std::unique_ptr<sf::Sprite> m_background;

    // sf::Sound m_sound;
     sf::Sound m_sound;
};