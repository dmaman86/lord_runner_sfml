#include "models/Player.h"
#include <Windows.h>
#include <chrono>
#include <thread>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

Player::Player(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	DynamicObject(pos, size, 250,txt) ,m_life(0),m_score(0),m_is_injured(false)
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
		// m_sound.play();
		this->m_score++;
	}
}

void Player::handleColision(Monster& obj)
{
	m_life--;
	// sound
	m_is_injured = true;

	//std::this_thread::sleep_for(std::chrono::seconds(10));
}

bool Player::isInjured()
{
	if (m_is_injured)
	{
		m_is_injured = false;
		return true;
	}
	return false;
}


