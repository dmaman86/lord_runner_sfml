#pragma once

#include "./Machine/State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>


class SettingsState : public State
{
public:
	SettingsState(StateStack& stack, Context context);

	virtual void					draw();
	virtual bool					update(double dt);
	virtual bool					handleEvent(const sf::Event& event);


private:
	void							updateLabels();
	void							addButtonLabel(float y, const std::string& text, Context context);


private:
	sf::Sprite											mBackgroundSprite;
};