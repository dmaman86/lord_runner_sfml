#include <iostream>
#include <sstream>

#include "MainMenuState.h"
#include "GameState.h"


MainMenuState::MainMenuState( GameDataRef & data )
    :m_data( data )
{
    m_isPlayButtonSelected = false;
    m_isPlayButtonPressed = false;
    m_isSettingsButtonSelected = false;
    m_isSettingsButtonPressed = false;
    m_isAboutOurSelected = false;
    m_isAboutOurPressed = false;
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::Init()
{
    sf::Vector2u textureSize, windowSize;

    m_data->assets.LoadTexture( "Main Menu BackGround",
                                "background_menu.png" );

    m_data->assets.LoadMusicFile( "Music Menu", "menusound.wav" );

    if( m_music.openFromFile( m_data->assets.GetMusic( "Music Menu" ) ) )
        m_music.setLoop( true );


    windowSize = this->m_data->window.getSize();
    textureSize = this->m_data->assets.GetTexture( "Main Menu BackGround" ).getSize();

    m_background.setTexture( this->m_data->assets.GetTexture( "Main Menu BackGround" ) );
    m_background.setScale( ( float )windowSize.x / textureSize.x,
                           ( float )windowSize.y / textureSize.y );

    sf::Text text;

    m_data->assets.LoadFont( "Main Menu Font", "arial.ttf" );
    text.setFont( m_data->assets.GetFont( "Main Menu Font" ) );
    text.setCharacterSize( 55 );
    text.setStyle( sf::Text::Bold );
    for( size_t i = 0; i < 3; i++ )
    {
        m_buttons.push_back( text );

        m_buttons[ i ].setOrigin( m_buttons[ i ].getLocalBounds().width / 2 ,
                                  m_buttons[ i ].getLocalBounds().height / 2 );
        m_buttons[ i ].setPosition( sf::Vector2f( windowSize.x / 2,
                                                  ( windowSize.y / 2 ) + ( i * 100 ) ) );
        m_buttons[ i ].setFillColor( sf::Color::White );
    }

    m_buttons[ 0 ].setString( "Play Game" );
    m_buttons[ 1 ].setString( "Settings Game" );
    m_buttons[ 2 ].setString( "About Our" );
}

void MainMenuState::PlaySound( float dt )
{
    static int i = 1;

    if( i == 1 )
    {
        m_music.play();
        i++;
    }
}

void MainMenuState::HandleInput()
{
    sf::Event event;

    while( m_data->window.pollEvent( event ) )
    {
        if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_music.stop();
            m_data->window.close();
        }

        if (sf::Event::MouseButtonPressed)
        {
            if ((m_isPlayButtonPressed = m_data->input.isSpriteClicked(m_buttons[0], sf::Mouse::Left,
                                                                       m_data->window)) == true)
            {
                m_isPlayButtonSelected = true;
                m_isSettingsButtonSelected = false;
                m_isAboutOurSelected = false;
            }

            if ((m_isSettingsButtonPressed = m_data->input.isSpriteClicked(m_buttons[1], sf::Mouse::Left,
                                                                           m_data->window)) == true)
            {
                m_isSettingsButtonSelected = true;
                m_isPlayButtonSelected = false;
                m_isAboutOurSelected = false;
            }


            if ((m_isAboutOurPressed = m_data->input.isSpriteClicked(m_buttons[2], sf::Mouse::Left,
                                                                     m_data->window)) == true)
            {
                m_isAboutOurSelected = true;
                m_isPlayButtonSelected = false;
                m_isSettingsButtonSelected = false;
            }
        }
    }
}

void MainMenuState::Update( float dt )
{
    if( m_isPlayButtonSelected )
    {
        m_buttons[ 0 ].setFillColor( sf::Color::Black );
        m_buttons[ 1 ].setFillColor( sf::Color::White );
        m_buttons[ 2 ].setFillColor( sf::Color::White );
    }
    else if( m_isSettingsButtonSelected )
    {
        m_buttons[ 0 ].setFillColor( sf::Color::White );
        m_buttons[ 1 ].setFillColor( sf::Color::Black );
        m_buttons[ 2 ].setFillColor( sf::Color::White );
    }
    else
    {
        m_buttons[ 0 ].setFillColor( sf::Color::White );
        m_buttons[ 1 ].setFillColor( sf::Color::White );
        m_buttons[ 2 ].setFillColor( sf::Color::Black );
    }

    if( m_isPlayButtonPressed )
    {
        // m_music_t.Stop();
        m_music.stop();
        m_data->machine.AddState( StateRef( new GameState( m_data ) ), true );
    }
    else if( m_isSettingsButtonPressed )
    {
        std::cout << "Go to Setting Screen" << std::endl;
    }
    else if( m_isAboutOurPressed )
    {
        std::cout << "Go to About Out Screen" << std::endl;
    }
}

void MainMenuState::Draw( float dt )
{
    m_data->window.clear();

    m_data->window.draw( m_background );

    for( auto button : m_buttons )
        m_data->window.draw( button );

    m_data->window.display();
}