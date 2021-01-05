#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Game.h"

class SplashState : public State{
public:
    SplashState( GameDataRef & data );

    void Init() override;
    void PlaySound() override;
    void HandleInput() override;
    void Update( float dt ) override;
    void Draw( float dt ) override;
private:
    GameDataRef  m_data;
    sf::Clock m_clock;
    sf::Sprite m_background;

    sf::SoundBuffer m_soundBuffer;
    sf::Sound m_sound;

    sf::Music m_music;
};