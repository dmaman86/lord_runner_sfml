#include <sstream>
#include <iostream>

#include "SplashState.h"
#include "MainMenuState.h"

SplashState::SplashState( GameDataRef data )
    :m_data( data )
{

}

void SplashState::Init()
{
    sf::Vector2u textureSize, windowSize;

    if( !m_soundBuffer.loadFromFile( "../resources/sounds/open.wav" ) )
        std::cout << "Error loading Open Sound Effect" << std::endl;

    m_sound.setBuffer( m_soundBuffer );

    m_data->assets.LoadTexture( "Splash State Background",
                                "../resources/img/splash-background.png" );

    windowSize = this->m_data->window.getSize();
    textureSize = this->m_data->assets.GetTexture( "Splash State Background" ).getSize();

    m_background.setTexture( this->m_data->assets.GetTexture( "Splash State Background" ) );
    m_background.setScale( ( float )windowSize.x / textureSize.x,
                           ( float )windowSize.y / textureSize.y );

}

void SplashState::PlaySound()
{
    // m_sound.play();
}

void SplashState::HandleInput()
{
    sf::Event event;

    while( m_data->window.pollEvent( event ) )
    {
        // m_sound.pause();
        if( sf::Event::Closed == event.type )
            m_data->window.close();
    }
}

void SplashState::Update( float dt )
{
    if( m_clock.getElapsedTime().asSeconds() > 3.0 )
    {
        // m_sound.pause();
        m_data->machine.AddState( StateRef( new MainMenuState( m_data ) ), true );
    }
}

void SplashState::Draw( float dt )
{
    m_data->window.clear();

    m_data->window.draw( m_background );

    m_data->window.display();
}