#include "bruit.h"

using namespace std;

Bruit::Bruit(int l, int h, int p, int n)
{
	initBruit2D(l, h, p, n);
}

double Bruit::interpolation_cos1D(double a, double b, double x)
{
	double k = (1 - cos(x * PI)) / 2;
	return a * (1 - k) + b * k;
}

void Bruit::initBruit2D(int l, int h, int p, int n) {
	nombre_octaves2D = n;
	if (longueur != 0)
		free(valeurs2D);
	longueur = l;
	hauteur = h;
	pas2D = p;
	longueur_max = (int)ceil(longueur * pow(2, nombre_octaves2D - 1) / pas2D);
	hauteur_max = (int)ceil(hauteur * pow(2, nombre_octaves2D - 1) / pas2D);

	valeurs2D = (double*)malloc(sizeof(double) * longueur_max * hauteur_max);
	
	seed = time(nullptr);
	srand(seed);
	cout <<"seed:"<< seed<<endl;
	for (int i = 0; i < longueur_max * hauteur_max; i++)
		valeurs2D[i] = ((double)rand()) / RAND_MAX;
}

void Bruit::destroyBruit2D() {
	if (longueur != 0)
		free(valeurs2D);
	longueur = 0;
}

double Bruit::bruit2D(int i, int j) {
	return valeurs2D[i * longueur + j];
}

double Bruit::interpolation_cos2D(double a, double b, double c, double d, double x, double y) {
	double y1 = interpolation_cos1D(a, b, x);
	double y2 = interpolation_cos1D(c, d, x);
	return  interpolation_cos1D(y1, y2, y);
}

double Bruit::fonction_bruit2D(double x, double y) {
	int i = (int)(x / pas2D);
	int j = (int)(y / pas2D);
	return interpolation_cos2D(bruit2D(i, j), bruit2D(i + 1, j), bruit2D(i, j + 1), bruit2D(i + 1, j + 1), fmod(x / pas2D, 1), fmod(y / pas2D, 1));
}

double Bruit::bruit_coherent2D(double x, double y, double persistance) {
	double somme = 0;
	double p = 1;
	int f = 1;
	int i;

	for (i = 0; i < nombre_octaves2D; i++) {
		somme += p * fonction_bruit2D(x * f, y * f);
		p *= persistance;
		f *= 2;
	}
	return somme * (1 - persistance) / (1 - p);
}

sf::Color Bruit::obtenirCouleur(int rouge, int vert, int bleu) {
	sf::Color color;
	color.r = rouge;
	color.g = vert;
	color.b = bleu;
	return color;
}

int Bruit::obtenirCaseS1(int x, int y, float p, double seuil, double seuil2, int t)
{
	double sm = 0.0;
	for (int i = x; i < x + t && i < hauteur_max; i++)
	{
		for (int j = y; j < y + t && j < longueur_max; j++)
		{
			sm += bruit_coherent2D(x, y, p);
		}
	}
	double valeur = sm / (t*t);


	// TRAITEMENT DE LA TEXTURE / MONDE/ HAUTEUR SELON valeur
	if (valeur < seuil)
	{
		return 0;
	}
	else if(valeur > seuil && valeur < seuil+0.05)
	{
		return 1;
	}
	else if (valeur > seuil && valeur < seuil2)
	{
		return 2;
	}
	else if(valeur > seuil2 && valeur < seuil2+0.5)
	{
		return 3;
	}
	else
	{
		return 4;
	}
}

Bruit::~Bruit()
{
	destroyBruit2D();
}
