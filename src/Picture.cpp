#include "Picture.h"
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
	m_texture_name[0] = "../resources/img/hero.png";
	m_texture_name[1] = "../resources/img/monster.png";
	m_texture_name[2] = "../resources/img/coin.png";
	m_texture_name[3] = "../resources/img/wall.png";
	m_texture_name[4] = "../resources/img/ropes.png";
	m_texture_name[5] = "../resources/img/ladder.png";
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

