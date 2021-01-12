#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "Singleton/ResourceManager.h"
#include "ResourceManager/ResourceIdentifiers.h"

struct GameData{
    StateMachine machine;
    sf::RenderWindow window;
    InputManager input;
    ResourceManager resources;
};

typedef std::shared_ptr< GameData > GameDataRef;

class Game{
public:
    Game( int width, int height, std::string title );
    void Run();

private:
    float m_dt;

    sf::Clock m_clock;
    GameDataRef m_data = std::make_shared< GameData >();
};