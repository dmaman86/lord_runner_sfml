#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Picture
{
public:
	Picture();
	~Picture();
	void loadTextureName();		//
	void loadTexture();         //load texturs & sprits menu
	sf::Texture* getTxt(int);
private:

protected:
	std::string m_texture_name[6]; // 
	std::vector<sf::Texture> m_texture;
};