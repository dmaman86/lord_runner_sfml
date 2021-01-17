#include "PlayerInput.h"

PlayerInput::PlayerInput()
{
	this->m_score = 0;
}

PlayerInput::~PlayerInput()
{

}

void PlayerInput::setScore(const int& sc)
{
	this->m_score = sc;
}

void PlayerInput::setSuccess(const bool& scs)
{
	this->m_success = scs;
}

int PlayerInput::getScore() const
{
	return this->m_score;
}
bool PlayerInput::getSuccess() const
{
	return this->m_success;
}