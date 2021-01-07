#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Identifiers.h"

class AssetManager{
public:
    AssetManager(){}
    ~AssetManager(){}

    void LoadTexture( Textures::ID name, std::string fileName );
    sf::Texture& GetTexture( Textures::ID name );

    void LoadFont( std::string name, std::string fileName );
    sf::Font& GetFont( std::string name );

    void LoadSoundFile( std::string name, std::string fileName );
    sf::SoundBuffer& GetSound( std::string name );

    void LoadMusicFile( std::string name, std::string fileName );
    std::string& GetMusic( std::string name );


private:
    std::map< Textures::ID, sf::Texture > m_textures;
    std::map< std::string, sf::Font > m_fonts;
    std::map< std::string, sf::SoundBuffer > m_sound;
    std::map< std::string, std::string > m_music;
};