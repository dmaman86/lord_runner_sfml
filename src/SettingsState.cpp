#include "SettingsState.h"
#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"

#include <SFML/Graphics/RenderWindow.hpp>


SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context), m_backToMenu(false), mEffectTime(0.0f)
{

	m_avaibleMusicSelected = false;
	m_avaibleMusicPressed = false;
	m_pressed = false;
	m_no_avaibleMusicSelected = false;
	m_no_avaibleMusicPressed = false;

	sf::Vector2u textureSize, windowSize;

	windowSize = context.window->getSize();
	textureSize = context.textures->get(Textures::Menu).getSize();

	sf::Texture& texture = context.textures->get(Textures::Menu);
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale((float)windowSize.x / textureSize.x,
		(float)windowSize.y / textureSize.y);

	m_soundState.setBuffer(context.sounds->get(SoundEffect::Menu));
	m_soundState.setLoop(true);
	m_sound.setBuffer(context.sounds->get(SoundEffect::Button));
	m_sound.setPlayingOffset(sf::seconds(2.f));

	sf::Text text;
	sf::Font& font = context.fonts->get(Fonts::Main);
	m_title.setFont(font);
	m_title.setString("Settings");
	m_title.setFillColor(sf::Color(76, 0, 153));
	m_title.setCharacterSize(100);
	centerOrigin(m_title);
	m_title.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

	text.setFont(font);
	text.setCharacterSize(55);
	text.setStyle(sf::Text::Bold);

	for (size_t i = 0; i < MaxButtonsInState::SettingsButtons; i++)
	{
		m_buttons.push_back(text);
		m_buttons[i].setFillColor(sf::Color::White);

		m_buttons[i].setOrigin(m_buttons[i].getLocalBounds().width / 2,
			m_buttons[i].getLocalBounds().height / 2);
		m_buttons[i].setPosition(sf::Vector2f(windowSize.x / 2.5,
			(windowSize.y / 2) + (i * 100)));
	}

	m_buttons[0].setString("Avaible Music");
	m_buttons[1].setString("No Avaible Music");

	m_soundState.play();
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);

	window.draw(m_title);

	window.draw(mousePicture);

	for (auto button : m_buttons)
		window.draw(button);

}

bool SettingsState::update(double dt)
{
	if (m_pressed)
	{
		mEffectTime += dt;
		updateColorButton();
		if (mEffectTime >= 1.0f)
		{
			m_pressed = false;
			mEffectTime = 0.0f;
			if (m_avaibleMusicSelected || m_no_avaibleMusicSelected )
			{
				requestStackPop();
				requestStackPush(States::Menu);
			}
			else if (m_backToMenu)
			{
				m_soundState.stop();
				requestStackPop();
				requestStackPush(States::Menu);
			}
		}
	}

	this->updateCursor();

	return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	sf::RenderWindow& window = *getContext().window;
	InputManager* input = getContext().input;

	if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_soundState.stop();
		// requestStackPop();
		requestStateClear();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		m_backToMenu = true;
		m_pressed = true;
	}

	if (event.MouseButtonPressed)
	{

		if (m_avaibleMusicPressed = input->isSpriteClicked(m_buttons[0], sf::Mouse::Left, window))
		{
			m_avaibleMusicSelected = true;
			m_no_avaibleMusicSelected = false;
			m_pressed = true;
			getContext().playerInput->setUserSound(true);
			m_sound.play();
		}

		if (m_no_avaibleMusicPressed = input->isSpriteClicked(m_buttons[1], sf::Mouse::Left, window))
		{
			m_no_avaibleMusicSelected = true;
			m_avaibleMusicSelected = false;
			m_pressed = true;
			getContext().playerInput->setUserSound(false);
			m_sound.play();
		}
		return true;
	}
	return false;
}

void SettingsState::centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
		std::floor(bounds.top + bounds.height / 2.f));
}

void SettingsState::updateColorButton()
{
	if (m_avaibleMusicSelected)
	{
		m_buttons[0].setFillColor(sf::Color::Black);
		m_buttons[1].setFillColor(sf::Color::White);
	}
	else if (m_no_avaibleMusicSelected)
	{
		m_buttons[0].setFillColor(sf::Color::White);
		m_buttons[1].setFillColor(sf::Color::Black);
	}
}
