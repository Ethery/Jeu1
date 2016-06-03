#pragma once

#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <SFML\Graphics.hpp>

#define PI 3.141592653589793238462

class Bruit
{
private:
	int pas2D;
	int nombre_octaves2D;
	int hauteur;
	int longueur;
	int longueur_max; 
	int hauteur_max;
	double* valeurs2D;

public:
	Bruit(int l, int h, int p, int n);
	double interpolation_cos1D(double a, double b, double x);
	void initBruit2D(int l, int h, int p, int n);
	void destroyBruit2D();
	double bruit2D(int i, int j);
	double interpolation_cos2D(double a, double b, double c, double d, double x, double y);
	double fonction_bruit2D(double x, double y);
	double bruit_coherent2D(double x, double y, double persistance);

	sf::Color obtenirCouleur(int rouge, int vert, int bleu);

	sf::Color obtenirPixel(int x, int y, float p);
	
	int obtenirCaseS1(int x, int y, float p, double seuil, int t);

	~Bruit();
};