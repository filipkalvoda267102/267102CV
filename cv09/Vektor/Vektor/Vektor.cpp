
#include <stdio.h>
#include "Vektor.h"
#include "VektorMath.h"

using namespace std;

int main()
{
	struct vector3d u, v, w;
	enum typOperace op;

	printf("Zadej vektor u (hodnoty oddelene carkou): ");
	scanf_s("%lf,%lf,%lf", &u.x, &u.y, &u.z);
	printf("Zadej vektor v (hodnoty oddelene carkou): ");
	scanf_s("%lf,%lf,%lf", &v.x, &v.y, &v.z);

	printf("Zadejte operaci (1= soucet, 2= vektorovySoucin, 3= porovnani: ");
	scanf_s("%d", &op);


	w = operace(u, v, op);

	printf("Vysledek operace:\n");

		tisk(w);
	
	
		/*double velikostU = vectorSize(u);
		double velikostV = vectorSize(v);
		printf("\n|u| = %.3f\n|v| = %.3f\n", velikostU, velikostV);

		int porovnani = vectorSizeComparation(u, v);

		if (porovnani > 0)
			printf("Vektor u je vetsi nez vektor v.\n");
		else if (porovnani < 0)
			printf("Vektor u je mensi nez vektor v.\n");
		else
			printf("Vektory u a v maji stejnou velikost.\n");


	*/

	return 0;
}


