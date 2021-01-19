#include "models/Player.h"
#include <Windows.h>
#include <chrono>
#include <thread>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
//#include "GameState.h"
#include "./Resources/ResourceHolder.h"

#include "models/Floor.h"



Player::Player(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt, sf::SoundBuffer* sound) :
	DynamicObject(pos, size, 250,txt), 
	m_is_injured(false), m_life(INIT_LIFE), m_score(INIT),m_numLevel(1), m_direction_dig(INIT)

{
	// m_sbuffer.loadFromFile("player_coin.wav");
	m_sound.setBuffer(*sound);
	m_sound.setVolume(30.0f);
}

void Player::updateDirection()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_dircetion = Object_Direction::Left;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_dircetion = Object_Direction::Right;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_dircetion = Object_Direction::Up;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_dircetion = Object_Direction::Down;

	this->SaveLastPosition();

	//std::cout << m_score << std::endl;
}

void Player::handleColision(Floor& obj)
{
	if (obj.isExsist())
		this->goBack();
	else if (obj.isFull())
		this->injured();
}

bool Player::dig()
{
	sf::Vector2f vec2f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		this->m_direction_dig = Object_Direction::Left;
		return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		this->m_direction_dig = Object_Direction::Right;
		return true;
	}
	return false;

}

const sf::Vector2f& Player::getMovementDig(sf::Vector2f size) const
{
	switch (m_direction_dig)
	{
	case 1:
		return (sf::Vector2f(this->m_rec->getPosition().x - (1 * (size.x )),
			this->m_rec->getPosition().y + 1 * size.y ));
	case 2:
		return (sf::Vector2f(this->m_rec->getPosition().x + (1 * (size.x )),
			this->m_rec->getPosition().y + 1 * size.y ));
	default:
		return (sf::Vector2f(0.f, 0.f));
	}
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
	if(!m_is_injured && obj.isExsist())
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
		if(m_life < MAX_LIFE)
			this->m_life++;
	}
}

void Player::handleColision(GiftScore& obj)
{
	if (obj.isExsist())
	{
		obj.handleColision(*this);
		this->m_score += 150;
	}
}

void Player::handleColision(GiftMonster& obj)
{
	if (obj.isExsist())
	{
		obj.handleColision(*this);
	}
}

void Player::handleColision(GiftStain& obj)
{
	if (obj.isExsist())
	{
		obj.handleColision(*this);
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
