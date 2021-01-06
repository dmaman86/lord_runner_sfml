#include "Game.h"
#include "SplashState.h"

Game::Game( int width, int height, std::string title )
{
    m_data->window.create( sf::VideoMode( width, height ), title );

    m_data->machine.AddState( StateRef( new SplashState( this->m_data ) ) );
}

void Game::Run()
{
    float accumulator = 0.0f;

    while( this->m_data->window.isOpen() )
    {
        accumulator += this->m_clock.restart().asSeconds();

        while( accumulator > m_dt )
        {
            accumulator -= m_dt;

            this->m_data->machine.ProcessStateChange();
            this->m_data->machine.GetActiveState()->HandleInput();
            this->m_data->machine.GetActiveState()->Update( m_dt );
            this->m_data->machine.GetActiveState()->PlaySound( m_dt );
            this->m_data->machine.GetActiveState()->Draw( m_dt );
        }
    }
}