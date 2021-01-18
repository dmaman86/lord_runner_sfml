#pragma once

#include "Object.h"

class Floor;
class Coin;
class Ladder;
class Ropes;
class Player;
class Monster;
class Gift;
class GiftLife;
class GiftTime;
class GiftScore;
class GiftMonster;
class GiftStain;


const float COLL_GAME_SCREEN = 1920.f;
const float ROW_GAME_SCREEN = 930.f;

class DynamicObject :public Object
{

public:
	// Constractor / Distactor
	DynamicObject
	(sf::Vector2f pos, sf::Vector2f size, size_t speed, sf::Texture* txt);
	virtual ~DynamicObject();

	// public functions
		// movment
	void resetData();
	void setDirectionDown();
	void move(const float& dt);
	void virtual goBack();
	void setFirstPos();
	const sf::Vector2f& getPosition() const;
	void virtual setGrid(char**, int, int) {};


	// ============= pure virtual functions ===============
	void virtual updateDirection() = 0;
	void virtual handleColision(DynamicObject& obj) = 0;
	void virtual handleColision(Player& obj) = 0;
	void virtual handleColision(Monster& obj) = 0;
	void virtual handleColision(Coin& obj) = 0;
	void virtual handleColision(GiftLife& obj) = 0;
	void virtual handleColision(GiftTime& obj) = 0;
	void virtual handleColision(GiftScore& obj) = 0;
	void virtual handleColision(GiftMonster& obj) = 0;
	void virtual handleColision(GiftStain& obj) = 0;

	// ============= virual functions =====================
	void virtual handleColision(Floor& obj) = 0;
	void virtual handleColision(Ladder& obj);
	void virtual handleColision(Ropes& obj);

protected:
	// members
		// move
	size_t m_dircetion;
	size_t m_moveSpeed;
		// positions
	sf::Vector2f m_first_position;
	sf::Vector2f m_last_postion;

	// private functions
		// Auxiliary functions
	void resetDirection();
	void SaveLastPosition();
		// Get functions
	const sf::Vector2f& getMovement() const;
	const sf::Vector2f& getLastPos() const;
	const sf::Vector2f& getFirstPos() const;

private:
	
}; // end DynamicObject