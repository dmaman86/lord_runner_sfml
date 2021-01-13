#include "models/Player.h"
#include <Windows.h>
#include <chrono>
#include <thread>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "GameState.h"
#include "./Resources/ResourceHolder.h"

Player::Player(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	DynamicObject(pos, size, 250,txt) ,
	m_life(3),m_score(0),m_is_injured(false), m_coin_collected(0)
{
	m_sbuffer.loadFromFile("player_coin.wav");
	m_sound.setBuffer(m_sbuffer);
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
		m_coin_collected++;
		m_sound.play();
		//Sleep(500);
		this->m_score ++;
	}
}

void Player::handleColision(Monster& obj)
{
	m_life--;
	// sound
	m_is_injured = true;

	//std::this_thread::sleep_for(std::chrono::seconds(10));
}

void Player::newData(sf::Vector2f pos, sf::Vector2f avgPix)
{
	m_rec->setScale(
		(avgPix.x / (m_rec->getTexture()->getSize().x)),
		(avgPix.y / (m_rec->getTexture()->getSize().y)));
	this->m_rec->setScale(m_rec->getScale() * (float)0.8);
	//m_rec->setOrigin(avgPix.x / 2.f, avgPix.y / 2.f);
	m_rec->setPosition(sf::Vector2f((pos.x * avgPix.x + avgPix.x / 2u),
		((pos.y * avgPix.y) + avgPix.y / 2u )));
	//(sf::Vector2f((pos.x * avgPix.x) + avgPix.x / 2u, (pos.y * avgPix.y) + avgPix.y / 2u));

	this->m_first_position = m_rec->getPosition();
	this->m_coin_collected = 0;

}


bool Player::isInjured()
{
	if (m_is_injured)
	{
		m_is_injured = false;
		this->m_coin_collected = 0;
		return true;
	}
	return false;
}

int Player::getCoinCollected()
{
	return  this->m_coin_collected;
}

int Player::getLife()
{
	return m_life;
}


