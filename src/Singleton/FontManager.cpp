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

bool FontManager::addFont(std::string name, std::string fileName)
{
	auto it = font_map.find(name);

	if (it != font_map.end())
	{
		std::cout << "Unable to add font: " << name << ", already exists" << std::endl;
		return false;
	}

	std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();

	if (!font->loadFromFile(fileName))
	{
		std::cout << "Unable to open font: " << fileName << std::endl;
		return false;
	}

	font_map.emplace(name, std::move(font));
	return true;
}

std::unique_ptr<sf::Font> FontManager::getFont(std::string name)
{
	auto it = font_map.find(name);
	if (it == font_map.end())
	{
		std::cout << "Unable to load font: " << name << ", doesn't exists." << std::endl;
		return nullptr;
	}
	return std::move(it->second);
}