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

class GameOverState : public State
{
public:
    GameOverState(GameDataRef& data);

    void Init() override;
    void HandleInput() override;
    void Update(float dt) override;
    void Draw(float dt) override;
    void PlaySound() override;

private:
    
};