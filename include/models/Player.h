#pragma once

#include "models/DynamicObject.h"
#include "Coin.h"

#include <SFML/Audio.hpp>

class Monster;

class Player : public DynamicObject
{
	
public:
	Player(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt, sf::SoundBuffer * sound);
	void virtual updateDirection() override;
	void virtual handleColision(Coin& obj);
	void virtual handleColision(Monster& obj) override;
	void virtual handleColision(DynamicObject& obj) {};
	void virtual handleColision(Player& obj) {};

	bool isInjured();
	int getCoinCollected();
	int getLife();

	void newData(sf::Vector2f pos, sf::Vector2f size);


private:
	static int m_life;
	static int m_score;
	bool m_is_injured;
	
	
	sf::Sound m_sound;
	// sf::SoundBuffer m_sbuffer;


};