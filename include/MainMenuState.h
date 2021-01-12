#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Game.h"
#include <vector>

class MainMenuState : public State{
public:
    MainMenuState( GameDataRef& data );

    void Init() override;
    void HandleInput() override;
    void Update( float dt ) override;
    void Draw( float dt ) override;
    void PlaySound() override;

private:
    GameDataRef  m_data;

    sf::Sprite m_background;
    std::vector< sf::Text > m_buttons;

    // sf::Music m_music;
    // std::unique_ptr<sf::Music> m_music;
    sf::Sound m_sound;
    sf::Sound m_sound_state;
    // sf::Sound m_sound;

    bool m_isPlayButtonSelected;
    bool m_isPlayButtonPressed;

    bool m_isSettingsButtonSelected;
    bool m_isSettingsButtonPressed;

    bool m_isAboutOurSelected;
    bool m_isAboutOurPressed;

    bool m_isRecordsSelected;
    bool m_isRecordsPressed;

    bool m_playMusic;
    bool m_pressed = false;

    void updateColorButton();

    sf::Clock m_clock;
};