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

bool MusicManager::addMusic(Music::ID nameId, std::string fileName)
{
	auto it = music_map.find(nameId);

	if (it != music_map.end())
	{
		std::cout << "Music already exists!" << std::endl;
		return false;
	}
	sf::Music *song = new sf::Music;

	if( !song->openFromFile( fileName ) )
    {
        std::cout << "Unable to open music: " << fileName << std::endl;
        return false;
    }


	/*sf::Music* const song = new sf::Music();

	if (!song->openFromFile(fileName))
	{
		std::cout << "Unable to open music: " << fileName << std::endl;
		return false;
	}*/

	/*if (!music.openFromFile(fileName))
	{
		std::cout << "Unable to open music: " << fileName << std::endl;
		return false;
	}*/

	// music_vec.push_back(std::move(song));
	// size_t musicBufferVecSize = music_vec.size();
	// std::unique_ptr<sf::Music> mus = std::make_unique<sf::Music>(std::move(music_vec[musicBufferVecSize - 1]));

	// music_map.emplace(nameId, std::move(song));
	music_map.emplace(nameId, std::move(song));
	return true;
}

sf::Music& MusicManager::getMusic(Music::ID nameId)
{
    sf::Music *music = nullptr;
	auto it = music_map.find(nameId);

	if (it == music_map.end())
	{
		std::cout << "Unable to load music, doesn't exist" << std::endl;
		return *music;
	}
	return *music_map.at(nameId);
}