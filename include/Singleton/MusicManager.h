#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <SFML/Audio.hpp>

class MusicManager
{
public:
	static MusicManager& getInstance();

	bool addMusic(std::string name, std::string fileName);
	std::unique_ptr<sf::Music> getMusic(std::string name);

private:
	MusicManager();
	~MusicManager();

	std::map<std::string, std::unique_ptr<sf::Music>> music_map;
	std::vector<sf::Music> music_vec;
};