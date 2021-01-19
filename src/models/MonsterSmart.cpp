#include "models/MonsterSmart.h"
#include <queue> 
#include <cmath>

class QItem {
public:
	int row;
	int col;
	std::vector<int> VecMov;

	QItem(int x, int y, std::vector<int> w)
		: row(x), col(y), VecMov(w)
	{
	}
};




MonsterSmart::MonsterSmart
(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt, Player * p) :
	Monster(pos, size, txt), m_size(size)
{
//this->m_rec->setScale(m_rec->getScale().x * (float)0.8, m_rec->getScale().y * (float)1.2);
	m_copy_player = p ;
}

void MonsterSmart::setGrid(std::vector<std::vector<char>> grid)
{
	m_grid = grid;
	this->buildVisited();

	static int i = 0;

	if (i == 0)
	{
		for (int i = 0; i < m_grid.size();i++)
		{
			for (int j = 0; j < m_grid[i].size();j++)
				std::cout << m_grid[i][j] << " ";
			std::cout << std::endl;
		}

		for (int i = 0; i < m_visited.size();i++)
		{
			for (int j = 0; j < m_visited[i].size();j++)
				std::cout << m_visited[i][j] << " ";
			std::cout << std::endl;
		}
		i++;
	}
}
/*
void MonsterSmart::handleColision(Ladder& obj)
{
	this->m_rec->setPosition(obj.getSprite().getPosition().x , m_rec->getPosition().y);
}
*/
/*
void MonsterSmart::handleColision(Ropes& obj)
{
	this->m_rec->setPosition(obj.getSprite().getPosition().x, m_rec->getPosition().y);
}
*/
void MonsterSmart::updateDirection()
{
	/* start but not finish
	// is in my row?
	if (isInMyRow())
	{
		if (m_copy_player->getPosition().x > this->getPosition().x)
			m_dircetion = 2;
		else if (m_copy_player->getPosition().x < this->getPosition().x)
			m_dircetion = 1;
	}
	*/
	sf::Vector2f playerPosMap, monsterPosMap;
	
	playerPosMap = this->getPosOnMat(m_copy_player);
	monsterPosMap = this->getPosOnMat(this);
	
	std::cout << monsterPosMap.x << " " << monsterPosMap.y << std::endl;
	
	if ((playerPosMap.x >= 0 && playerPosMap.y >= 0 &&
		playerPosMap.x < m_visited.size() && playerPosMap.y < m_visited[0].size()) &&
		(monsterPosMap.x >= 0 && monsterPosMap.y >= 0 &&
			monsterPosMap.x < m_visited.size() && monsterPosMap.y < m_visited[0].size()))
	{
		this->buildVisited();
		m_dircetion = this->getDirectionSmart(playerPosMap, monsterPosMap);
	}

	/*
	if (m_grid[monsterPosMap.x][monsterPosMap.y] == 'H' && ((m_dircetion == 3) || (m_dircetion == 4)) ) 
	{
		this->m_rec->setPosition(this->getPosition().x - m_size.x / 2u, this->getPosition().y);

		monsterPosMap = this->getPosOnMat(this);
		
		if (m_grid[monsterPosMap.x][monsterPosMap.y] != 'H')
		{
			this->m_rec->setPosition(this->getPosition().x + m_size.x , this->getPosition().y);
			monsterPosMap = this->getPosOnMat(this);
		}
	}
	*/

	if (m_dircetion == -1)
	{
		srand((unsigned int)time(NULL));

		//m_dircetion = rand() % 4;
	}


	this->SaveLastPosition();
}

size_t MonsterSmart::getDirectionSmart(sf::Vector2f playerPosMap, sf::Vector2f monsterPosMap)
{
	std::queue <QItem> queueManager;
	std::vector<int> vec;
	vec.clear();
	QItem source(monsterPosMap.x, monsterPosMap.y, vec);

	if (source.row >= 0 && source.col >= 0 &&
		source.row < m_visited.size() && source.col < m_visited[0].size())
		m_visited[source.row][source.col] = 1;
	else
		return -1;

	queueManager.push(source);
	bool moveTwo = false;

	while (!queueManager.empty()) {
		QItem p = queueManager.front();
		queueManager.pop();

		if (!(p.row >= 0 && p.col >= 0 &&
			p.row < m_visited.size() && p.col < m_visited[0].size()))
			return -1;

		if(m_grid[p.row][p.col] == 2)
			moveTwo = true;
		else
			moveTwo = false;


		// Destination found; 
		if (p.row == playerPosMap.x && p.col == playerPosMap.y)
			return p.VecMov[0];

		// moving up 
		if ( p.row - 1 >= 0 && m_visited[p.row - 1][p.col] == 0 && !moveTwo)
		{
			p.VecMov.push_back(Object_Direction::Up);
			queueManager.push(QItem(p.row - 1, p.col, std::vector<int>(p.VecMov)));
			p.VecMov.pop_back();
			m_visited[p.row - 1][p.col] = 1;
		}

		// moving down 
		if ( p.row + 1 < m_visited.size() &&
			( m_visited[p.row + 1][p.col] == 0 || m_visited[p.row + 1][p.col] == 2) )
		{
			p.VecMov.push_back(Object_Direction::Down);
			queueManager.push(QItem(p.row + 1, p.col, std::vector<int>(p.VecMov)));
			p.VecMov.pop_back();
			m_visited[p.row + 1][p.col] = 1;
		}

		// moving left 
		if ( p.col - 1 >= 0 && 
			(m_visited[p.row][p.col - 1] == 0 || m_visited[p.row][p.col - 1] == 2)  && !moveTwo)
		{
			p.VecMov.push_back(Object_Direction::Left);
			queueManager.push(QItem(p.row, p.col - 1, std::vector<int>(p.VecMov)));
			p.VecMov.pop_back();
			m_visited[p.row][p.col - 1] = 1;
		}

		// moving right 
		if ( p.col + 1 < m_visited[1].size() &&
			(m_visited[p.row][p.col + 1] == 0 || m_visited[p.row][p.col + 1] == 2) && !moveTwo)
		{
			p.VecMov.push_back(Object_Direction::Right);
			queueManager.push(QItem(p.row, p.col + 1, std::vector<int>(p.VecMov)));
			p.VecMov.pop_back();
			m_visited[p.row][p.col + 1] = 1;
		}
	}
	return -1;
}


sf::Vector2f MonsterSmart::getPosOnMat(DynamicObject * dObj)
{
	float position;
	int row,col;
	position = m_size.y;
	sf::Vector2f vec;

	col = std::round((dObj->getPosition().x - m_size.x / 2u) / m_size.x);
	row = std::round((dObj->getPosition().y - m_size.y / 2u) / m_size.y);

	/*
	for (row = 0; position < dObj->getPosition().y; ++row) {
		position += m_size.y;
	}
	
	
	position = m_size.x;
	for (col = 0; position < dObj->getPosition().x ; ++col) {
		position += m_size.x;
	}
	*/

	//if (position - m_size.x / 2u > dObj->getPosition().x && col != 0 && col + 1 < m_visited.size())
	//	col++;

	 //if ( ( position > ( dObj->getPosition().x + m_size.x / 2u ) ) && ( ( col > 1 ) && ( col + 1 < m_visited[0].size() ) ) )
	//	col--;
	return sf::Vector2f(row,col);
}


void MonsterSmart::buildVisited()
{
	// build
	m_visited.resize(m_grid.size());
	
	for (int i = 0; i < m_grid.size();i++)
		m_visited[i].resize(m_grid[i].size());
	
	// full
	for (size_t i = 0; i < m_grid.size(); i++) {
		for (size_t j = 0; j < m_grid[i].size(); j++)
		{
			if ( (m_grid[i][j] == ObjectType::RopesChar || m_grid[i][j] == ObjectType::LadderChar) ||
				(i + 1 < m_grid.size() && ( m_grid[i + 1][j] == ObjectType::FloorChar || m_grid[i + 1][j] == ObjectType::LadderChar )) 
				&& (m_grid[i][j] == ObjectType::CoinChar || m_grid[i][j] == ObjectType::GiftChar || m_grid[i][j] == '\0') )
				m_visited[i][j] = 0;
			else if(m_grid[i][j] != ObjectType::FloorChar && i != m_grid.size() - 1 && i != 0)
				m_visited[i][j] = 2;
			else
				m_visited[i][j] = 1;
		}
	}
}

/*
bool MonsterSmart::isInMyRow()
{
	return (m_copy_player->getPosition().y < this->getPosition().y + m_size.y &&
		m_copy_player->getPosition().y >= this->getPosition().y - m_size.y);
}
*/

