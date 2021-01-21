#include "models/MonsterSmart.h"
#include <queue> 
#include <cmath>
#include <stdlib.h> 
#include "models/Floor.h"

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
(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt,  Player* const p) :
	Monster(pos, size, txt), m_size(size),m_last_cell(0, 0)
{
	m_copy_player = p;
}

void MonsterSmart::setGrid(std::vector<std::vector<char>> &grid)
{
	m_map = grid;
	this->buildVisited();
}

void MonsterSmart::handleColision(Ladder& obj)
{
	if (m_dircetion == Object_Direction::Up || m_dircetion == Object_Direction::Down)
	{
		this->m_rec->setPosition(obj.getSprite().getPosition().x, m_rec->getPosition().y);
	}
	else if (m_dircetion == Object_Direction::Right || m_dircetion == Object_Direction::Left)
	{
		if (m_last_dir == Object_Direction::Up)
			this->m_rec->setPosition(m_rec->getPosition().x,
				m_rec->getPosition().y - m_rec->getGlobalBounds().height / 2.5);
		else if (m_last_dir == Object_Direction::Down)
			this->m_rec->setPosition(m_rec->getPosition().x,
				m_rec->getPosition().y + m_rec->getGlobalBounds().height / 2.5);
	}
}

bool MonsterSmart::isInRange(int row, int col)
{
	return (row >= 0 && col >= 0 && row < m_visited.size() && col < m_visited[0].size());
}

void MonsterSmart::updateDirection(const float& dt)
{
	sf::Vector2i  monsterPosMap, playerPosMap;
	playerPosMap = this->getPosOnMat(m_copy_player);
	monsterPosMap = this->getPosOnMat(this);

	m_last_dir = m_dircetion;

	this->fixPixel(monsterPosMap);

	m_last_cell = sf::Vector2i(monsterPosMap.x, monsterPosMap.y);


	if ((playerPosMap.x >= 0 && playerPosMap.y >= 0 &&
		playerPosMap.x < m_visited.size() && playerPosMap.y < m_visited[0].size()) &&
		(monsterPosMap.x >= 0 && monsterPosMap.y >= 0 &&
			monsterPosMap.x < m_visited.size() && monsterPosMap.y < m_visited[0].size()))
	{
		this->buildVisited();
		m_dircetion = this->getDirectionSmartBfs(playerPosMap, monsterPosMap);
	}

	if (m_dircetion == -1)
	{
		if (this->getLastPos() == this->m_rec->getPosition())
		{
			(m_last_dir == Object_Direction::Left) ?
				m_last_dir = Object_Direction::Right : m_last_dir = Object_Direction::Left;
		}
		m_dircetion = m_last_dir;
	}

	this->SaveLastPosition();
}

size_t MonsterSmart::getDirectionSmartBfs(sf::Vector2i playerPosMap, sf::Vector2i monsterPosMap)
{
	if (m_map.size() == 0 || m_visited.size() == 0)
		return 0;


	std::queue <QItem> queueManager;
	std::vector<int> vec;
	vec.clear();
	QItem source(monsterPosMap.x, monsterPosMap.y, vec);

	//	if (source.row >= 0 && source.col >= 0 &&
	//		source.row < m_visited.size() && source.col < m_visited[0].size())
	//		m_visited[source.row][source.col] = 1;
	//	else
	//		return -1;

	queueManager.push(source);
	bool moveTwo = false;

	while (!queueManager.empty()) {
		QItem p = queueManager.front();
		queueManager.pop();

			if (!(p.row >= 0 && p.col >= 0 &&
			p.row < m_visited.size() && p.col < m_visited[0].size()))
			return -1;

		if (m_map[p.row][p.col] == 2)
			moveTwo = true;
		else
			moveTwo = false;

		// Player found; 
		if (p.row == playerPosMap.x && p.col == playerPosMap.y)
		{
			if (!p.VecMov.empty())
				return p.VecMov[0];
			else
				return -1;
		}

		// moving up 
		if (p.row - 1 >= 0 && m_visited[p.row - 1][p.col] == 0 && !moveTwo)
		{
			p.VecMov.push_back(Object_Direction::Up);
			queueManager.push(QItem(p.row - 1, p.col, std::vector<int>(p.VecMov)));
			p.VecMov.pop_back();
			m_visited[p.row - 1][p.col] = 1;
		}

		// moving down 
		if (p.row + 1 < m_visited.size() &&
			(m_visited[p.row + 1][p.col] == 0 || m_visited[p.row + 1][p.col] == 2))
		{
			p.VecMov.push_back(Object_Direction::Down);
			queueManager.push(QItem(p.row + 1, p.col, std::vector<int>(p.VecMov)));
			p.VecMov.pop_back();
			m_visited[p.row + 1][p.col] = 1;
		}

		// moving left 
		if (p.col - 1 >= 0 &&
			(m_visited[p.row][p.col - 1] == 0 || m_visited[p.row][p.col - 1] == 2) && !moveTwo)
		{
			p.VecMov.push_back(Object_Direction::Left);
			queueManager.push(QItem(p.row, p.col - 1, std::vector<int>(p.VecMov)));
			p.VecMov.pop_back();
			m_visited[p.row][p.col - 1] = 1;
		}

		// moving right 
		if (p.col + 1 < m_visited[1].size() &&
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


sf::Vector2i MonsterSmart::getPosOnMat(DynamicObject* dObj)
{
	int row, col;

	col = std::round((dObj->getPosition().x - m_size.x / 2u) / m_size.x);
	row = std::round((dObj->getPosition().y - m_size.y / 2u) / m_size.y);

	return sf::Vector2i(row, col);
}


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
			if ((m_map[i][j] == ObjectType::RopesChar || m_map[i][j] == ObjectType::LadderChar) ||
				(i + 1 < m_map.size() && (m_map[i + 1][j] == ObjectType::FloorChar || m_map[i + 1][j] == ObjectType::LadderChar))
				&& (m_map[i][j] == ObjectType::CoinChar || m_map[i][j] == ObjectType::GiftChar || m_map[i][j] == '\0'))
				m_visited[i][j] = 0;
			else if (m_map[i][j] == ObjectType::FloorChar)
				m_visited[i][j] = 1;
			else
				m_visited[i][j] = 2;
		}
	}
}

void MonsterSmart::fixPixel(sf::Vector2i  monsterPosMap)
{
	static int parameter = 0;
	if (m_last_cell == sf::Vector2i(monsterPosMap.x, monsterPosMap.y) && this->getPosition() == this->m_last_postion)
	{
		if (m_dircetion == Object_Direction::Down)
		{
			if (isInRange(monsterPosMap.x + 1, monsterPosMap.y - 1) &&
				m_map[monsterPosMap.x + 1][monsterPosMap.y - 1] == '#')
			{
				this->m_rec->setPosition(this->getPosition().x + m_rec->getGlobalBounds().width / 2, this->getPosition().y);
				parameter = 3;
			}
			if (isInRange(monsterPosMap.x + 1, monsterPosMap.y + 1) &&
				m_map[monsterPosMap.x + 1][monsterPosMap.y + 1] == '#')
			{
				this->m_rec->setPosition(this->getPosition().x - m_rec->getGlobalBounds().width / 2, this->getPosition().y);
				if (parameter = 3)
					this->m_rec->setPosition(this->getPosition().x + m_rec->getGlobalBounds().width / 2, this->getPosition().y);
				parameter = 4;
			}
		}
	}
}