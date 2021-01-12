#include "Game.h"
#include "SplashState.h"


Game::Game( int width, int height, std::string title )
{
    m_data->window.create( sf::VideoMode( width, height ), title );
    m_data->resources->getInstance().loadResource();

    m_data->machine.AddState( StateRef( new SplashState( this->m_data ) ) );
}

void Game::Run()
{
    // m_data->resources->getInstance().loadResource();
    while( this->m_data->window.isOpen() )
    {
        m_dt = this->m_clock.restart().asSeconds();

        this->m_data->machine.ProcessStateChange();
        // this->m_data->machine.GetActiveState()->PlaySound();
        this->m_data->machine.GetActiveState()->HandleInput();
        this->m_data->machine.GetActiveState()->Update( m_dt );
        this->m_data->machine.GetActiveState()->PlaySound();
        this->m_data->machine.GetActiveState()->Draw( m_dt );
    }
}