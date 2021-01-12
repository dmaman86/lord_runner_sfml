#include "Singleton/ResourceManager.h"
#include "Identifiers.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

ResourceManager& ResourceManager::getInstance()
{
	static ResourceManager instance;
	return instance;
}

void ResourceManager::loadResource()
{
	musicManager.addMusic(Music::ID::Menu, "menusound.wav");
	musicManager.addMusic(Music::ID::Game, "gamesound.wav");

	soundManager.addSound(SoundEffect::ID::MoveState, "new_move_next_state.wav");
	soundManager.addSound(SoundEffect::ID::Open, "open.wav");
	soundManager.addSound(SoundEffect::ID::PlayerCoin, "player_coin.wav");

	fontManager.addFont(Fonts::ID::Main, "arial.ttf");

	textureManager.addTexture(Textures::ID::Game, "background.png");
	textureManager.addTexture(Textures::ID::Menu, "background_menu.png");
	textureManager.addTexture(Textures::ID::Splash, "splash_background.png");

	textureManager.addTexture(Textures::ID::Coin, "coin.png");
	textureManager.addTexture(Textures::ID::Player, "hero.png");
	textureManager.addTexture(Textures::ID::Ladder, "ladder.png");
	textureManager.addTexture(Textures::ID::Monster, "monster.png");
	textureManager.addTexture(Textures::ID::Ropes, "ropes.png");
	textureManager.addTexture(Textures::ID::Floor, "wall.png");
}