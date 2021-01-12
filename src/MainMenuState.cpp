#include <iostream>
#include <sstream>

#include "MainMenuState.h"
#include "GameState.h"

#include "Identifiers.h"
#include "Singleton/ResourceManager.h"

MainMenuState::MainMenuState( GameDataRef& data )
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
}

void MainMenuState::Init()
{
    sf::Vector2u textureSize, windowSize;

    m_sound = SoundManager::getInstance().getSound(SoundEffect::MoveState);


    windowSize = this->m_data->window.getSize();

    sf::Texture texture = TextureManager::getInstance().getTexture(Textures::Menu);
    textureSize = texture.getSize();
    m_background.setTexture(texture);
    m_background.setScale( ( float )windowSize.x / textureSize.x,
                           ( float )windowSize.y / textureSize.y );

    sf::Text text;
    sf::Font font = FontManager::getInstance().getFont(Fonts::Main);
    text.setFont(font);
    text.setCharacterSize( 55 );
    text.setStyle( sf::Text::Bold );

    for( size_t i = 0; i < 4; i++ )
    {
        m_buttons.push_back( text );
        m_buttons[i].setFillColor(sf::Color::White);

        m_buttons[ i ].setOrigin( m_buttons[ i ].getLocalBounds().width / 2 ,
                                  m_buttons[ i ].getLocalBounds().height / 2 );
        m_buttons[ i ].setPosition( sf::Vector2f( windowSize.x / 2.5,
                                                  ( windowSize.y / 2 ) + ( i * 100 ) ) );
    }

    m_buttons[ 0 ].setString( "Play Game" );
    m_buttons[ 1 ].setString( "Settings Game" );
    m_buttons[ 2 ].setString( "About Our" );
    m_buttons[ 3 ].setString("Records Game");

    m_sound_state = SoundManager::getInstance().getSound(SoundEffect::Menu);
    m_sound_state.setLoop(true);
    // m_sound_state.play();
}

void MainMenuState::PlaySound()
{
    m_sound_state.play();
}

void MainMenuState::HandleInput()
{
    sf::Event event;

    while (m_data->window.pollEvent(event))
    {
        if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_sound_state.stop();
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
                m_isRecordsSelected = false;
                m_pressed = true;
            }

            if ((m_isSettingsButtonPressed = m_data->input.isSpriteClicked(m_buttons[1], sf::Mouse::Left,
                m_data->window)) == true)
            {
                m_isSettingsButtonSelected = true;
                m_isPlayButtonSelected = false;
                m_isAboutOurSelected = false;
                m_isRecordsSelected = false;
                m_pressed = true;
            }


            if ((m_isAboutOurPressed = m_data->input.isSpriteClicked(m_buttons[2], sf::Mouse::Left,
                m_data->window)) == true)
            {
                m_isAboutOurSelected = true;
                m_isPlayButtonSelected = false;
                m_isSettingsButtonSelected = false;
                m_isRecordsSelected = false;
                m_pressed = true;
            }

            if ((m_isRecordsPressed = m_data->input.isSpriteClicked(m_buttons[3], sf::Mouse::Left, m_data->window)) == true)
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
        m_pressed = false;
        m_sound.play();
        if (m_clock.getElapsedTime().asSeconds() > 2.0)
        {
            // StopSound();
            m_sound_state.stop();
            m_sound.stop();
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
        m_buttons[0].setFillColor(sf::Color::Black);
        m_buttons[1].setFillColor(sf::Color::White);
        m_buttons[2].setFillColor(sf::Color::White);
        m_buttons[3].setFillColor(sf::Color::White);

    }
    else if (m_isSettingsButtonSelected)
    {
        m_buttons[0].setFillColor(sf::Color::White);
        m_buttons[1].setFillColor(sf::Color::Black);
        m_buttons[2].setFillColor(sf::Color::White);
        m_buttons[3].setFillColor(sf::Color::White);

    }
    else if (m_isAboutOurSelected)
    {
        m_buttons[0].setFillColor(sf::Color::White);
        m_buttons[1].setFillColor(sf::Color::White);
        m_buttons[2].setFillColor(sf::Color::Black);
        m_buttons[3].setFillColor(sf::Color::White);
    }
    else if( m_isRecordsSelected)
    {
        m_buttons[0].setFillColor(sf::Color::White);
        m_buttons[1].setFillColor(sf::Color::White);
        m_buttons[2].setFillColor(sf::Color::White);
        m_buttons[3].setFillColor(sf::Color::Black);
    }
}