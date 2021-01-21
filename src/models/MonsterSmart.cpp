#include "models/MonsterSmart.h"
#include <queue> 
#include <cmath>
#include <stdlib.h> 
#include "models/Floor.h"

//constructor
//========================================================================
MonsterSmart::MonsterSmart
(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt,  Player* const p) :
	Monster(pos, size, txt), m_size(size),m_last_cell(0, 0), m_last_dir(0)
{
	m_copy_player = p;
}

/*
	get from bord mat-type char of static object 
*/
//========================================================================
void MonsterSmart::setGrid(std::vector<std::vector<char>> &grid)
{
	m_map = grid;
	this->buildVisited();
}

//========================================================================
bool MonsterSmart::isInRange(int row, int col)
{
	return (row >= 0 && col >= 0 && row < m_visited.size() && col < m_visited[0].size());
}

/*
1. Builds two points with matching indexes in the matrix according to
   the position of the player and the monster.

2. Rebuilds the matrix of the numbers each time according to
   the position of all the static objects.

3. After it is built it happens to the algorithm
  (in which the matrix of the numbers is destroyed and 
    therefore it is necessary to rebuild it every time)
*/
//========================================================================
void MonsterSmart::updateDirection(const float& dt)
{
	sf::Vector2i  monsterPosMap, playerPosMap;

	playerPosMap = this->getPosOnMat(m_copy_player);
	monsterPosMap = this->getPosOnMat(this);
	// save last direction
	m_last_dir = m_dircetion;
	// try to fix monster location
	this->fixPixel(monsterPosMap);

	m_last_cell = sf::Vector2i(monsterPosMap.x, monsterPosMap.y);

	if (isInRange(monsterPosMap.x, monsterPosMap.y) &&
		isInRange(playerPosMap.x, playerPosMap.y))
	{
		this->buildVisited();
		m_dircetion = this->getDirectionSmartBfs(playerPosMap, monsterPosMap);
	}

	if (m_dircetion == -1)
	{
		if (this->getLastPos() == this->getPosition())
		{
			(m_last_dir == Object_Direction::Left) ?
				m_last_dir = Object_Direction::Right : m_last_dir = Object_Direction::Left;
		}
		m_dircetion = m_last_dir;
	}

	this->SaveLastPosition();
}

/*
	We will describe the algorithm briefly:
	
	The algorithm is run in turn.

	In the loop: We will take the first out of the queue.
	Handling: He will try to go in any of the possible directions
	and every cell we reach will put him 
	in the last queue position.
	Whichever direction we go we will keep it 
	within the vector direction of the current trajectory.

	The algorithm will stop if we reach the player's 
	position and then return the first member Buctor built
	for or when the queue is empty and then it is certainly
	not possible to reach the player
*/
//========================================================================
size_t MonsterSmart::getDirectionSmartBfs(sf::Vector2i playerPosMap, sf::Vector2i monsterPosMap)
{
	if (m_map.size() == 0 || m_visited.size() == 0)
		return -1;

	size_t i = 1;

	std::queue <NudeBfs> queueManager;
	std::vector<int> vec;
	vec.clear();
	// make nude source from monster index 
	NudeBfs source(monsterPosMap.x, monsterPosMap.y, vec);

	queueManager.push(source);
	bool moveTwo = false;

	while (!queueManager.empty()) {
		NudeBfs p = queueManager.front();
		queueManager.pop();

		if (!(p.row >= 0 && p.col >= 0 &&
			p.row < m_visited.size() && p.col < m_visited[0].size()))
			return -1;

		// to make the algoritm check only down direction 
		// if he in cell that hold 2
		if (m_map[p.row][p.col] == 2)
			moveTwo = true;
		else
			moveTwo = false;

		// Player found; 
		if (p.row == playerPosMap.x && p.col == playerPosMap.y)
		{
			// return the first direction
			if (!p.VecMov.empty())
				return p.VecMov[0];
			else
				return -1;
		}

		// moving up 
		if (p.row - 1 >= 0 && m_visited[p.row - i][p.col] == 0 && !moveTwo)
		{
			// push direction to vector
			p.VecMov.push_back(Object_Direction::Up);
			// push new nudeBfs to queue
			queueManager.push(NudeBfs(p.row - 1, p.col, std::vector<int>(p.VecMov)));
			// pop from vector the last direction
			p.VecMov.pop_back(); 
			// mark the cell
			m_visited[p.row - i][p.col] = 1;
		}

		// moving down 
		if (p.row + i < m_visited.size() &&
			(m_visited[p.row + i][p.col] == 0 || m_visited[p.row + i][p.col] == 2))
		{
			p.VecMov.push_back(Object_Direction::Down);
			queueManager.push(NudeBfs(p.row + 1, p.col, std::vector<int>(p.VecMov)));
			p.VecMov.pop_back();
			m_visited[p.row + i][p.col] = 1;
		}

		// moving left 
		if (p.col - 1 >= 0 &&
			(m_visited[p.row][p.col - i] == 0 || m_visited[p.row][p.col - i] == 2) && !moveTwo)
		{
			p.VecMov.push_back(Object_Direction::Left);
			queueManager.push(NudeBfs(p.row, p.col - 1, std::vector<int>(p.VecMov)));
			p.VecMov.pop_back();
			m_visited[p.row][p.col - i] = 1;
		}

		// moving right 
		if (p.col + i < m_visited[1].size() &&
			(m_visited[p.row][p.col + i] == 0 || m_visited[p.row][p.col + i] == 2) && !moveTwo)
		{
			p.VecMov.push_back(Object_Direction::Right);
			queueManager.push(NudeBfs(p.row, p.col + 1, std::vector<int>(p.VecMov)));
			p.VecMov.pop_back();
			m_visited[p.row][p.col + i] = 1;
		}
	}
	return -1;
}

// return position of objects on mat
//========================================================================
sf::Vector2i MonsterSmart::getPosOnMat(DynamicObject* dObj)
{
	int row, col;

	col = (int)std::round((dObj->getPosition().x - m_size.x / 2u) / m_size.x);
	row = (int)std::round((dObj->getPosition().y - m_size.y / 2u) / m_size.y);

	return sf::Vector2i(row, col);
}

/* build mat 
	Cells that can be reached will be colored with the digit 0.
	All floors will be painted in the number 1. (Can not be reached)
	All other cells will be colored in the number 2.
*/
//========================================================================
void MonsterSmart::buildVisited()
{
	// build
	m_visited.resize(m_map.size());

	for (int i = 0; i < m_map.size();i++)
		m_visited[i].resize(m_map[i].size());

	// full
	for (size_t i = 0; i < m_map.size(); i++) {
		for (size_t j = 0; j < m_map[i].size(); j++)
		{
			if ((m_map[i][j] == ObjectType::RopesChar || 
				m_map[i][j] == ObjectType::LadderChar) ||
				(i + 1 < m_map.size() && (m_map[i + 1][j] == ObjectType::FloorChar ||
					m_map[i + 1][j] == ObjectType::LadderChar)) && 
					(m_map[i][j] == ObjectType::CoinChar ||
						m_map[i][j] == ObjectType::GiftChar ||
						m_map[i][j] == '\0'))
				m_visited[i][j] = 0;
			else if (m_map[i][j] == ObjectType::FloorChar)
				m_visited[i][j] = 1;
			else
				m_visited[i][j] = 2;
		}
	}
}

/*
	The function tries to fix the problems in moving
	from a two-dimensional matrix to a sfml window that works on pixels
*/
//========================================================================
void MonsterSmart::fixPixel(sf::Vector2i  monsterPosMap)
{
	if (m_map.size() == 0 || m_visited.size() == 0)
		return;
	
	int parameter = 0;
	size_t i = 1;

	if (m_last_cell == sf::Vector2i(monsterPosMap.x, monsterPosMap.y)
		&& this->getPosition()== this->m_last_postion)
	{
		// floor in Up right or left
		if (m_last_dir == Object_Direction::Up)
		{
			if (isInRange(monsterPosMap.x + 1, monsterPosMap.y - 1) &&
				m_map[monsterPosMap.x + i][monsterPosMap.y - i] == '#')
				{
					this->m_rec->setPosition(this->getPosition().x -
						(float)0.5, this->getPosition().y);
					parameter = 1;
				}
			if (isInRange(monsterPosMap.x - 1, monsterPosMap.y - 1) &&
				m_map[monsterPosMap.x - i][monsterPosMap.y - i] == '#')
				{
					this->m_rec->setPosition(this->getPosition().x +
						(float)0.5, this->getPosition().y);
					if (parameter == 1)
						this->m_rec->setPosition(this->getPosition().x +
						(float)0.5, this->getPosition().y);
						parameter = 2;
				}
		}
		// floor in Down right or left
		if (m_last_dir == Object_Direction::Down)
		{
			if (isInRange(monsterPosMap.x + 1, monsterPosMap.y - 1) &&
				m_map[monsterPosMap.x + i][monsterPosMap.y - i] == '#')
			{
				this->m_rec->setPosition(this->getPosition().x +
					(float)0.5, this->getPosition().y);
				parameter = 3;
			}
			if (isInRange(monsterPosMap.x + 1, monsterPosMap.y + 1) &&
				m_map[monsterPosMap.x + i][monsterPosMap.y + i] == '#')
			{
				this->m_rec->setPosition
				(this->getPosition().x - (float)0.5, this->getPosition().y);
				if (parameter == 3)
					this->m_rec->setPosition
					(this->getPosition().x - (float)0.5, this->getPosition().y);
				parameter = 4;
			}
		}
		// floor in Right up or down
		if (m_last_dir == Object_Direction::Right)
		{
			if (isInRange(monsterPosMap.x + 1, monsterPosMap.y + 1) &&
				m_map[monsterPosMap.x + i][monsterPosMap.y + i] == '#')
			{
				this->m_rec->setPosition
				(this->getPosition().x, this->getPosition().y + (float)0.5);
				parameter = 5;
			}
			if (isInRange(monsterPosMap.x - 1, monsterPosMap.y + 1) &&
				m_map[monsterPosMap.x - i][monsterPosMap.y + i] == '#')
			{
					this->m_rec->setPosition(this->getPosition().x,
						this->getPosition().y - (float)0.5);
					if (parameter == 5)
						this->m_rec->setPosition
						(this->getPosition().x, this->getPosition().y - (float)0.5);
					parameter = 6;
			}
		}
		// floor in left up or down
		if (m_last_dir == Object_Direction::Left)
		{
			if (isInRange(monsterPosMap.x + 1, monsterPosMap.y - 1) &&
				m_map[monsterPosMap.x + i][monsterPosMap.y - i] == '#')
			{
				this->m_rec->setPosition(this->getPosition().x,
					this->getPosition().y - (float)0.5);
				parameter = 7;
			}
			if (isInRange(monsterPosMap.x - 1, monsterPosMap.y - 1) &&
				m_map[monsterPosMap.x - i][monsterPosMap.y - i] == '#')
			{
				this->m_rec->setPosition(this->getPosition().x,
					this->getPosition().y + (float)0.5);
				if (parameter == 7)
				this->m_rec->setPosition(this->getPosition().x, this->getPosition().y + (float)0.5);
				parameter = 8;
			}
		}
	}
}