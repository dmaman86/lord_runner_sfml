#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Identifiers.h"

class TextureManager
{
public:
	static TextureManager& getInstance();

	bool addTexture(Textures::ID nameId, std::string fileName);
	sf::Texture& getTexture(Textures::ID nameId);

private:
	TextureManager();
	~TextureManager();
	std::map<Textures::ID, sf::Texture> texture_map;
};