#pragma once

#include "./Machine/State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

#include <vector>


class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	virtual void			draw();
	virtual bool			update(double dt);
	virtual bool			handleEvent(const sf::Event& event);


private:
	sf::Sprite				mBackgroundSprite;
    sf::Text m_title;
	std::vector< sf::Text > m_buttons;

	sf::Sound m_sound;
	sf::Sound m_soundState;

    bool m_isPlayButtonSelected;
    bool m_isPlayButtonPressed;

    bool m_isSettingsButtonSelected;
    bool m_isSettingsButtonPressed;

    bool m_isAboutOurSelected;
    bool m_isAboutOurPressed;

    bool m_isRecordsSelected;
    bool m_isRecordsPressed;

    bool m_pressed = false;

    void updateColorButton();
    void centerOrigin(sf::Text&);

    sf::Clock m_clock;
};
