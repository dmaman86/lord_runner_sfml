#include <sstream>
#include <iostream>

#include "SplashState.h"
#include "MainMenuState.h"
#include "Singleton/ResourceManager.h"

SplashState::SplashState( GameDataRef & data )
    :m_data( data )
{

}

SplashState::~SplashState()
{

}

void SplashState::Init()
{
    sf::Vector2u textureSize, windowSize;

    m_sound = SoundManager::getInstance().getSound("Open State");

    windowSize = this->m_data->window.getSize();
    textureSize = this->m_data->assets.GetTexture( Textures::Splash ).getSize();

    std::unique_ptr<sf::Texture> texture = TextureManager::getInstance().getTexture("BackGround Open");

    m_background.setTexture( *texture );
    m_background.setScale( ( float )windowSize.x / textureSize.x,
                           ( float )windowSize.y / textureSize.y );
}

void SplashState::PlaySound( float dt )
{
    m_sound->play();
}

void SplashState::HandleInput()
{
    sf::Event event;

    while( m_data->window.pollEvent( event ) )
    {
        if( sf::Event::Closed == event.type )
        {
            // m_sound.stop();
            m_sound->stop();
            m_data->window.close();
        }
    }
}

void SplashState::Update( float dt )
{
    if( m_clock.getElapsedTime().asSeconds() > 3.0 )
    {
        // m_sound.pause();
        m_sound->stop();
        m_data->machine.AddState( StateRef( new MainMenuState( m_data ) ), true );
    }
}

void SplashState::Draw( float dt )
{
    m_data->window.clear();

    m_data->window.draw( m_background );

    m_data->window.display();
}