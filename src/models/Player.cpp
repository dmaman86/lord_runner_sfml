#include "models/Player.h"

Player::Player(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	DynamicObject(pos, size, 250,txt) ,m_life(0),m_score(0)
{

}

void Player::setDirection()
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
}

void Player::initPlayer(sf::Vector2f pos, sf::Vector2f avgPix, sf::Texture * txt)
{
	Object::initObject(pos, avgPix, txt);
}
