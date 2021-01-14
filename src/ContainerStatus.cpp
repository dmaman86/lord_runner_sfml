#include "ContainerStatus.h"

ContainerStatus::ContainerStatus(sf::Texture* txt, sf::Font* fnt)
{
	this->m_heart.setTexture(*txt);
	m_heart.setScale(0.15, 0.15);
	m_heart.setPosition(0, ROW + 50);

	this->m_textLevel.setFont(*fnt);
	m_textLevel.setPosition(900, ROW + 50 );
	m_textLevel.setFillColor(sf::Color::White);

	this->m_textScore.setFont(*fnt);
	m_textScore.setPosition(600, ROW + 50);
	m_textScore.setFillColor(sf::Color::White);
	
	
}

ContainerStatus::~ContainerStatus()
{

}

void ContainerStatus::renderStatus(Player& p, sf::RenderWindow* window, int m_level)
{
	m_textScore.setString("Score: " + std::to_string(p.getScore()));
	m_textLevel.setString("Level: " + std::to_string(m_level));


	for (int i = 0; i < p.getLife();i++)
	{
		m_heart.setPosition(i * 100, ROW + 50);
		window->draw(m_heart);
	}
	
	window->draw(m_textScore);
	window->draw(m_textLevel);


}
