#include <iostream>
#include <sstream>
#include <cmath>

#include "PauseState.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "Singleton/ResourceManager.h"
#include "Identifiers.h"

PauseState::PauseState( GameDataRef& data )
    :m_data( data ), m_isResetGamePressed( false ),
    m_isResetGameSelected( false ), m_isBackMenuPressed( false ),
    m_isBackMenuSelected( false ), m_pressed(false)
{

}

void PauseState::Init()
{
    sf::Vector2u textureSize, windowSize;
    sf::Texture texture = TextureManager::getInstance().getTexture(Textures::Menu);

    windowSize = this->m_data->window.getSize();

    textureSize = texture.getSize();

    m_background.setTexture( texture );

    m_background.setScale( ( float )windowSize.x / textureSize.x,
                           ( float )windowSize.y / textureSize.y );

    sf::Font font = FontManager::getInstance().getFont(Fonts::Main);

    m_paused_text.setFont( font );
    m_paused_text.setString( "Game Paused" );
    m_paused_text.setCharacterSize( 70 );
    centerOrigin( m_paused_text );
    m_paused_text.setPosition( 0.5f * windowSize.x, 0.4f * windowSize.y );

    sf::Text text;
    text.setFont( font );
    text.setCharacterSize( 55 );
    text.setStyle( sf::Text::Bold );
    for( size_t i = 0; i < 2; i++ )
    {
        m_buttons.push_back( text );
        m_buttons[i].setFillColor(sf::Color::White);
        m_buttons[ i ].setOrigin( m_buttons[ i ].getLocalBounds().width / 2 ,
                                  m_buttons[ i ].getLocalBounds().height / 2 );
        m_buttons[ i ].setPosition( sf::Vector2f( windowSize.x / 2.5,
                                                  ( windowSize.y / 2 ) + ( i * 100 ) ) );
    }

    m_buttons[ 0 ].setString( "Back Menu Game" );
    m_buttons[ 1 ].setString( "Restart Game" );

    m_sound_state = SoundManager::getInstance().getSound(SoundEffect::Menu);
    m_sound_state.setLoop(true);
    // m_sound_state.play();
    m_sound = SoundManager::getInstance().getSound(SoundEffect::MoveState);
}

void PauseState::PlaySound()
{
    m_sound_state.play();
}

void PauseState::HandleInput()
{
    sf::Event event;

    while( m_data->window.pollEvent( event ) )
    {
        if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_sound_state.stop();
            m_data->window.close();
        }
        if( ( m_isBackMenuPressed = m_data->input.isSpriteClicked( m_buttons[ 0 ],
                                    sf::Mouse::Left, m_data->window ) ) == true )
        {
            m_isBackMenuSelected = true;
            m_isResetGameSelected = false;
            m_pressed = true;
        }
        if( ( m_isResetGamePressed = m_data->input.isSpriteClicked( m_buttons[ 1 ],
                                    sf::Mouse::Left, m_data->window ) ) == true )
        {
            m_isBackMenuSelected = false;
            m_isResetGameSelected = true;
            m_pressed = false;
        }
    }
}

void PauseState::Update( float dt )
{
    if (m_pressed)
    {
        m_pressed = false;
        m_sound.play();
        if (m_clock.getElapsedTime().asSeconds() > 2.0)
        {
            m_sound.stop();
            if (m_isBackMenuSelected)
            {
                m_sound_state.stop();
                m_data->machine.AddState(StateRef(new MainMenuState(m_data)));
            }
            else if (m_isResetGameSelected)
            {
                m_sound_state.stop();
                m_data->machine.RemoveState();
                m_data->machine.AddState(StateRef(new GameState(m_data)));
            }
        }
    }
}

void PauseState::Draw( float dt )
{
    m_data->window.clear();

    m_data->window.draw( m_background );

    m_data->window.draw( m_paused_text );

    for( auto button : m_buttons )
        m_data->window.draw( button );
    m_data->window.display();
}

void PauseState::centerOrigin(sf::Text & text )
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin( std::floor( bounds.left + bounds.width / 2.f ),
                    std::floor( bounds.top + bounds.height / 2.f ) );
}