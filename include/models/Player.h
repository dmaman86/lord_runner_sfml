#pragma once

#include "models/DynamicObject.h"
#include "Coin.h"
#include "Singleton/ResourceManager.h"

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


private:
	int m_life;
	int m_score;
	bool m_is_injured;
	
	std::unique_ptr<sf::Sound>m_sound;
};