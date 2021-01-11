#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

class FontManager
{
public:
	static FontManager& getInstance();

	bool addFont(std::string name, std::string fileName);
	std::unique_ptr<sf::Font> getFont(std::string name);

private:
	FontManager();
	~FontManager();
	std::map<std::string, std::unique_ptr<sf::Font>> font_map;
};