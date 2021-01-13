#include "Application.h"
#include "./Machine/State.h"
#include "./Machine/StateIdentifiers.h"
#include "TitleState.h"
#include "GameState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "SettingsState.h"
#include "GameOverState.h"

#include <iostream>
#include <string>



Application::Application()
	: mWindow(sf::VideoMode(1920, 1080), "Lord Runner Game")
	, mTextures()
	, mFonts()
	, mSounds()
	, mInput()
	, mStateStack(State::Context(mWindow, mTextures, mFonts, mSounds, mInput))
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setVerticalSyncEnabled(true);
	mWindow.setFramerateLimit(60);

	mFonts.load(Fonts::Main, "SuperMario256.ttf");

	mTextures.load(Textures::TitleScreen, "splash-background.png");
	mTextures.load(Textures::Game, "background.png");
	mTextures.load(Textures::Menu, "background_menu_origin.png");
	mTextures.load(Textures::Player, "hero.png");
	mTextures.load(Textures::Coin, "coin.png");
	mTextures.load(Textures::Monster, "monster.png");
	mTextures.load(Textures::Ladder, "ladder.png");
	mTextures.load(Textures::Ropes, "ropes.png");
	mTextures.load(Textures::Wall, "wall.png");

	mSounds.load(SoundEffect::Open, "open.wav");
	mSounds.load(SoundEffect::Game, "gamesound.wav");
	mSounds.load(SoundEffect::Menu, "menusound.wav");
	mSounds.load(SoundEffect::Button, "new_move_next_state.wav");

	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10u);

	registerStates();
	mStateStack.pushState(States::Title);

	// mMusic.setVolume(25.f);
}

void Application::run()
{
	float newTime, frameTime, interpolation;
	float currentTime = this->m_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (mWindow.isOpen())
	{
		newTime = this->m_clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;
		if (frameTime > 0.25f)
			frameTime = 0.25f;

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= TimePerFrame)
		{
			processInput();
			update(TimePerFrame);

			accumulator -= TimePerFrame;
		}

		updateStatistics(TimePerFrame);
		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(double dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);

	mWindow.display();
}

void Application::updateStatistics(double dt)
{
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;
	if (mStatisticsUpdateTime >= 1.0f)
	{
		mStatisticsText.setString("FPS: " + std::to_string(mStatisticsNumFrames));

		mStatisticsUpdateTime -= 1.0f;
		mStatisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<SettingsState>(States::Settings);
	mStateStack.registerState<GameOverState>(States::GameOver);
}
