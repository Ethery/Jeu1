Bruit b = Bruit(TAILLE*FACTEURPRECISION, TAILLE*FACTEURPRECISION, PAS, OCTAVES);
	vector<vector<int>> map;
	for (int i = 0; i < TAILLE; i++)
	{
		vector<int> d1;
		for (int j = 0; j < TAILLE; j++)
		{
			d1.push_back(b.obtenirCaseS1(i*FACTEURPRECISION, j*FACTEURPRECISION, PERSISTANCE, 0.4,0.6, FACTEURPRECISION));
		}
		map.push_back(d1);
	}

	b.~Bruit();