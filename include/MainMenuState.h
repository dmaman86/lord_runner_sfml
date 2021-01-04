#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Game.h"
#include <vector>

class MainMenuState : public State{
public:
    MainMenuState( GameDataRef data );
    ~MainMenuState();

    void Init() override;
    void PlaySound() override;
    void HandleInput() override;
    void Update( float dt ) override;
    void Draw( float dt ) override;

private:
    GameDataRef  m_data;
    sf::Sprite m_background;
    std::vector< sf::Text > m_buttons;

    sf::SoundBuffer m_soundBuffer;
    sf::Sound m_sound;

    sf::Music m_music;

    bool m_isPlayButtonSelected;
    bool m_isPlayButtonPressed;

    bool m_isSettingsButtonSelected;
    bool m_isSettingsButtonPressed;

    bool m_isAboutOurSelected;
    bool m_isAboutOurPressed;
};