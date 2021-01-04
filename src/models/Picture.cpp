#include "models/Picture.h"
#include <iostream>

Picture::Picture() // constructor
{
	loadTextureName();
	loadTexture();
}

Picture::~Picture()
{

}

//====================================================
void Picture::loadTextureName()		//load from text 
{
	m_texture_name[0] = "hero.png";
	m_texture_name[1] = "monster.png";
	m_texture_name[2] = "coin.png";
	m_texture_name[3] = "wall.png";
	m_texture_name[4] = "ropes.png";
	m_texture_name[5] = "ladder.png";
}

//====================================================
void Picture::loadTexture()		//load texturs & sprits menu
{
	m_texture.resize(sizeof(m_texture_name) / sizeof(m_texture_name[0]));
	for (int i = 0; i < sizeof(m_texture_name) / sizeof(m_texture_name[0]); i++)
	{
		m_texture[i].loadFromFile(m_texture_name[i]);
	}
}

//====================================================

sf::Texture* Picture::getTxt(int i)
{
	return &this->m_texture[i];
}

