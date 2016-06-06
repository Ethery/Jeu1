#include "enemy.h"

using namespace std;

Enemy::Enemy(std::vector<std::vector<int>> map):Unite()
{
	memorisedMap = map;
	visitedx.clear();
	visitedy.clear();
}

Enemy::Enemy(int v, std::vector<std::vector<int>> map):Unite()
{
	vie = v;
	memorisedMap = map;
	visitedx.clear();
	visitedy.clear();
}

Enemy::Enemy(int v, int ap, std::vector<std::vector<int>> map):Unite()
{
	vie = v;
	actionPoints = ap;
	memorisedMap = map;
	visitedx.clear();
	visitedy.clear();
}

Enemy::Enemy(int v, int ap, int mp, std::vector<std::vector<int>> map):Unite()
{
	vie = v;
	actionPoints = ap;
	movePoints = mp;
	memorisedMap = map;
	visitedx.clear();
	visitedy.clear();
}

int Enemy::addJoueur(sf::Vector2i jpos)
{
	positionsJoueurs.push_back(jpos);
	return positionsJoueurs.size() - 1;
}

void Enemy::updateJoueur(int i, sf::Vector2i jpos)
{
	positionsJoueurs[i] = jpos;
}

int Enemy::getRange()
{
	return attaqueRange;
}

int Enemy::getDelaiAttaque()
{
	return delaiAttaque;
}

std::vector<int> Enemy::getVisitedx()
{
	return visitedx;
}

std::vector<int> Enemy::getVisitedy()
{
	return visitedy;
}

sf::Clock* Enemy::getCD()
{
	return &clockAttaque;
}

void Enemy::setDelaiAttaque(sf::Clock c )
{
	clockAttaque = c;
}

bool Enemy::isJoueur(int x, int y)
{
	for (int i = 0; i < positionsJoueurs.size(); i++)
	{
		if (positionsJoueurs[i].x == x && positionsJoueurs[i].y == y)
		{
			return true;
		}
	}
	return false;
}

bool Enemy::canHit(int idJ)
{
	for (int i = 0; i < visitedx.size(); i++)
	{
		if (visitedx[i] == positionsJoueurs[idJ].x && visitedy[i] == positionsJoueurs[idJ].y)
		{
			return true;
		}
	}
	return false;
}

bool Enemy::isVisited(int x, int y)
{
	for (int i = 0; i < visitedx.size(); i++)
	{
		if (visitedx[i] == x && visitedy[i] == y)
		{
			return true;
		}
	}
	return false;
}

void Enemy::setVisited(int x, int y ,int range)
{
	if (range >= 0 && memorisedMap[x][y] == 2)
	{
		if (!isVisited(x, y))
		{
			visitedx.push_back(x);
			visitedy.push_back(y);
		}
		bool result = false;
		if (x + 1 < memorisedMap.size())
		{
			setVisited(x + 1, y, range - 1);
		}
		if (x - 1 >= 0)
		{
			setVisited(x - 1, y, range - 1);
		}
		if (y - 1 >= 0)
		{
			setVisited(x, y - 1, range - 1);
		}
		if (y + 1 < memorisedMap.size())
		{
			setVisited(x, y + 1, range - 1);
		}
	}
}

void Enemy::cleanVisited()
{
	visitedx.clear();
	visitedy.clear();
}

void Enemy::setDelaiAttaque(int delai)
{
	delaiAttaque = delai;
}

int Enemy::nextMove()
{
	cleanVisited();
	setVisited(position.x, position.y, attaqueRange);
	for (int i = 0; i < positionsJoueurs.size(); i++)
	{
		if (canHit(i))
		{
			return 4;
		}
	}
	
	return -1;
}

std::vector<int> Enemy::calculNextsMoves()
{
	std::vector<int> moves;
	
	if (nextMove() == 4)
	{
		moves.push_back(4);
		return moves;
	}
	moves.push_back(2);
	return moves;
}

void Enemy::showMemory()
{
	for (int i = 0; i < memorisedMap.size(); i++)
	{
		for (int j = 0; j < memorisedMap[i].size(); j++)
		{
			bool isJoueur = false;
			for (int k = 0; k < positionsJoueurs.size(); k++)
			{
				if (positionsJoueurs[k].x == i && positionsJoueurs[k].y == j)
				{
					cout << "J";
					isJoueur = true;
					break;
				}
			}
			if (i == position.x && j == position.y)
			{
				cout << "X";
				continue;
			}
			if (!isJoueur)
			{
				cout << memorisedMap[i][j];
			}
		}
		cout << endl;
	}
}


