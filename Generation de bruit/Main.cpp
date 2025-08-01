#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <iostream>

#include "bruit.h"
#include "enemy.h"
#include "joueur.h" 
#include "map.cpp"
#include "timer.cpp"

using namespace std;

// Taille de l'image
#define TAILLE 55
// On d�finit le nombre d'octaves.
#define OCTAVES 8
// On d�finit le pas.
#define PAS 100
// On d�finit la persistance.
#define PERSISTANCE 0.6

// Taille d'une case de jeu
#define CASE 16.0

#define TAILLEECRAN TAILLE*CASE

#define FACTEURPRECISION 2

void vectorErase(vector<Enemy> &v,int index)
{
	for (int i = index; i < v.size() - 1; i++)
	{
		v[i] = v[i + 1];
		v[i].setSprite(v[i + 1].getSpritePath());
	}
	v.pop_back();
}

void initJeu(Joueur &j, vector<Enemy> &enemys, vector<vector<int>> map)
{
	j.setDelaiDeplacement(300);
	j.setDelaiAttaque(300);
	j.setVie(150);
	j.setSpritePath("src/D3.png");
	j.setSprite("src/D3.png");
	j.setAttaqueRange(7);
	int x = rand() % map.size();
	int y = rand() % map.size();
	while (map[x][y] == 2)
	{
		x = rand() % map.size();
		y = rand() % map.size();
	}
	j.setPos(sf::Vector2i(x,y));
	j.setSpriteScale(sf::Vector2f(CASE / j.getTexture().getSize().x, CASE / j.getTexture().getSize().y));
	j.cleanRange();
	j.setRange(j.getPosition().x, j.getPosition().y, j.getRange(), map);

	enemys.clear();

	srand(time(nullptr));
	for (int i = 0; i < 1; i++)
	{
		enemys.push_back(Enemy(map));
	}
	for (int i = 0; i < enemys.size(); i++)
	{
		int x = rand() % map.size();
		int y = rand() % map.size();
		if (map[x][y] != 2)
		{
			i--;
			continue;
		}
		enemys[i].setPos(sf::Vector2i(x,y));
		enemys[i].setSpritePath("src/enemy.png");
		enemys[i].setSprite("src/enemy.png");
		enemys[i].setSpriteScale(sf::Vector2f(CASE / enemys[i].getTexture().getSize().x, CASE / enemys[i].getTexture().getSize().y));
		enemys[i].setDelaiAttaque(700);
		enemys[i].setDelaiAttaque(sf::Clock());
		j.setID(enemys[i].addJoueur(j.getPosition()));
		enemys[i].cleanVisited();
		enemys[i].setVisited(enemys[i].getPosition().x, enemys[i].getPosition().y, enemys[i].getRange());
	}
}

int main()
{
	Bruit b = Bruit(TAILLE*FACTEURPRECISION, TAILLE*FACTEURPRECISION, PAS, OCTAVES);
	vector<vector<int>> map;
	for (int i = 0; i < TAILLE; i++)
	{
		vector<int> d1;
		for (int j = 0; j < TAILLE; j++)
		{
			d1.push_back(b.obtenirCaseS1(i*FACTEURPRECISION, j*FACTEURPRECISION, PERSISTANCE, 0.45,0.70, FACTEURPRECISION));
		}
		map.push_back(d1);
	}

	b.~Bruit();

	TileMap tileMap;
	if (!tileMap.load("src/map.png", sf::Vector2u(32, 32), sf::Vector2u(CASE, CASE), map, map.size(), map.size()))
		return -1;

	sf::RectangleShape mouseCursor;
	mouseCursor.setFillColor(sf::Color::Transparent);
	mouseCursor.setSize(sf::Vector2f(CASE, CASE));
	mouseCursor.setOutlineColor(sf::Color::Black);
	mouseCursor.setOutlineThickness(1);

	sf::CircleShape range(CASE/2);
	range.setFillColor(sf::Color(255, 0, 0, 60));

	//---------------------------------//

	Joueur j;

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");

	sf::Text jVie;
	jVie.setFont(font);
	jVie.setCharacterSize(CASE/2);

	sf::Text restart;

	srand(time(nullptr));

	int r, v, bl;
	r = rand() % 40;
	v = rand() % 40;
	bl = rand() % 205 + 50;
	Timer recuperationMoveJoueur(sf::Color(r, v, bl, 120));

	r = rand() % 40;
	v = rand() % 205 + 50;
	bl = rand() % 40;
	Timer recuperationAttaqueJoueur(sf::Color(r, v, bl, 120));
	
	sf::Texture tDegats;
	tDegats.loadFromFile("src/degats.png");
	sf::Sprite degats(tDegats);
	
	//---------------------------------//
	
	vector<Enemy> enemys;

	initJeu(j, enemys, map);

	sf::Vector2i pMouse;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;

	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

	modes.push_back(sf::VideoMode::getDesktopMode());
	sf::VideoMode mode = modes[modes.size() - 1];
	cout << "Desktop mode: " << mode.width << "x" << mode.height << " - " << mode.bitsPerPixel << " bpp" << endl;

	for (std::size_t i = 0; i < modes.size(); ++i)
	{
		mode = modes[i];
		cout << "Mode #" << i << ": " << mode.width << "x" << mode.height << " - " << mode.bitsPerPixel << " bpp" << endl;
	}


	sf::RenderWindow window;
	window.create(modes[8], "Jeu 1", sf::Style::Default, settings);
	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			for (int i = 0; i < enemys.size(); i++)
			{
				enemys[i].getCD()->restart();
			}
			j.getClockDeplacement()->restart();
			j.getClockAttaque()->restart();
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		restart.setFont(font);
		if (j.getVie() <= 0)
		{
			j.setVie(0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				initJeu(j, enemys, map);
				continue;
			}
			restart.setString("LOSE ! Press Space for restart or Esc for leave");
			restart.setCharacterSize(20);
			restart.setPosition(0,0);
		}
		else if (enemys.size() == 0)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				initJeu(j, enemys, map);
				continue;
			}
			restart.setString("WIN ! Press Space for restart or Esc for leave");
			restart.setCharacterSize(20);
			restart.setPosition(0,0);
		}
		else
		{

			restart.setString("");
			//CALCULS JEU / TOUR
			pMouse.x = sf::Mouse::getPosition(window).x / CASE;
			pMouse.y = sf::Mouse::getPosition(window).y / CASE;
			mouseCursor.setPosition(sf::Vector2f(pMouse.x*CASE, pMouse.y*CASE));
			if (j.getClockDeplacement()->getElapsedTime().asMilliseconds() > j.getDelaiDeplacement())
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
					&& j.getPosition().x < ((TAILLE*CASE) / CASE) - 1)
				{
					j.setPos(sf::Vector2i(j.getPosition().x + 1, j.getPosition().y));
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
					&& j.getPosition().x > 0)
				{
					j.setPos(sf::Vector2i(j.getPosition().x - 1, j.getPosition().y));
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
					&& j.getPosition().y < ((TAILLE*CASE) / CASE) - 1)
				{
					j.setPos(sf::Vector2i(j.getPosition().x, j.getPosition().y + 1));
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
					&& j.getPosition().y > 0)
				{
					j.setPos(sf::Vector2i(j.getPosition().x, j.getPosition().y - 1));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					j.getClockDeplacement()->restart();
					for (int i = 0; i < enemys.size(); i++)
					{
						enemys[i].updateJoueur(j.getID(), j.getPosition());
					}
					j.cleanRange();
					j.setRange(j.getPosition().x, j.getPosition().y, j.getRange(), map);
				}
			}

			if (j.getClockAttaque()->getElapsedTime().asMilliseconds() > j.getDelaiAttaque())
			{
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (j.isRanged(pMouse.x,pMouse.y))
					{
						for (int i = 0; i < enemys.size(); i++)
						{
							if (enemys[i].getPosition() == pMouse)
							{
								vectorErase(enemys, i);
								continue;
							}
						}
						j.getClockAttaque()->restart();
					}
				}
			}

			for (int i = 0; i < enemys.size(); i++)
			{
				if (enemys[i].getCD()->getElapsedTime().asMilliseconds() > enemys[i].getDelaiAttaque())
				{
					if (enemys[i].canHit(j.getID()))
					{
						j.setVie(j.getVie() - enemys[i].getDegats());
						enemys[i].getCD()->restart();
					}
				}
			}
		}

		//AFFICHAGE

		window.clear();
		window.draw(tileMap);

		range.setFillColor(sf::Color(255, 0, 0, 60));
		for (int i = 0; i < enemys.size(); i++)
		{
			enemys[i].setSpritePosition(sf::Vector2f(enemys[i].getPosition().x*CASE, enemys[i].getPosition().y*CASE));
			degats.setPosition(sf::Vector2f(enemys[i].getPosition().x*CASE, enemys[i].getPosition().y*CASE));
			degats.setScale(0, 0);
			window.draw(enemys[i].getSprite());

			if (enemys[i].getCD()->getElapsedTime().asMilliseconds() < enemys[i].getDelaiAttaque())
			{
				int tcd = enemys[i].getDelaiAttaque() - enemys[i].getCD()->getElapsedTime().asMilliseconds();
				float size = ((CASE*tcd) / enemys[i].getDelaiAttaque());
				degats.setTexture(tDegats);
				degats.setPosition(sf::Vector2f(enemys[i].getPosition().x*CASE + (CASE / 2) - (size / 2), enemys[i].getPosition().y*CASE + (CASE / 2) - (size / 2)));
				degats.setScale(sf::Vector2f(size / tDegats.getSize().x, size / tDegats.getSize().y));
			}
			window.draw(degats);

			for (int j = 0; j < enemys[i].getVisitedx().size(); j++)
			{
				range.setPosition(CASE*enemys[i].getVisitedx()[j], CASE*enemys[i].getVisitedy()[j]);
				window.draw(range);
			}
		}

		range.setFillColor(sf::Color(0, 0, 255, 60));
		for (int i = 0; i < j.getVisitedSize(); i++)
		{
			range.setPosition(CASE*j.getVisitedx()[i], CASE*j.getVisitedy()[i]);
			window.draw(range);
		}

		j.setSpritePosition(sf::Vector2f(j.getPosition().x*CASE, j.getPosition().y*CASE));
		window.draw(j.getSprite());

		if (j.getClockDeplacement()->getElapsedTime().asMilliseconds() < j.getDelaiDeplacement())
		{
			recuperationMoveJoueur.reload(sf::Vector2i(j.getPosition().x*CASE + (CASE / 2), j.getPosition().y*CASE + (CASE / 2)), CASE / 2, j.getDelaiDeplacement(), j.getClockDeplacement()->getElapsedTime().asMilliseconds());
			window.draw(recuperationMoveJoueur);
		}

		if (j.getClockAttaque()->getElapsedTime().asMilliseconds() < j.getDelaiAttaque())
		{
			recuperationAttaqueJoueur.reload(sf::Vector2i(pMouse.x*CASE + (CASE / 2), pMouse.y*CASE + (CASE / 2)), CASE / 2, j.getDelaiAttaque(), j.getClockAttaque()->getElapsedTime().asMilliseconds());
			window.draw(recuperationAttaqueJoueur);
		}



		jVie.setString(std::to_string(j.getVie()));
		jVie.setPosition(j.getPosition().x*CASE+(CASE/2) - jVie.getLocalBounds().width /2, j.getPosition().y*CASE - CASE / 2);

		window.draw(jVie);
		window.draw(mouseCursor);
		window.draw(restart);

		window.display();
	}

	return 0;
}