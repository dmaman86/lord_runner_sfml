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

bool TextureManager::addTexture(Textures::ID nameId, std::string fileName) {
    auto it = texture_map.find(nameId);

    if (it != texture_map.end()) {
        std::cout << "Unable to add texture, already exists" << std::endl;
        return false;
    }

    /*sf::Texture *texture = new sf::Texture;

    if (!texture->loadFromFile(fileName))
    {
        std::cout << "Unable to open texture: " << fileName << std::endl;
        return false;
    }

    texture_map.emplace(nameId,texture);*/

    if (!this->texture_map[nameId].loadFromFile(fileName)) {
        std::cout << "Unable to open texture" << std::endl;
        return false;
    }
    return true;
}

sf::Texture& TextureManager::getTexture(Textures::ID nameId)
{
    sf::Texture *text = nullptr;

	auto it = texture_map.find(nameId);
	if (it == texture_map.end())
	{
		std::cout << "Unable to load texture, doesn't exists." << std::endl;
		return *text;
	}
	text = &it->second;

	return *text;
}