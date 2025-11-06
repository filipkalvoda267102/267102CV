

#include "prunik.h"
#include "kalvoda.h"
#include <stdio.h>

int main()
{
	double z1, z2, k1, k2;
	double vysledekZ, vysledekK;
	double zz1, kk1, zz2, kk2;

	

	z1 = 1.5;
	k1 = 2.8;
	z2 = 1.6;
	k2 = 2.0;
	prunik(z1, k1, z2, k2, &vysledekZ, &vysledekK);

	z1 = 1.5;
	k1 = 2.8;
	z2 = 3.6;
	k2 = 7.5;
	prunik(z1, k1, z2, k2, &vysledekZ, &vysledekK);

	z1 = 1.5;
	k1 = 4.8;
	z2 = 2.6;
	k2 = 7.5;
	prunik(z1, k1, z2, k2, &vysledekZ, &vysledekK);

	z1 = 5.1;
	k1 = -2.3;
	z2 = 1.5;
	k2 = 6.2;
	prunik(z1, k1, z2, k2, &vysledekZ, &vysledekK);

	z1 = 2.5;
	k1 = 8.8;
	z2 = -0.3;
	k2 = 9.5;
	prunik(z1, k1, z2, k2, &vysledekZ, &vysledekK);

	z1 = 5.5;
	k1 = -9.5;
	z2 = 9.9;
	k2 = -2.3;
	prunik(z1, k1, z2, k2, &vysledekZ, &vysledekK);



	printf("Zadejte 1. interval: ");
	scanf_s("%lf %lf", &zz1, &kk1);
	printf("Zadejte 2. interval: ");
	scanf_s("%lf %lf", &zz2, &kk2);
	prunik(zz1, kk1, zz2, kk2, &vysledekZ, &vysledekK);

	

	return 0;
}
