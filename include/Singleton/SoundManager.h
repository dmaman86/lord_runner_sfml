#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <SFML/Audio.hpp>

class SoundManager
{
public:
	static SoundManager& getInstance();

	bool addSound(std::string name, std::string fileName);
	std::unique_ptr<sf::Sound> getSound(std::string name);

private:
	SoundManager();
	~SoundManager();

	std::map<std::string, std::unique_ptr<sf::Sound>> sound_map;
	std::vector<sf::SoundBuffer> soundBuffer_vec;
};