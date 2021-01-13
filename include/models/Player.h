#pragma once

#include "models/DynamicObject.h"
#include "Coin.h"

class Monster;

class Player : public DynamicObject
{
	
public:
	Player(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	void virtual updateDirection() override;
	void virtual handleColision(Coin& obj);
	void virtual handleColision(Monster& obj) override;
	void virtual handleColision(DynamicObject& obj) {};
	bool isInjured();
	int getCoinCollected();
	int getLife();

	void newData(sf::Vector2f pos, sf::Vector2f size);


private:
	int m_life;
	int m_score;
	bool m_is_injured;
	
	int m_coin_collected;
	
	sf::Sound m_sound;
	sf::SoundBuffer m_sbuffer;


};