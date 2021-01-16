#pragma once

#include "models/DynamicObject.h"
#include "Coin.h"

#include <SFML/Audio.hpp>

#include "GiftLife.h"
#include "GiftTime.h"


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
	void virtual handleColision(GiftLife& obj);
	void virtual handleColision(GiftTime& obj) override;

	//void virtual handleColision(GiftTime& obj);
	//void virtual handleColision(Gift& obj) ;


	bool isInjured();
	const int getLife() const;
	const int getScore() const;
	const int getLevel() const;

	void injured();
	void newLevel();


	void newData(sf::Vector2f pos, sf::Vector2f size);


private:
	int m_life;
	int m_score;
	bool m_is_injured;
	int m_numLevel;

	
	sf::Sound m_sound;
	// sf::SoundBuffer m_sbuffer;


};