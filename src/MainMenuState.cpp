#include <iostream>
#include <sstream>

#include "MainMenuState.h"


MainMenuState::MainMenuState( GameDataRef data )
    :m_data( data )
{

}

void MainMenuState::Init()
{
    sf::Vector2u textureSize, windowSize;

    m_data->assets.LoadTexture( "Main Menu BackGround",
                                "../resources/img/background_menu.png" );

    windowSize = this->m_data->window.getSize();
    textureSize = this->m_data->assets.GetTexture( "Main Menu BackGround" ).getSize();

    m_background.setTexture( this->m_data->assets.GetTexture( "Main Menu BackGround" ) );
    m_background.setScale( ( float )windowSize.x / textureSize.x,
                           ( float )windowSize.y / textureSize.y );

    sf::Text text;

    m_data->assets.LoadFont( "Main Menu Font", "../resources/fonts/arial.ttf" );
    text.setFont( m_data->assets.GetFont( "Main Menu Font" ) );
    text.setCharacterSize( 24 );
    text.setStyle( sf::Text::Bold );
    for( size_t i = 0; i < 3; i++ )
    {
        m_buttons.push_back( text );

        m_buttons[ i ].setOrigin( m_buttons[ i ].getLocalBounds().width / 2 ,
                                  m_buttons[ i ].getLocalBounds().height / 2 );
        m_buttons[ i ].setPosition( sf::Vector2f( windowSize.x / 2,
                                                  ( windowSize.y / 2 ) + ( i * 100 ) ) );
    }

    m_buttons[ 0 ].setString( "Play Game" );
    m_buttons[ 0 ].setFillColor( sf::Color::White );
    m_buttons[ 1 ].setString( "Settings Game" );
    m_buttons[ 1 ].setFillColor( sf::Color::White );
    m_buttons[ 2 ].setString( "About Our" );
    m_buttons[ 2 ].setFillColor( sf::Color::White );
}

void MainMenuState::HandleInput()
{
    sf::Event event;

    while( m_data->window.pollEvent( event ) )
    {
        if( sf::Event::Closed == event.type )
            m_data->window.close();

        if( m_data->input.isSpriteClicked( m_buttons[ 0 ], sf::Mouse::Left, m_data->window ) )
        {
            m_buttons[ 0 ].setFillColor( sf::Color::Black );
            m_buttons[ 1 ].setFillColor( sf::Color::White );
            m_buttons[ 2 ].setFillColor( sf::Color::White );
            std::cout << "Go to Game Screen" << std::endl;
        }

        if( m_data->input.isSpriteClicked( m_buttons[ 1 ], sf::Mouse::Left, m_data->window ) )
        {
            m_buttons[ 1 ].setFillColor( sf::Color::Black );
            m_buttons[ 0 ].setFillColor( sf::Color::White );
            m_buttons[ 2 ].setFillColor( sf::Color::White );
            std::cout << "Go to Settings Screen" << std::endl;
        }


        if( m_data->input.isSpriteClicked( m_buttons[ 2 ], sf::Mouse::Left, m_data->window ) )
        {
            m_buttons[ 2 ].setFillColor( sf::Color::Black );
            m_buttons[ 0 ].setFillColor( sf::Color::White );
            m_buttons[ 1 ].setFillColor( sf::Color::White );
            std::cout << "Go to About Our Screen" << std::endl;
        }
    }
}

void MainMenuState::Update( float dt )
{

}

void MainMenuState::Draw( float dt )
{
    m_data->window.clear();

    m_data->window.draw( m_background );

    for( auto button : m_buttons )
        m_data->window.draw( button );

    m_data->window.display();
}