#pragma once

#include "Object.h"
class Floor;
class Coin;
class Ladder;
class Ropes;
class Player;
class Monster;

const float COLL_GAME_SCREEN = 1920.f;
const float ROW_GAME_SCREEN = 930.f;

class DynamicObject :public Object
{

public:
	DynamicObject(sf::Vector2f pos, sf::Vector2f size, size_t speed, sf::Texture* txt);
	virtual ~DynamicObject();
	void foo() {};
	void move(const float& dt);
	void virtual update(const float& dt,int dir);
	void virtual render(sf::RenderWindow* window) override;
	//sf::Sprite virtual getRecNextStep(); // need deleated
	void SaveLastPosition();
	void resetData();

	void goBack();

	void setFirstPos();

	sf::Vector2f& getLastPos();
	sf::Vector2f& getFirstPos();


	sf::Vector2f getMovement();
	void virtual updateDirection() = 0;
	void resetDirection();

	//void virtual handleColision(Object& obj) override;
	//void virtual handleColision(StaticObj& obj) override;
	//void virtual handleColision(Creature& obj) override;
	//void virtual handleColision(Monster& obj) override;
	//void virtual handleColision(Player& obj) override;
	void virtual handleColision(Floor& obj) ;
	void virtual handleColision(Coin& obj) ;
	void virtual handleColision(Ladder& obj) ;
	void virtual handleColision(Ropes& obj) ;

	void virtual handleColision(Monster& obj) = 0;
	void virtual handleColision(DynamicObject& obj) = 0;


	void setDirectionDown();

protected:
	// members
		// move
	size_t m_dircetion;
	size_t m_moveSpeed;
		// positions
	sf::Vector2f m_first_position;
	sf::Vector2f m_last_postion;

private:
	
};