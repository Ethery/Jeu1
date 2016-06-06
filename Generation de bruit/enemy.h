#pragma once
#include <vector>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <algorithm>

#include "unite.h"


class Enemy:public Unite
{
private:
	std::vector<sf::Vector2i> positionsJoueurs;
	std::vector<std::vector<int>> memorisedMap;
	std::vector<int> visitedx;
	std::vector<int> visitedy;
	int delaiAttaque;
	sf::Clock clockAttaque;

public:
	Enemy(std::vector<std::vector<int>> map);
	Enemy(int v, std::vector<std::vector<int>> map);
	Enemy(int v, int ap, std::vector<std::vector<int>> map);
	Enemy(int v, int ap,int mp, std::vector<std::vector<int>> map);

	int addJoueur(sf::Vector2i jpos);
	void updateJoueur(int i, sf::Vector2i jpos);

	int getRange();
	int getDelaiAttaque();
	std::vector<int> getVisitedx();
	std::vector<int> getVisitedy();
	sf::Clock* getCD();
	void setDelaiAttaque(sf::Clock c);

	bool isJoueur(int x, int y);
	//bool canSpell(int x, int y, int range);
	bool canHit(int idJ);
	bool isVisited(int x, int y);
	void setVisited(int x, int y, int range);
	void cleanVisited();
	void setDelaiAttaque(int delai);
	
	/*
	DOC DEPLACEMENT:
	-1 -> RIEN
	0 -> HAUT
	1 -> DROITE
	2 -> BAS
	3 -> GAUCHE
	4 -> ATTAK
	*/

	int nextMove();
	std::vector<int> calculNextsMoves();

	void showMemory();

};