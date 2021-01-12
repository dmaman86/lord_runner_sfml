#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Identifiers.h"

class FontManager
{
public:
	static FontManager& getInstance();

	bool addFont(Fonts::ID nameId, std::string fileName);
	sf::Font& getFont(Fonts::ID nameId);

private:
	FontManager();
	~FontManager();
	std::map<Fonts::ID, sf::Font> font_map;
};