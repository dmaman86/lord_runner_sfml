#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
	static TextureManager& getInstance();

	bool addTexture(std::string name, std::string fileName);
	std::unique_ptr<sf::Texture> getTexture(std::string name);

private:
	TextureManager();
	~TextureManager();
	std::map<std::string, std::unique_ptr<sf::Texture>> texture_map;
};