#include "unite.h"

using namespace std;

Unite::Unite()
{
	vie = 100;
	actionPoints = 3;
	movePoints = 5;
	attaqueRange = 5;
	position.x = 0;
	position.y = 0;
	degats = 100;
}

void Unite::setDegats(int d)
{
	degats = d;
}

void Unite::setVie(int v)
{
	vie = v;
}

void Unite::setActionPoints(int ap)
{
	actionPoints = ap;
}

void Unite::setMovePoints(int mp)
{
	movePoints = mp;
}

void Unite::setAttaqueRange(int range)
{
	attaqueRange = range;
}

void Unite::setPos(sf::Vector2i p)
{
	position = p;
}

int Unite::getDegats()
{
	return degats;
}

int Unite::getVie()
{
	return vie;
}

int Unite::getActionPoints()
{
	return actionPoints;
}

int Unite::getMovePoints()
{
	return movePoints;
}

int Unite::getRange()
{

	return attaqueRange;
}

sf::Vector2i Unite::getPosition()
{
	return position;
}

std::string Unite::getSpritePath()
{
	return spritePath;
}

bool Unite::setTexture(std::string src)
{
	if (!texture.loadFromFile(src))
	{
		return false;
	}
	texture.setSmooth(true);
	return true;
}

bool Unite::setSprite(std::string src)
{
	if (!setTexture(src))
	{
		return false;
	}
	sprite.setTexture(texture);
	return true;
}

void Unite::setSprite(sf::Sprite spr)
{
	sprite = spr;
}

void Unite::setSpritePosition(sf::Vector2f p)
{
	sprite.setPosition(p);
}

void Unite::setSpriteScale(sf::Vector2f s)
{
	sprite.setScale(s);
}

void Unite::setSpritePath(std::string path)
{
	spritePath = path;
}

sf::Texture Unite::getTexture()
{
	return texture;
}

sf::Sprite Unite::getSprite()
{
	return sprite;
}


