#pragma once

#include "FontManager.h"
#include "MusicManager.h"
#include "TextureManager.h"
#include "SoundManager.h"

class ResourceManager {
public:
	static ResourceManager& getInstance();

	void loadResource();

private:
	ResourceManager();
	~ResourceManager();

	FontManager& fontManager = FontManager::getInstance();
	// MusicManager& musicManager = MusicManager::getInstance();
	TextureManager& textureManager = TextureManager::getInstance();
	SoundManager& soundManager = SoundManager::getInstance();
};