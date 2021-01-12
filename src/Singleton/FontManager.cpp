#include "Singleton/FontManager.h"

FontManager::FontManager()
{

}

FontManager::~FontManager()
{

}

FontManager& FontManager::getInstance()
{
	static FontManager instance;
	return instance;
}

bool FontManager::addFont(Fonts::ID nameId, std::string fileName)
{
	auto it = font_map.find(nameId);

	if (it != font_map.end())
	{
		std::cout << "Unable to add font: " << fileName << ", already exists" << std::endl;
		return false;
	}

	std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();

	if (!font->loadFromFile(fileName))
	{
		std::cout << "Unable to open font: " << fileName << std::endl;
		return false;
	}

	font_map.emplace(nameId, std::move(font));
	return true;
}

std::unique_ptr<sf::Font> FontManager::getFont(Fonts::ID nameId)
{
	auto it = font_map.find(nameId);
	if (it == font_map.end())
	{
		std::cout << "Unable to load font, doesn't exists." << std::endl;
		return nullptr;
	}
	return std::move(it->second);
}