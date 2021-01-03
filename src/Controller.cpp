#include "Controller.h"

//Private function
std::string Controller::getPath()
{
	std::string path = "Board" + std::to_string(m_numLevel) + ".txt";
	return path;
}

//Initializer function
void Controller::initWindow()
{
	this->m_window = new sf::RenderWindow
	(sf::VideoMode(1920, 1080), "c++ SFML Lord runner");//,sf::Style::Fullscreen);
	this->m_window->setFramerateLimit(120);
	this->m_window->setVerticalSyncEnabled(true);
}

void Controller::initbackground()
{
	m_back.loadFromFile("background.png");
	m_sprite.setTexture(m_back);

}

//Concstructor/Distractor
Controller::Controller() 
{
	this->initWindow();
	this->initbackground();
	
	std::ifstream fd_readLevel(this->getPath());
	if (fd_readLevel.is_open())
		read_data(fd_readLevel);
}

Controller::~Controller()
{
	delete this->m_window;
}

//Function
void Controller::updateSFMLEvnt()
{
	while (this->m_window->pollEvent(this->m_SFevnet))
	{
		if (this->m_SFevnet.type == sf::Event::Closed)
			this->m_window->close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->m_window->close();
	}
}

void Controller::updateDt()
{
	/*  */
	this->m_dt = this->m_dtClock.restart().asSeconds();
}

void Controller::update()
{
	this->updateSFMLEvnt();

	this->m_board.update(m_dt);
}

void Controller::render()
{
	this->m_window->clear();

	this->m_window->draw(m_sprite);

	this->m_board.renderStaticObj(m_window);

	this->m_board.renderMonster(m_window);

	this->m_board.renderPlayer(m_window);

	this->m_window->display();
}

void Controller::run()
{
	while (this->m_window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}

void Controller::read_data(std::ifstream& fd_readLevel)
{
	//std::string heightStr, weidthStr;
	size_t height, weidth;
	char c;
	
	fd_readLevel >> height;
	fd_readLevel >> weidth;
	this->m_board.initAvg(height, weidth);

	fd_readLevel.get(c);	//eat '\n'
	for (size_t i = 0; i < height ;i++)
	{
		for (size_t j = 0; j < weidth;j++)
		{
			fd_readLevel.get(c);
			m_board.initData(sf::Vector2f((float)j, (float)i), c);
		}
		fd_readLevel.get(c);	//eat '\n'
	}

	fd_readLevel.close();
}

