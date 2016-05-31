#pragma once
#include <vector>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <algorithm>

class Unite
{
protected:
	int vie;
	int actionPoints;
	int movePoints;
	int attaqueRange;
	sf::Vector2i position;
	sf::Texture texture;
	sf::Sprite sprite;
	std::string spritePath;

public:
	Unite();

	void setVie(int v);
	void setActionPoints(int ap);
	void setMovePoints(int mp);
	void setRange(int range);
	void setPos(sf::Vector2i p);

	void setSpritePosition(sf::Vector2f p);
	void setSpriteScale(sf::Vector2f s);
	void setSpritePath(std::string path);
	bool setTexture(std::string src);
	bool setSprite(std::string src);
	void setSprite(sf::Sprite spr);

	int getVie();
	int getActionPoints();
	int getMovePoints();
	int getRange();
	sf::Vector2i getPosition();
	std::string getSpritePath();

	sf::Texture getTexture();
	sf::Sprite getSprite();

};