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
    soundManager.addSound(SoundEffect::Menu, "menusound.wav");
    soundManager.addSound(SoundEffect::Game, "gamesound.wav");

	soundManager.addSound(SoundEffect::MoveState, "new_move_next_state.wav");
	soundManager.addSound(SoundEffect::Open, "open.wav");
	soundManager.addSound(SoundEffect::PlayerCoin, "player_coin.wav");

	fontManager.addFont(Fonts::Main, "arial.ttf");

	textureManager.addTexture(Textures::Game, "background.png");
	textureManager.addTexture(Textures::Menu, "background_menu.png");
	textureManager.addTexture(Textures::Splash, "splash-background.png");

	textureManager.addTexture(Textures::Coin, "coin.png");
	textureManager.addTexture(Textures::Player, "hero.png");
	textureManager.addTexture(Textures::Ladder, "ladder.png");
	textureManager.addTexture(Textures::Monster, "monster.png");
	textureManager.addTexture(Textures::Ropes, "ropes.png");
	textureManager.addTexture(Textures::Floor, "wall.png");
}