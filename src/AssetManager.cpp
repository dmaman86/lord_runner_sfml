#include "AssetManager.h"

#include <iostream>

void AssetManager::LoadTexture( std::string name, std::string fileName )
{
    sf::Texture tex;

    if( tex.loadFromFile( fileName ) )
        this->m_textures[ name ] = tex;
}

sf::Texture& AssetManager::GetTexture( std::string name )
{
    return this->m_textures.at( name );
}

void AssetManager::LoadFont( std::string name, std::string fileName )
{
    sf::Font font;

    if( font.loadFromFile( fileName ) )
        this->m_fonts[ name ] = font;
}

sf::Font& AssetManager::GetFont( std::string name )
{
    return this->m_fonts.at( name );
}

void AssetManager::LoadSoundFile( std::string name, std::string fileName )
{
    /*sf::SoundBuffer soundBuffer;

    if( soundBuffer.loadFromFile( fileName ) )
    {
        this->m_sound[ name ] = soundBuffer;
    }*/

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

    if( music->openFromFile( fileName ) )
    {
        this->m_music[ name ] = fileName;
    }
}


std::string& AssetManager::GetMusic( std::string name )
{
    return this->m_music.at( name );
}