#include "AssetManager.h"


#include <iostream>
#include <algorithm>

/*void AssetManager::LoadTexture( Textures::ID name, std::string fileName )
{
    if( m_textures.find( name ) == m_textures.end() )
        if( !this->m_textures[ name ].loadFromFile( fileName ) )
            std::cout << "Not found Texture File" << std::endl;
}

sf::Texture& AssetManager::GetTexture( Textures::ID name )
{
    return this->m_textures.at( name );
}

void AssetManager::LoadFont( Fonts::ID name, std::string fileName )
{
    sf::Font font;
    if (m_fonts.find( name ) == m_fonts.end())
        if( font.loadFromFile( fileName ) )
            this->m_fonts[ name ] = font;
}

sf::Font& AssetManager::GetFont( Fonts::ID name )
{
    return this->m_fonts.at( name );
}

void AssetManager::LoadSoundFile( std::string name, std::string fileName )
{
    if (m_sound.find(name) == m_sound.end())
        if( !this->m_sound[ name ].loadFromFile( fileName ) )
            std::cout << "Not found Sound File" << std::endl;
}

sf::SoundBuffer& AssetManager::GetSound( std::string name )
{
    return this->m_sound.at( name );
}

void AssetManager::LoadMusicFile( std::string name, std::string fileName )
{
    sf::Music *music = new sf::Music;
    if (m_music.find(name) == m_music.end())
        if( music->openFromFile( fileName ) )
        {
            this->m_music[ name ] = fileName;
        }
}


std::string& AssetManager::GetMusic( std::string name )
{
    return this->m_music.at( name );
}*/