#include "Singleton/ResourceManager.h"

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
	musicManager.addMusic("Menu Music", "menusound.wav");
	musicManager.addMusic("Game Music", "gamesound.wav");

	soundManager.addSound("Next State", "new_move_next_state.wav");
	soundManager.addSound("Open State", "open.wav");

	fontManager.addFont("Font Game", "arial.ttf");

	textureManager.addTexture("BackGround Game", "background.png");
	textureManager.addTexture("BackGround Menu", "background_menu.png");
	textureManager.addTexture("BackGround Open", "splash_background.png");

	textureManager.addTexture("Coin Game", "coin.png");
	textureManager.addTexture("Hero Game", "hero.png");
	textureManager.addTexture("Ladder Game", "ladder.png");
	textureManager.addTexture("Monster Game", "monster.png");
	textureManager.addTexture("Ropes Game", "ropes.png");
	textureManager.addTexture("Floor Game", "wall.png");
}