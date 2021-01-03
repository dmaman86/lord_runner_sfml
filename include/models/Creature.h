#pragma once

#include "Object.h"
class Flor;
class Coin;
class Ladder;
class Ropes;


const float COLL_GAME_SCREEN = 1920.f;
const float ROW_GAME_SCREEN = 930.f;

class Creature :public Object
{

public:
	Creature(sf::Vector2f pos, sf::Vector2f size, size_t speed, sf::Texture* txt);
	virtual ~Creature();
	void foo() {};
	void move(const float& dt);
	void virtual update(const float& dt,int dir);
	void virtual render(sf::RenderWindow* window)override;
//	sf::RectangleShape virtual getRecNextStep(const float& );
	sf::Sprite virtual getRecNextStep();
	void SaveLastPosition();
	void resetData();

	sf::Vector2f getMovement();
	void virtual setDirection() = 0;
	void resetDirection();

	//void virtual handleColision(Object& obj) override;
	//void virtual handleColision(StaticObj& obj) override;
	//void virtual handleColision(Creature& obj) override;
	//void virtual handleColision(Monster& obj) override;
	//void virtual handleColision(Player& obj) override;
	void virtual handleColision(Flor& obj) ;
	void virtual handleColision(Coin& obj) ;
	void virtual handleColision(Ladder& obj) ;
	void virtual handleColision(Ropes& obj) ;

	void setDir();

protected:
	
	size_t m_dircetion;
	size_t m_moveSpeed;
	sf::Vector2f m_last_postion;


private:
	
};