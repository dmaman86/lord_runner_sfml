#include "Singleton/MusicManager.h"

MusicManager::MusicManager()
{

}

MusicManager::~MusicManager()
{

}

MusicManager& MusicManager::getInstance()
{
	static MusicManager instance;
	return instance;
}

bool MusicManager::addMusic(std::string name, std::string fileName)
{
	auto it = music_map.find(name);

	if (it != music_map.end())
	{
		std::cout << "Music already exists!" << std::endl;
		return false;
	}

	std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();

	if (!music->openFromFile(fileName))
	{
		std::cout << "Unable to open music: " << fileName << std::endl;
		return false;
	}

	music_vec.push_back(std::move(*(music)));
	size_t musicBufferVecSize = music_vec.size();
	std::unique_ptr<sf::Music> mus = std::make_unique<sf::Music>(std::move(music_vec[musicBufferVecSize - 1]));

	music_map.emplace(name, std::move(music));
	return true;
}

std::unique_ptr<sf::Music> MusicManager::getMusic(std::string name)
{
	auto it = music_map.find(name);

	if (it == music_map.end())
	{
		std::cout << "Unable to load music: " << name << ", doesn't exist" << std::endl;
		return nullptr;
	}
	return std::move(it->second);
}