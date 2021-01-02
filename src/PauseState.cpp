#include <iostream>
#include <sstream>
#include <cmath>

#include "PauseState.h"
#include "GameState.h"
#include "MainMenuState.h"

PauseState::PauseState( GameDataRef data )
    :m_data( data )
{

}

void PauseState::Init()
{
    sf::Vector2u textureSize, windowSize;

    m_data->assets.LoadTexture( "Main Menu BackGround",
                                "../resources/img/background_menu.png" );

    windowSize = this->m_data->window.getSize();
    textureSize = this->m_data->assets.GetTexture( "Main Menu BackGround" ).getSize();

    m_background.setTexture( this->m_data->assets.GetTexture( "Main Menu BackGround" ) );
    m_background.setScale( ( float )windowSize.x / textureSize.x,
                           ( float )windowSize.y / textureSize.y );

    m_data->assets.LoadFont( "Main Menu Font", "../resources/fonts/arial.ttf" );

    m_paused_text.setFont( m_data->assets.GetFont( "Main Menu Font" ) );
    m_paused_text.setString( "Game Paused" );
    m_paused_text.setCharacterSize( 70 );
    centerOrigin( m_paused_text );
    m_paused_text.setPosition( 0.5f * windowSize.x, 0.4f * windowSize.y );

    sf::Text text;
    text.setFont( m_data->assets.GetFont( "Main Menu Font" ) );
    text.setCharacterSize( 24 );
    text.setStyle( sf::Text::Bold );
    for( size_t i = 0; i < 2; i++ )
    {
        m_buttons.push_back( text );

        m_buttons[ i ].setOrigin( m_buttons[ i ].getLocalBounds().width / 2 ,
                                  m_buttons[ i ].getLocalBounds().height / 2 );
        m_buttons[ i ].setPosition( sf::Vector2f( windowSize.x / 2,
                                                  ( windowSize.y / 2 ) + ( i * 100 ) ) );
    }

    m_buttons[ 0 ].setString( "Return" );
    m_buttons[ 0 ].setFillColor( sf::Color::White );
    m_buttons[ 1 ].setString( "Back Menu" );
    m_buttons[ 1 ].setFillColor( sf::Color::White );
}

void PauseState::HandleInput()
{
    sf::Event event;

    while( m_data->window.pollEvent( event ) )
    {
        if( sf::Event::Closed == event.type )
            m_data->window.close();

        if( m_data->input.isSpriteClicked( m_buttons[ 0 ], sf::Mouse::Left, m_data->window ) )
        {
            std::cout << "Return to Game" << std::endl;
        }
        if( m_data->input.isSpriteClicked( m_buttons[ 1 ], sf::Mouse::Left, m_data->window ) )
        {
            std::cout << "Return to Menu" << std::endl;
        }
    }
}

void PauseState::Update( float dt )
{

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