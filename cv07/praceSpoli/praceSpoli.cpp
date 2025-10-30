

#include "praceSpoli.h"

#include "Body2d.h"

#define POCET_BODU 10 

using namespace std;

int main()
{
	int souradniceX, souradniceY, idxNejblizsi;
	double prumerVzdalenost;
	int body[POCET_BODU][2] = { 5,10,
	-14,2,
	 45,4,
	 -9,8,
	 58,-3,
	 47,5,
	-18,-86,
	75,7,
	 -25,51,
	 17,98 };

	printf("Zadej souradnice referencniho bodu:\nSouradnice X:");
	scanf_s("%d", &souradniceX);
	printf("\nSouradnice Y:");
	scanf_s("%d", &souradniceY);

	idxNejblizsi = indexNejblizsi(POCET_BODU, body, souradniceX, souradniceY);
	prumerVzdalenost = prumernaVzdalenost(POCET_BODU, body, souradniceX, souradniceY);


	printf("\n\nNejblizsi bod je: [%d, %d]\n", body[idxNejblizsi][0], body[idxNejblizsi][1]);
	printf("Prumerna vzdalenost je: %lf\n\n", prumerVzdalenost);

	return 0;
}
