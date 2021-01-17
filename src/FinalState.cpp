#include "FinalState.h"
#include "./Resources/ResourceHolder.h"
#include "./Resources/ResourceIdentifiers.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


FinalState::FinalState(StateStack& stack, Context context)
	: State(stack, context), mElapsedTime(0.0f), m_backToMenu(false)
{
	sf::Vector2u textureSize, windowSize;

	windowSize = context.window->getSize();
	textureSize = context.textures->get(Textures::Menu).getSize();

	sf::Texture& texture = context.textures->get(Textures::Menu);
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setScale((float)windowSize.x / textureSize.x,
		(float)windowSize.y / textureSize.y);

	m_soundState.setBuffer(context.sounds->get(SoundEffect::Menu));
	m_soundState.setLoop(true);

	sf::Font& font = context.fonts->get(Fonts::Main);
	m_title.setFont(font);
	if (context.playerInput->getSuccess())
		m_title.setString("Congratulations!You Win!!\n\tYour score is: " + std::to_string(context.playerInput->getScore()));
	else
		m_title.setString("Sorry, You Lose!\n\tYour score is: " + std::to_string(context.playerInput->getScore()));
	m_title.setFillColor(sf::Color::Cyan);
	m_title.setCharacterSize(100);
	centerOrigin(m_title);
	m_title.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

	m_message.setFont(font);
	m_message.setString("Please enter your name");
	m_message.setFillColor(sf::Color::White);
	m_message.setCharacterSize(50);
	m_message.setOrigin(m_message.getLocalBounds().width / 2,
		m_message.getLocalBounds().height / 2);
	m_message.setPosition(sf::Vector2f(windowSize.x / 2.5,
		(windowSize.y / 2) + 100));

	playerText.setFont(font);
	playerText.setCharacterSize(50);
	playerText.setFillColor(sf::Color::Red);
	centerOrigin(playerText);
	playerText.setPosition(sf::Vector2f(windowSize.x / 2.5, (windowSize.y / 2) + 200));

	m_score_player = new std::string(std::to_string(context.playerInput->getScore()));

	m_soundState.play();
}

FinalState::~FinalState()
{
	delete m_score_player;
	delete m_name;
}

void FinalState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(m_title);
	window.draw(m_message);
	window.draw(playerText);

	window.draw(mousePicture);

}

bool FinalState::update(double dt)
{
	if (m_backToMenu)
	{
		requestStateClear();
		requestStackPush(States::Menu);
	}
	this->updateCursor();

	return true;
}

bool FinalState::handleEvent(const sf::Event& event)
{
	if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_backToMenu = true;
	}
	else if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode < 128)
			inputLogic(event.text.unicode);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		//TODO: save name into scores.txt
		saveString();
		foo();
		m_backToMenu = true;
	}
	return true;
}

void FinalState::centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
		std::floor(bounds.top + bounds.height / 2.f));
}

void FinalState::inputLogic(int charTyped)
{
	if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
	{
		playerInput += static_cast<char>(charTyped);
		playerText.setString(playerInput);
	}
	else if (charTyped == DELETE_KEY)
	{
		if (playerInput.getSize() > 0)
			deleteLastChar();
		playerText.setString(playerInput + "_");
	}
}

void FinalState::deleteLastChar()
{
	sf::String tempString = "";

	for (int i = 0; i < playerInput.getSize() - 1; i++)
		tempString += playerInput[i];

	playerInput = tempString;
	playerText.setString(playerInput);
	
}

void FinalState::saveString()
{
	std::ofstream scores_file;

	m_name = new std::string(playerInput.toAnsiString());
	std::cout << *m_name << " " << m_name->length() << std::endl;
	std::cout << *m_score_player << " " << m_score_player->length() << std::endl;

	scores_file.open("Records.txt");
	if (!scores_file.is_open())
	{
		requestStackPop();
		requestStackPush(States::ErrorState);
	}
	else
	{
		scores_file.seekp(0, std::ios::end);

		scores_file << (*m_name) << " " << (*m_score_player) << std::endl;

		scores_file.close();
	}
}

void FinalState::foo()
{
	std::string line;
	std::ifstream myfile("Records.txt", std::ios::in);

	if (!myfile.is_open())
	{
		std::cout << "Can not open file" << std::endl;
	}
	else
	{
		std::cout << "Read file:\n";
		while (!myfile.eof())
		{
			myfile >> line;
			std::cout << line << std::endl;
		}
		myfile.close();
	}
}
