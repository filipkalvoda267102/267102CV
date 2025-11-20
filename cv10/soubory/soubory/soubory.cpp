

#include "soubory.h"
#include <stdio.h> 
#include <ctype.h>


using namespace std;

int main()
{
	const char* vstupniSouborCesta = "D:\\267102\\267102CV\\cv10\\soubory\\vstup.txt";
	const char* vystupniSouborCesta = "D:\\267102\\267102CV\\cv10\\soubory\\vysledky.txt";
	char aktualniZnak;
	int pocetPismen = 0;
	int pocetCislic = 0;

	int pocetSlov = 0;
	int pocetVet = 0;
	FILE* vstup;
	FILE* vystup;

	int uvnitrSlova = 0;

	vstup = fopen(vstupniSouborCesta, "r");
	if (vstup == NULL)
	{
		printf("nelze otervit vstupni soubor");
		return -1;

	}

	while ((aktualniZnak = fgetc(vstup)) != EOF) {
		printf("%c", aktualniZnak);

		if (isalpha(aktualniZnak)) {
			pocetPismen++;
		}
		else if (isdigit(aktualniZnak)) {
			pocetCislic++;
		}

		if (aktualniZnak == '.') {
			pocetVet++;
		}

		if (isspace(aktualniZnak)) {
			
			uvnitrSlova = 0;
		}
		else {
			if (uvnitrSlova == 0) {
				pocetSlov++;
				uvnitrSlova = 1;
			}
		}
	}
	
		fclose(vstup);


		printf("\n\nPismena: %d\n", pocetPismen);
		printf("Cisla: %d\n", pocetCislic);
		printf("Pocet vet: %d\n", pocetVet);
		printf("Pocet slov: %d\n", pocetSlov);

		vystup = fopen(vystupniSouborCesta, "w");

		if (vystup == NULL) {
			printf("nelze vytvorit vystupni soubor");
			return -1;
		}

		fprintf(vystup, "Pismena: %d\n", pocetPismen);
		fprintf(vystup, "Cisla: %d\n", pocetCislic);
		fprintf(vystup, "Vety: %d\n", pocetVet);
		fprintf(vystup, "Slova: %d\n", pocetSlov);
		fclose(vystup);

	return 0;
}
