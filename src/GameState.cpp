#include "GameState.h"
#include "PauseState.h"

GameState::GameState( GameDataRef data ) : m_data( data ) {}

void GameState::Init()
{
    m_data->assets.LoadTexture( "Game Background", "../resources/img/background.png" );
    m_background.setTexture( this->m_data->assets.GetTexture( "Game Background" ) );
}

void GameState::HandleInput()
{
    sf::Event event;

    while( m_data->window.pollEvent( event ) )
    {
        if( sf::Event::Closed == event.type )
            m_data->window.close();
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
            m_data->window.close();
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
        {
            m_data->machine.AddState( StateRef( new PauseState( m_data ) ), true );
        }
    }
}

void GameState::Update( float dt )
{

}

void GameState::Draw( float dt )
{
    m_data->window.clear();

    m_data->window.draw( m_background );

    m_data->window.display();
}

