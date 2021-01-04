#include "Game.h"
#include "SplashState.h"
#include "StateStack.h"

Game::Game( int width, int height, std::string title )
{
    m_data->window.create( sf::VideoMode( width, height ), title );

    m_data->machine.AddState( StateRef( new SplashState( this->m_data ) ) );
    // m_data->machine.pushState( StateRef( new SplashState( this->m_data ) ) );

    // this->Run();
}

void Game::Run()
{
    float newTime, frameTime, interpolation;

    float currentTime = this->m_clock.getElapsedTime().asSeconds();

    float accumulator = 0.0f;

    while( this->m_data->window.isOpen() )
    {
        this->m_data->machine.ProcessStateChange();

        newTime = this->m_clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;

        if( frameTime > 0.25f )
            frameTime = 0.25f;

        currentTime = newTime;
        accumulator += frameTime;

        while( accumulator >= dt )
        {
            accumulator -= dt;
            this->m_data->machine.GetActiveState()->PlaySound();
            this->m_data->machine.GetActiveState()->HandleInput();
            this->m_data->machine.GetActiveState()->Update( dt );
        }

        interpolation = accumulator / dt;
        this->m_data->machine.GetActiveState()->Draw( interpolation );
    }
}