#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <SFML/Audio.hpp>

#include "Identifiers.h"

class SoundManager
{
public:
	static SoundManager& getInstance();

	bool addSound(SoundEffect::ID nameId, std::string fileName);
	std::unique_ptr<sf::Sound> getSound(SoundEffect::ID nameId);

private:
	SoundManager();
	~SoundManager();

	std::map<SoundEffect::ID, std::unique_ptr<sf::Sound>> sound_map;
	std::vector<sf::SoundBuffer> soundBuffer_vec;
};