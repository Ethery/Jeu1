#include "joueur.h"

using namespace std;

Joueur::Joueur():Unite()
{
	vie = 150;
}

void Joueur::setDelaiDeplacement(int delai)
{
	delaiDeplacement = delai;
}

void Joueur::setDelaiAttaque(int delai)
{
	delaiAttaque = delai;
}

void Joueur::setID(int id)
{
	ID = id;
}

void Joueur::setClockDeplacement(sf::Clock delai)
{
	clockDeplacement = delai;
}

void Joueur::setClockAttaque(sf::Clock delai)
{
	clockAttaque = delai;
}


int Joueur::getDelaiDeplacement()
{
	return delaiDeplacement;
}

int Joueur::getDelaiAttaque()
{
	return delaiAttaque;
}

int Joueur::getID()
{
	return ID;
}

sf::Clock* Joueur::getClockDeplacement()
{
	return &clockDeplacement;
}

sf::Clock * Joueur::getClockAttaque()
{
	return &clockAttaque;
}

bool Joueur::isRanged(int x, int y)
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

void Joueur::setRange(int x, int y, int range,int tmap)
{
	if (range >= 0)
	{
		if (!isRanged(x, y))
		{
			visitedx.push_back(x);
			visitedy.push_back(y);
		}
		bool result = false;
		if (x + 1 < tmap)
		{
			setRange(x + 1, y, range - 1, tmap);
		}
		if (x - 1 >= 0)
		{
			setRange(x - 1, y, range - 1, tmap);
		}
		if (y - 1 >= 0)
		{
			setRange(x, y - 1, range - 1, tmap);
		}
		if (y + 1 < tmap)
		{
			setRange(x, y + 1, range - 1, tmap);
		}
	}
}

void Joueur::cleanRange()
{
	visitedx.clear();
	visitedy.clear();
}