#include "Application.h"
#include "./Machine/State.h"
#include "./Machine/StateIdentifiers.h"
#include "TitleState.h"
#include "GameState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "SettingsState.h"
#include "GameOverState.h"
#include "AboutOurState.h"
#include "RecordsState.h"

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

	loadFonts();
	loadTextures();
	loadSounds();

	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10u);

	registerStates();
	mStateStack.pushState(States::Title);
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

			if (mStateStack.isEmpty())
				mWindow.close();
		}

		// updateStatistics(TimePerFrame);
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
	// mWindow.draw(mStatisticsText);

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
	mStateStack.registerState<AboutOurState>(States::AboutOur);
	mStateStack.registerState<RecordsState>(States::Records);
}

void Application::loadFonts()
{
	this->mFonts.load(Fonts::Main, "SuperMario256.ttf");
}

void Application::loadTextures()
{
	this->mTextures.load(Textures::TitleScreen, "splash-background.png");
	this->mTextures.load(Textures::Game, "background.png");
	this->mTextures.load(Textures::Menu, "background_menu_origin.png");
	this->mTextures.load(Textures::Player, "hero.png");
	this->mTextures.load(Textures::Coin, "coin.png");
	this->mTextures.load(Textures::Monster, "monster.png");
	this->mTextures.load(Textures::Ladder, "ladder.png");
	this->mTextures.load(Textures::Ropes, "ropes.png");
	this->mTextures.load(Textures::Wall, "wall.png");
	this->mTextures.load(Textures::Heart, "heart.png");
	this->mTextures.load(Textures::Gifts, "gift.png");
	this->mTextures.load(Textures::Stain, "black_stain.png");



}

void Application::loadSounds()
{
	this->mSounds.load(SoundEffect::Open, "open.wav");
	this->mSounds.load(SoundEffect::Game, "gamesound.wav");
	this->mSounds.load(SoundEffect::Menu, "menusound.wav");
	this->mSounds.load(SoundEffect::Button, "new_move_next_state.wav");
	this->mSounds.load(SoundEffect::PlayerCoin, "player_coin.wav");
	this->mSounds.load(SoundEffect::PlayerDead, "player_dead.wav");
	this->mSounds.load(SoundEffect::StartLevelClock, "start_level_clock.wav");
	this->mSounds.load(SoundEffect::EndTime, "end_of_time.wav");

}

