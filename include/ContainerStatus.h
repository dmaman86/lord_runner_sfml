#pragma once

#include <SFML/Graphics.hpp>
#include "./models/Player.h"


const float ROW = 930.f;

class ContainerStatus
{
public:
	ContainerStatus(sf::Texture *,sf::Font *);
	~ContainerStatus();

	void renderStatus( Player & ,sf::RenderWindow* window,int m_level);
private:
	sf::Sprite m_heart;
	sf::Text m_textLevel;
	sf::Text m_textScore;

}; // end ContainerStatus 