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
The root of tree inheritance
Classes inherit directly : * StaticObj * Creature

*/ 
class Object
{

public:
	// Constractor / Distactor
	Object(sf::Vector2f position, sf::Vector2f size, sf::Texture* txt); // need move name!
	virtual ~Object() ; // using inheritance, prefer virtual destractor

	const sf::Vector2f& getPositionRec() ;
	const sf::Vector2f& getSizeRec();
	const void setPosRec(sf::Vector2f& pos);
	const sf::FloatRect getGlobBounds() const;
	const void initObject(sf::Vector2f pos, sf::Vector2f avgPix, sf::Texture*);

	bool collisionWith(const Object& obj) const;
	
	// Pure virtual functions 
	void virtual render(sf::RenderWindow* target);

	//void virtual handleColision(Object& obj) = 0;
	//void virtual handleColision(StaticObj& obj) = 0;
	//void virtual handleColision(Creature& obj) = 0;
	//void virtual handleColision(Monster& obj) = 0;
	//void virtual handleColision(Player& obj) = 0;
	//void virtual handleColision(Flor& obj) = 0;

protected:
	sf::Sprite* m_rec;
	// sf::Texture m_txt;
private:

}; // end Object