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

Player::Player(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt, sf::SoundBuffer* sound) :
	DynamicObject(pos, size, 250,txt) , m_is_injured(false), m_life(3), m_score(0),m_numLevel(1)

{
	// m_sbuffer.loadFromFile("player_coin.wav");
	m_sound.setBuffer(*sound);
	m_sound.setVolume(30.0f);
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
		m_sound.play();
		//Sleep(500);
		this->m_score += m_numLevel * 2;
	}
}


void Player::handleColision(Monster& obj)
{
	this->injured();

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
	//this->m_numLevel++;
	this->m_score += (m_numLevel - 1) * 50;

}


void Player::handleColision(GiftLife& obj)
{
	if (obj.isExsist())
	{
		obj.handleColision(*this);
		this->m_life++;
	}
}

void Player::handleColision(GiftTime& obj)
{
	if (obj.isExsist())
	{
		obj.handleColision(*this);
	}
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

void Player::newLevel() 
{
	m_numLevel++;
}


const int Player::getScore() const
{
	return m_score;
}

const int Player::getLevel() const
{
	return m_numLevel;
}

void Player::injured() 
{
	m_life--;
	// sound
	m_is_injured = true;
	Coin::resetCollected();
}

const int Player::getLife() const
{
	return m_life;
}


