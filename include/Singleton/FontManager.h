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
	std::unique_ptr<sf::Font> getFont(Fonts::ID nameId);

private:
	FontManager();
	~FontManager();
	std::map<Fonts::ID, std::unique_ptr<sf::Font>> font_map;
};