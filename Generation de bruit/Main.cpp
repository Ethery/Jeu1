#include <SFML/Graphics.hpp>
#include <iostream>

#include "bruit.h"
#include "enemy.h"
#include "joueur.h"
#include "map.cpp"

using namespace std;

// Taille de l'image
#define TAILLE 800
// On définit le nombre d'octaves.
#define OCTAVES 8
// On définit le pas.
#define PAS 100
// On définit la persistance.
#define PERSISTANCE 0.5

// Taille d'une case de jeu
#define CASE 32.0

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
	j.setDelaiDeplacement(200);
	j.setDelaiAttaque(200);
	j.setVie(150);
	j.setSpritePath("src/D3.png");
	j.setSprite("src/D3.png");
	j.setPos(sf::Vector2i(2, 2));
	j.setSpriteScale(sf::Vector2f(CASE / j.getTexture().getSize().x, CASE / j.getTexture().getSize().y));
	j.cleanRange();
	j.setRange(j.getPosition().x, j.getPosition().y, j.getRange(), map.size());

	enemys.clear();

	srand(time(nullptr));
	for (int i = 0; i < rand() % 20+20; i++)
	{
		enemys.push_back(Enemy(map));
	}
	cout << enemys.size() << endl;
	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i].setPos(sf::Vector2i(rand() % map.size(), rand() % map.size()));
		enemys[i].setSpritePath("src/enemy.png");
		enemys[i].setSprite("src/enemy.png");
		enemys[i].setSpriteScale(sf::Vector2f(CASE / enemys[i].getTexture().getSize().x, CASE / enemys[i].getTexture().getSize().y));
		enemys[i].setDelaiAttaque(1000);
		enemys[i].setDelaiAttaque(sf::Clock());
		j.setID(enemys[i].addJoueur(j.getPosition()));
		enemys[i].cleanVisited();
		enemys[i].setVisited(enemys[i].getPosition().x, enemys[i].getPosition().y, enemys[i].getRange());
	}
}

int main()
{
	Bruit b = Bruit(TAILLE, TAILLE, PAS, OCTAVES);
	vector<vector<int>> map;
	for (int i = 0; i < TAILLE/CASE; i++)
	{
		vector<int> d1;
		for (int j = 0; j < TAILLE/CASE; j++)
		{
			d1.push_back(b.obtenirCaseS1(i*CASE, j*CASE, PERSISTANCE, 0.5, CASE));
		}
		map.push_back(d1);
	}

	b.~Bruit();

	TileMap tileMap;
	if (!tileMap.load("src/map.png", sf::Vector2u(32, 32), map, map.size(), map.size()))
		return -1;

	sf::RectangleShape mouseCursor;
	mouseCursor.setFillColor(sf::Color::Transparent);
	mouseCursor.setSize(sf::Vector2f(CASE, CASE));
	mouseCursor.setOutlineColor(sf::Color::Black);
	mouseCursor.setOutlineThickness(1);


	//---------------------------------//

	Joueur j;

	sf::Text jVie;
	sf::Font font;
	font.loadFromFile("src/arial.ttf");
	jVie.setFont(font);
	jVie.setCharacterSize(CASE / 2);

	sf::CircleShape recuperationMoveJoueur(0, 300);
	recuperationMoveJoueur.setFillColor(sf::Color(0, 0, 255, 120));

	sf::CircleShape recuperationAttaqueJoueur(0, 300);
	recuperationAttaqueJoueur.setFillColor(sf::Color(255, 0, 0, 120));
	
	sf::Texture tDegats;
	tDegats.loadFromFile("src/degats.png");
	sf::Sprite degats(tDegats);
	
	//---------------------------------//
	
	vector<Enemy> enemys;

	initJeu(j, enemys, map);

	sf::Vector2i pMouse;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	
	sf::RenderWindow window;
	//window.setFramerateLimit(60);
	window.create(sf::VideoMode(TAILLE, TAILLE), "Génération de bruit", sf::Style::Default, settings);
	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			for (int i = 0; i < enemys.size(); i++)
			{
				enemys[i].getCD()->restart();
			}
			j.getClockDeplacement()->restart();
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

		sf::Text restart;
		sf::Font font;
		font.loadFromFile("src/arial.ttf");
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
			//CALCULS JEU / TOUR
			pMouse.x = sf::Mouse::getPosition(window).x / CASE;
			pMouse.y = sf::Mouse::getPosition(window).y / CASE;
			mouseCursor.setPosition(sf::Vector2f(pMouse.x*CASE, pMouse.y*CASE));
			if (j.getClockDeplacement()->getElapsedTime().asMilliseconds() > j.getDelaiDeplacement())
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
					&& j.getPosition().x < (TAILLE / CASE) - 1)
				{
					j.setPos(sf::Vector2i(j.getPosition().x + 1, j.getPosition().y));
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
					&& j.getPosition().x > 0)
				{
					j.setPos(sf::Vector2i(j.getPosition().x - 1, j.getPosition().y));
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
					&& j.getPosition().y < (TAILLE / CASE) - 1)
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
					j.setRange(j.getPosition().x, j.getPosition().y, j.getRange(), map.size());
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
						j.setVie(j.getVie() - 1);
						enemys[i].getCD()->restart();
					}
				}
			}
		}

		//AFFICHAGE

		window.clear();
		window.draw(tileMap);

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

			sf::RectangleShape range(sf::Vector2f(CASE, CASE));
			range.setFillColor(sf::Color(255, 0, 0, 50));
			for (int j = 0; j < enemys[i].getVisitedx().size(); j++)
			{
				range.setPosition(CASE*enemys[i].getVisitedx()[j], CASE*enemys[i].getVisitedy()[j]);
				window.draw(range);
			}
		}

		j.setSpritePosition(sf::Vector2f(j.getPosition().x*CASE, j.getPosition().y*CASE));
		recuperationMoveJoueur.setPosition(sf::Vector2f(j.getPosition().x*CASE, j.getPosition().y*CASE));
		recuperationMoveJoueur.setRadius(0);
		recuperationAttaqueJoueur.setPosition(sf::Vector2f(pMouse.x*CASE, pMouse.y*CASE));
		recuperationAttaqueJoueur.setRadius(0);
		window.draw(j.getSprite());

		if (j.getClockDeplacement()->getElapsedTime().asMilliseconds() < j.getDelaiDeplacement())
		{
			int tcd = j.getDelaiDeplacement() - j.getClockDeplacement()->getElapsedTime().asMilliseconds();
			int radius = (((CASE / 2)*tcd) / j.getDelaiDeplacement());
			recuperationMoveJoueur.setPosition(sf::Vector2f(j.getPosition().x*CASE + (CASE / 2) - radius, j.getPosition().y*CASE + (CASE / 2) - radius));
			recuperationMoveJoueur.setRadius(radius);
		}
		window.draw(recuperationMoveJoueur);

		if (j.getClockAttaque()->getElapsedTime().asMilliseconds() < j.getDelaiAttaque())
		{
			int tcd = j.getDelaiAttaque() - j.getClockAttaque()->getElapsedTime().asMilliseconds();
			int radius = (((CASE / 2)*tcd) / j.getDelaiAttaque());
			recuperationAttaqueJoueur.setPosition(sf::Vector2f(pMouse.x*CASE + (CASE / 2) - radius, pMouse.y*CASE + (CASE / 2) - radius));
			recuperationAttaqueJoueur.setRadius(radius);
		}
		window.draw(recuperationAttaqueJoueur);




		jVie.setString(std::to_string(j.getVie()));
		jVie.setPosition(j.getPosition().x*CASE+(CASE/2) - jVie.getLocalBounds().width /2, j.getPosition().y*CASE - CASE / 2);

		window.draw(jVie);
		window.draw(mouseCursor);
		window.draw(restart);

		window.display();
	}

	return 0;
}