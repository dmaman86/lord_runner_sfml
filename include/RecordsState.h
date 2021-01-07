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

class RecordsState : public State
{
public:
    RecordsState(GameDataRef& data);
    ~RecordsState();

    void Init() override;
    void HandleInput() override;
    void Update(float dt) override;
    void Draw(float dt) override;
    void PlaySound(float dt) override;

private:
    GameDataRef  m_data;

    sf::Sprite m_background;


    sf::SoundBuffer m_soundBuffer;
    sf::Sound m_sound;

    sf::Music m_music;

    bool m_isPause;
};