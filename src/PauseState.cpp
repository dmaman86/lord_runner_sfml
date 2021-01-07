#include <iostream>
#include <sstream>
#include <cmath>

#include "PauseState.h"
#include "GameState.h"
#include "MainMenuState.h"

#include "Identifiers.h"

PauseState::PauseState( GameDataRef & data )
    :m_data( data ), m_isResetGamePressed( false ),
    m_isResetGameSelected( false ), m_isBackMenuPressed( false ),
    m_isBackMenuSelected( false )
{

}

PauseState::~PauseState()
{

}

void PauseState::Init()
{
    sf::Vector2u textureSize, windowSize;

    windowSize = this->m_data->window.getSize();

    textureSize = this->m_data->assets.GetTexture( Textures::Menu ).getSize();

    m_background.setTexture( this->m_data->assets.GetTexture( Textures::Menu ) );

    m_background.setScale( ( float )windowSize.x / textureSize.x,
                           ( float )windowSize.y / textureSize.y );

    m_data->assets.LoadFont( "Main Menu Font", "arial.ttf" );

    m_paused_text.setFont( m_data->assets.GetFont( "Main Menu Font" ) );
    m_paused_text.setString( "Game Paused" );
    m_paused_text.setCharacterSize( 70 );
    centerOrigin( m_paused_text );
    m_paused_text.setPosition( 0.5f * windowSize.x, 0.4f * windowSize.y );

    sf::Text text;
    text.setFont( m_data->assets.GetFont( "Main Menu Font" ) );
    text.setCharacterSize( 55 );
    text.setStyle( sf::Text::Bold );
    for( size_t i = 0; i < 2; i++ )
    {
        m_buttons.push_back( text );

        m_buttons[ i ].setOrigin( m_buttons[ i ].getLocalBounds().width / 2 ,
                                  m_buttons[ i ].getLocalBounds().height / 2 );
        m_buttons[ i ].setPosition( sf::Vector2f( windowSize.x / 2,
                                                  ( windowSize.y / 2 ) + ( i * 100 ) ) );
    }

    m_buttons[ 0 ].setString( "Back Menu Game" );
    m_buttons[ 0 ].setFillColor( sf::Color::White );
    m_buttons[ 1 ].setString( "Restart Game" );
    m_buttons[ 1 ].setFillColor( sf::Color::White );
}

void PauseState::PlaySound( float dt )
{

}

void PauseState::HandleInput()
{
    sf::Event event;

    while( m_data->window.pollEvent( event ) )
    {
        if( sf::Event::Closed == event.type )
            m_data->window.close();

        if( ( m_isBackMenuPressed = m_data->input.isSpriteClicked( m_buttons[ 0 ], sf::Mouse::Left, m_data->window ) ) == true )
        {
            m_isBackMenuSelected = true;
            m_isResetGameSelected = false;
        }
        if( ( m_isResetGamePressed = m_data->input.isSpriteClicked( m_buttons[ 1 ], sf::Mouse::Left, m_data->window ) ) == true )
        {
            m_isBackMenuSelected = false;
            m_isResetGameSelected = true;
        }
    }
}

void PauseState::Update( float dt )
{
    if( m_isBackMenuSelected )
    {
        m_data->machine.AddState( StateRef( new MainMenuState( m_data ) ) );
    }
    else if( m_isResetGameSelected )
    {
        m_data->machine.RemoveState();
        m_data->machine.AddState( StateRef( new GameState( m_data ) ), true );
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