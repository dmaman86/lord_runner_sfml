#pragma once

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

class PlayerInput
{
public:
	PlayerInput();
	~PlayerInput();

	void setScore(const int&);
	void setSuccess(const bool&);

	int getScore() const;
	bool getSuccess() const;

private:
	bool m_success;
	int m_score;
	sf::String m_playerInput;
	sf::Text m_playerText;
};