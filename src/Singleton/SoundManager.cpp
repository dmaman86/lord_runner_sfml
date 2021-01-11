#include "Singleton/SoundManager.h"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{

}

SoundManager& SoundManager::getInstance()
{
	static SoundManager instance;
	return instance;
}

bool SoundManager::addSound(std::string name, std::string fileName)
{
	auto it = sound_map.find(name);

	if (it != sound_map.end())
	{
		std::cout << "Sound already exists!" << std::endl;
		return false;
	}

	std::unique_ptr<sf::SoundBuffer> soundBuffer = std::make_unique<sf::SoundBuffer>();

	if (!soundBuffer->loadFromFile(fileName))
	{
		std::cout << "Unable to open sound " << fileName << std::endl;
		return false;
	}

	soundBuffer_vec.push_back(std::move(*(soundBuffer)));
	unsigned int soundBufferVecSize = soundBuffer_vec.size();
	std::unique_ptr<sf::Sound> sound = std::make_unique<sf::Sound>(std::move(soundBuffer_vec[soundBufferVecSize - 1]));

	sound_map.emplace(name, std::move(sound));
	return true;
}

std::unique_ptr<sf::Sound> SoundManager::getSound(std::string name)
{
	auto it = sound_map.find(name);

	if (it == sound_map.end())
	{
		std::cout << "Unable to load sound " << name << ", doesn't exist" << std::endl;
		return nullptr;
	}
	return std::move(it->second);
}