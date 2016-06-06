#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "unite.h"

class Joueur : public Unite
{
private:
	int delaiDeplacement;
	int delaiAttaque;
	int ID;
	sf::Clock clockDeplacement;
	sf::Clock clockAttaque;
	std::vector<int> visitedx;
	std::vector<int> visitedy;

public:
	Joueur();

	void setDelaiDeplacement(int delai);
	void setDelaiAttaque(int delai);
	void setID(int id);
	void setClockDeplacement(sf::Clock delai);
	void setClockAttaque(sf::Clock delai);

	int getDelaiDeplacement();
	int getDelaiAttaque();
	int getID();
	sf::Clock* getClockDeplacement();
	sf::Clock* getClockAttaque();

	bool isRanged(int x, int y);
	int getVisitedSize();
	std::vector<int> getVisitedx();
	std::vector<int> getVisitedy();
	void setRange(int x, int y, int range, std::vector<std::vector<int>> tmap);
	void cleanRange();
};