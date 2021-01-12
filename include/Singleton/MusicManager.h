#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <SFML/Audio.hpp>

#include "Identifiers.h"

class MusicManager
{
public:
	static MusicManager& getInstance();

	bool addMusic(Music::ID nameId, std::string fileName);
	sf::Music* getMusic(Music::ID nameId);

private:
	MusicManager();
	~MusicManager();

	std::map<Music::ID, sf::Music*> music_map;
	std::vector<sf::Music*> music_vec;
};