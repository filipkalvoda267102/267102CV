#include <limits.h>
#include "Body2d.h"
#include <math.h>
#include <stdio.h>


int indexNejblizsi(int velikost, int(*poleBodu)[2], int souradniceX, int
	souradniceY) {
	int minVzdalenost = INT_MAX;
	int hledany_idx= -1;
	for (int idx =0; idx < velikost;++idx){ 
		int dx = poleBodu[idx][0] - souradniceX;
		int dy = poleBodu[idx][1] - souradniceY;
		int aktKvadratVzdalenosti = dx * dx + dy * dy;

		if (aktKvadratVzdalenosti < minVzdalenost)
		{
			minVzdalenost = aktKvadratVzdalenosti;
			hledany_idx = idx;


		}
	}

	return hledany_idx;

}

double prumernaVzdalenost(int velikost, int(*poleBodu)[2], int souradniceX, int
	souradniceY) {
	
	int index;
	double soucet = 0.0;

	for (int index = 0; index < velikost; ++index)
	{
		int dx = poleBodu[index][0] - souradniceX;
		int dy = poleBodu[index][1] - souradniceY;
		soucet += sqrt((double)(dx * dx + dy * dy));


	}
	return soucet / velikost;

	





}

