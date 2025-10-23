// pocitaniZnaku.cpp : Defines the entry point for the application.
//

#include "pocitaniZnaku.h"
#include "ctype.h"

using namespace std;

int calcCharakters(char* text) {
	int count = 0;
	for (int i = 0; text[i] != '\0'; i++) {

		if (isalpha(text[i])) {
			count++;
		}
	}
	return count;
}
int calcNumbers(char* text) {
	int count = 0;
	for (int i = 0; text[i] != '\0'; i++) {

		if (isdigit(text[i])) {
			count++;
		}
	}
	return count;
}
int maxDelkaSlova(char* text) {
	int pocet = 0;
	int maxDelka = 0;
	for (int i = 0; text[i] != '\0'; i++) {
		if (isalpha(text[i])) {
			pocet++;
			if(pocet > maxDelka){
				maxDelka = pocet;
			}
		}
		else {
			pocet = 0;
		}
	}
	
	return maxDelka;
}


int main()
{
	
	char text[] = "Toto jsou 2 vzorove vety, ktere budou zpracovavany Vasemi funkcemi. Auto Hyundai ix35 ma pres 120 konskych sil.";

	calcCharakters(text);
	calcNumbers(text);
	maxDelkaSlova(text);
	printf("Statistiky textu:\n ");
	printf("\tPismena: %d\n", calcCharakters(text));
	printf("\tCisla: %d\n", calcNumbers(text));
	printf("\tNejdelsi slovo: %d\n", maxDelkaSlova(text));
	return 0;
}
