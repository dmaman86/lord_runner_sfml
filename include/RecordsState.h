#pragma once

#include "./Machine/State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

#include <vector>

class RecordsState : public State
{
public:
	RecordsState(StateStack& stack, Context context);

	virtual void			draw();
	virtual bool			update(double dt);
	virtual bool			handleEvent(const sf::Event& event);

private:
	sf::Sprite mBackgroundSprite;
	sf::Texture m_title;

	sf::Sound m_soundState;

	bool m_backToMenu;
};