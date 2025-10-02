// komplexnicislo.cpp : Defines the entry point for the application.
//

#include "komplexnicislo.h"

using namespace std;

int main()
{
	int realA;
	int imgA;
	int realB;
	int imgB;

		printf("Zadej realnou cast cisla A: ");
	scanf("%d",&realA);
		printf("Zadej imaginarni cast cisla A: ");
	scanf("%d",&imgA);
		printf("Zadej realnou cast cisla B: ");
	scanf("%d",&realB);
		printf("Zadej imaginarni cast cisla B: ");
	scanf("%d",&imgB);

	int soucetreal = realA + realB;
	int soucetimg = imgA + imgB;

	printf("\nsoucet cisla A a cisla B je %d + %di\n\n\n", soucetreal, soucetimg);
	return 0;
}
