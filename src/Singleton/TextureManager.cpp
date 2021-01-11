#include "Singleton/TextureManager.h"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

TextureManager& TextureManager::getInstance()
{
	static TextureManager instance;
	return instance;
}

bool TextureManager::addTexture(std::string name, std::string fileName)
{
	auto it = texture_map.find(name);

	if (it != texture_map.end())
	{
		std::cout << "Unable to add texture: " << name << ", already exists" << std::endl;
		return false;
	}

	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

	if (!texture->loadFromFile(fileName))
	{
		std::cout << "Unable to open texture: " << fileName << std::endl;
		return false;
	}

	texture_map.emplace(name,std::move(texture));
	return true;
}

std::unique_ptr<sf::Texture> TextureManager::getTexture(std::string name)
{
	auto it = texture_map.find(name);
	if (it == texture_map.end())
	{
		std::cout << "Unable to load texture: " << name << ", doesn't exists." << std::endl;
		return nullptr;
	}
	return std::move(it->second);
}