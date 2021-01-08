#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// forward declaration
class StaticObject;
class DynamicObject;
class Monster;
class Player;



/* ================================================
Abstract class Object

Classes inherit directly : 1. StaticObject - absract class 
						   2. DynamicObject - absract class 
*/ 
class Object
{

public:
	// Constractor / Distactor
	Object(sf::Vector2f position, sf::Vector2f size, sf::Texture* txt); 
	virtual ~Object() ; 

	const sf::Vector2f& getPositionRec() ;

	bool collisionWith(const Object& obj) const;
	
	void virtual render(sf::RenderWindow* target);

	// Pure virtual functions 

	//void virtual handleColision(Object& obj) = 0;
	//void virtual handleColision(StaticObj& obj) = 0;
	//void virtual handleColision(Creature& obj) = 0;
	//void virtual handleColision(Monster& obj) = 0;
	//void virtual handleColision(Player& obj) = 0;
	//void virtual handleColision(Flor& obj) = 0;

protected:
	sf::Sprite* m_rec;

private:

}; // end Object