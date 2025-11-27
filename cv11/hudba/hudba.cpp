
#include <stdio.h>
#include <ctype.h>              // tolower
#include <stdlib.h>				// system

#include "hudba.h"
#include "hudbaDB.h"
using namespace std;

struct t_auto* prvni = NULL; // globalni ukazatel na prvni auto

void OnAdd()
{
	char my_name[ZNACKA_SIZE];
	char my_album[ZNACKA_SIZE];
	int my_year;

	

	printf("\nInterpret: ");         // dotazeme se na polozky
	scanf_s("%s", my_name, ZNACKA_SIZE);
	while (getchar() != '\n');
	printf("\nAlbum : ");         // dotazeme se na polozky
	scanf_s("%s", my_album, ZNACKA_SIZE);
	while (getchar() != '\n');
	printf("\nRok vydani: ");
	scanf_s("%d", &my_year);
	while (getchar() != '\n');
	add(my_name, my_album, my_year, &prvni);         // volame pridavaci funkci
}

void OnDel()
{
	char my_name[ZNACKA_SIZE]; // Vytvoříme paměť pro text (nejen pointer!)

	printf("\nInterpret ke smazani: ");

	// Načtení textu. Pozor: scanf_s u stringů vyžaduje velikost bufferu!
	scanf_s("%s", my_name, ZNACKA_SIZE);

	while (getchar() != '\n'); // Vyčištění bufferu klávesnice

	del(my_name, &prvni);      // Voláme funkci s textem
}



void ShowCars()
{
	struct t_auto* aktAuto = prvni; // ukazatel na aktualni auto
	printf("\n\n");
	while (aktAuto) // prochazeni seznamu
	{
		printf("%d: %s, %s\n", aktAuto->rok, aktAuto->znacka, aktAuto->album); // tisk radku
		aktAuto = aktAuto->dalsi; // posun na dalsi auto
	}
	getchar();
}


int main()
{
	char  cmd;

	do
	{
		system("cls");		// smaze obrazovku
		printf("A: Pridat     ");
		printf("D: Smazat     ");
		printf("P: Tisk     ");
		printf("F: Hledat podle pismena\n");
		printf("Q: Konec\n\n");

		cmd = tolower(getchar());
		while (getchar() != '\n');

		switch (cmd)
		{
		case 'a':
			OnAdd();					// volame pridani
			break;
		case 'd':
			OnDel();					// volame mazani
			break;
		case 'p':
			ShowCars();
			break;
		}
	} while (cmd != 'q');     // koncime az pri Q
	return 0;
}
