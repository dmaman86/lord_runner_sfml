#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button
{
	
public:
	Button(float x, float y, float width, float height,
		sf::Font* font,std::string text,
		sf::Color idelColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	//
	const bool isPressed() const;

	
	//Function
	void update(const sf::Vector2f mousepos);
	void rendr(sf::RenderTarget* target);

private:
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;



};