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

bool TextureManager::addTexture(Textures::ID nameId, std::string fileName)
{
	auto it = texture_map.find(nameId);

	if (it != texture_map.end())
	{
		std::cout << "Unable to add texture, already exists" << std::endl;
		return false;
	}

	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

	if (!texture->loadFromFile(fileName))
	{
		std::cout << "Unable to open texture: " << fileName << std::endl;
		return false;
	}

	texture_map.emplace(nameId,std::move(texture));
	return true;
}

std::unique_ptr<sf::Texture> TextureManager::getTexture(Textures::ID nameId)
{
	auto it = texture_map.find(nameId);
	if (it == texture_map.end())
	{
		std::cout << "Unable to load texture, doesn't exists." << std::endl;
		return nullptr;
	}
	return std::move(it->second);
}