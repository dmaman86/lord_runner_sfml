#include "GameState.h"
#include "PauseState.h"

GameState::GameState( GameDataRef data ) : m_data( data ), m_isPause( false )
{
    std::ifstream fd_readLevel( getPath() );
    if( fd_readLevel.is_open() )
        read_data( fd_readLevel );
}

void GameState::Init()
{
    m_data->assets.LoadTexture( "Game Background", "../resources/img/background.png" );
    m_background.setTexture( this->m_data->assets.GetTexture( "Game Background" ) );

    if( !m_soundBuffer.loadFromFile( "../resources/sounds/gamesound.wav" ) )
        std::cout << "Error loading Open Sound Effect" << std::endl;

    m_sound.setBuffer( m_soundBuffer );

    if( !m_music.openFromFile( "../resources/sounds/gamesound.wav" ) )
        std::cout << "Error loading Open Sound Effect" << std::endl;
}

void GameState::PlaySound()
{
    // m_music.play();
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
            m_isPause = true;
    }
}

void GameState::Update( float dt )
{
    // m_music.play();
    m_board.update( dt );

    if( m_isPause )
    {
        m_isPause = false;
        m_data->machine.AddState( StateRef( new PauseState( m_data ) ), true );
    }
}

void GameState::Draw( float dt )
{
    m_data->window.clear();

    m_data->window.draw( m_background );

    m_board.renderStaticObj( &m_data->window );

    m_board.renderMonster( &m_data->window );

    m_board.renderPlayer( &m_data->window );

    m_data->window.display();
}

//Private function
std::string GameState::getPath()
{
    std::string path = "../resources/levels/Board" + std::to_string(m_numLevel) + ".txt";
    return path;
}

void GameState::read_data(std::ifstream& fd_readLevel)
{
    //std::string heightStr, weidthStr;
    size_t height, weidth;
    char c;

    fd_readLevel >> height;
    fd_readLevel >> weidth;
    this->m_board.initAvg(height, weidth);

    fd_readLevel.get(c);	//eat '\n'
    for (size_t i = 0; i < height ;i++)
    {
        for (size_t j = 0; j < weidth;j++)
        {
            fd_readLevel.get(c);
            m_board.initData(sf::Vector2f((float)j, (float)i), c);
        }
        fd_readLevel.get(c);	//eat '\n'
    }

    fd_readLevel.close();
}


