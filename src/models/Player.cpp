#include "models/Player.h"

Player::Player(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	DynamicObject(pos, size, 250,txt) ,m_life(0),m_score(0)
{

}

void Player::updateDirection()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_dircetion = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_dircetion = 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_dircetion = 3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_dircetion = 4;

	this->SaveLastPosition();

	//std::cout << m_score << std::endl;
}

void Player::handleColision(Coin& obj)
{
	if (obj.isExsist())
	{
		obj.handleColision(*this);
		this->m_score++;
	}
}


