#include <iostream>
#include <sstream>

#include "MainMenuState.h"
#include "GameState.h"

#include "Identifiers.h"
#include "IdentifiersState.h"
#include "Singleton/ResourceManager.h"

MainMenuState::MainMenuState( GameDataRef & data )
    :m_data( data ), m_playMusic( true )
{
    m_isPlayButtonSelected = false;
    m_isPlayButtonPressed = false;
    m_isSettingsButtonSelected = false;
    m_isSettingsButtonPressed = false;
    m_isAboutOurSelected = false;
    m_isAboutOurPressed = false;
    m_isRecordsPressed = false;
    m_isRecordsSelected = false;

    if ((m_music = MusicManager::getInstance().getMusic("menusound.wav")) != nullptr)
        m_music->setLoop(true);
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::Init()
{
    sf::Vector2u textureSize, windowSize;

    m_sound = SoundManager::getInstance().getSound("new_move_next_state.wav");


    windowSize = this->m_data->window.getSize();

    std::unique_ptr<sf::Texture> texture = TextureManager::getInstance().getTexture("background_menu.png");
    textureSize = texture->getSize();
    m_background.setTexture(*texture);
    m_background.setScale( ( float )windowSize.x / textureSize.x,
                           ( float )windowSize.y / textureSize.y );

    sf::Text text;
    std::unique_ptr<sf::Font> font = FontManager::getInstance().getFont("arial.ttf");
    text.setFont(*font);
    text.setCharacterSize( 55 );
    text.setStyle( sf::Text::Bold );

    for( size_t i = 0; i < StatesMenu::Exit; i++ )
    {
        m_buttons.push_back( text );
        m_buttons[i].setFillColor(sf::Color::White);

        m_buttons[ i ].setOrigin( m_buttons[ i ].getLocalBounds().width / 2 ,
                                  m_buttons[ i ].getLocalBounds().height / 2 );
        m_buttons[ i ].setPosition( sf::Vector2f( windowSize.x / 2.5,
                                                  ( windowSize.y / 2 ) + ( i * 100 ) ) );
    }

    m_buttons[ StatesMenu::Game ].setString( "Play Game" );
    m_buttons[ StatesMenu::Settings ].setString( "Settings Game" );
    m_buttons[ StatesMenu::AboutOur ].setString( "About Our" );
    m_buttons[ StatesMenu::Records ].setString("Records Game");
}

void MainMenuState::PlaySound( float dt )
{
    m_music->play();
}

void MainMenuState::StopSound()
{
   // m_music->stop();
   // m_sound->play();
}

void MainMenuState::HandleInput()
{
    sf::Event event;

    while( m_data->window.pollEvent( event ) )
    {
        if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_music->stop();
            m_data->window.close();
        }

        if (sf::Event::MouseButtonPressed)
        {
           
            if ((m_isPlayButtonPressed = m_data->input.isSpriteClicked(m_buttons[ StatesMenu::Game ], sf::Mouse::Left,
                                                                       m_data->window)) == true)
            {
                m_isPlayButtonSelected = true;
                m_isSettingsButtonSelected = false;
                m_isAboutOurSelected = false;
                m_isRecordsSelected = false;
                m_pressed = true;
            }

            if ((m_isSettingsButtonPressed = m_data->input.isSpriteClicked(m_buttons[ StatesMenu::Settings ], sf::Mouse::Left,
                                                                           m_data->window)) == true)
            {
                m_isSettingsButtonSelected = true;
                m_isPlayButtonSelected = false;
                m_isAboutOurSelected = false;
                m_isRecordsSelected = false;
                m_pressed = true;
            }


            if ((m_isAboutOurPressed = m_data->input.isSpriteClicked(m_buttons[ StatesMenu::AboutOur ], sf::Mouse::Left,
                                                                     m_data->window)) == true)
            {
                m_isAboutOurSelected = true;
                m_isPlayButtonSelected = false;
                m_isSettingsButtonSelected = false;
                m_isRecordsSelected = false;
                m_pressed = true;
            }

            if ((m_isRecordsPressed = m_data->input.isSpriteClicked(m_buttons[ StatesMenu::Records ], sf::Mouse::Left, m_data->window)) == true)
            {
                m_isAboutOurSelected = false;
                m_isPlayButtonSelected = false;
                m_isSettingsButtonSelected = false;
                m_isRecordsSelected = true;
                m_pressed = true;
            }
        }
    }
}

void MainMenuState::Update( float dt )
{
    updateColorButton();

    if (m_pressed)
    {
        if (m_clock.getElapsedTime().asSeconds() > 2.0)
        {
            // StopSound();
            m_music->pause();
            m_sound->pause();
            m_pressed = false;
            if (m_isPlayButtonSelected)
            {
                 m_data->machine.AddState(StateRef(new GameState(m_data)), true);
            }
            else if (m_isSettingsButtonSelected)
            {
                std::cout << "Go to Setting Screen" << std::endl;
            }
            else if (m_isAboutOurSelected)
            {
                std::cout << "Go to About Out Screen" << std::endl;
            }
            else if (m_isRecordsSelected)
            {
                std::cout << "Go to Records Screen" << std::endl;
            }
        }
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

void MainMenuState::updateColorButton()
{
    if (m_isPlayButtonSelected)
    {
        m_buttons[StatesMenu::Game ].setFillColor(sf::Color::Black);
        m_buttons[StatesMenu::Settings].setFillColor(sf::Color::White);
        m_buttons[StatesMenu::AboutOur].setFillColor(sf::Color::White);
        m_buttons[StatesMenu::Records].setFillColor(sf::Color::White);

    }
    else if (m_isSettingsButtonSelected)
    {
        m_buttons[StatesMenu::Game].setFillColor(sf::Color::White);
        m_buttons[StatesMenu::Settings].setFillColor(sf::Color::Black);
        m_buttons[StatesMenu::AboutOur].setFillColor(sf::Color::White);
        m_buttons[StatesMenu::Records].setFillColor(sf::Color::White);

    }
    else if (m_isAboutOurSelected)
    {
        m_buttons[StatesMenu::Game].setFillColor(sf::Color::White);
        m_buttons[StatesMenu::Settings].setFillColor(sf::Color::White);
        m_buttons[StatesMenu::AboutOur].setFillColor(sf::Color::Black);
        m_buttons[StatesMenu::Records].setFillColor(sf::Color::White);
    }
    else if( m_isRecordsSelected)
    {
        m_buttons[StatesMenu::Game].setFillColor(sf::Color::White);
        m_buttons[StatesMenu::Settings].setFillColor(sf::Color::White);
        m_buttons[StatesMenu::AboutOur].setFillColor(sf::Color::White);
        m_buttons[StatesMenu::Records].setFillColor(sf::Color::Black);
    }
}