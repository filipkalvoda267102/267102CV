#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h> // Nutné pro strcmp
#include <stdlib.h> // Nutné pro free
#include <ctype.h> // NUTNE PRO tolower

#include "hudbaDB.h"

void add(char* znacka, char* album, int rok, struct t_auto** uk_prvni) // pridani auta
{
	struct t_auto* noveAuto; // ukazatel pro nove vkladane auto
	struct t_auto* aktAuto; // ukazatel na aktualni auto

	// alokace dynamicke promenne
	noveAuto = (struct t_auto*)malloc(sizeof(struct t_auto));

	strcpy_s(noveAuto->znacka, ZNACKA_SIZE, znacka); // naplneni struktury
	strcpy_s(noveAuto->album, ZNACKA_SIZE, album);
	noveAuto->rok = rok;
	noveAuto->dalsi = NULL;

	if (*uk_prvni == NULL) // linearni seznam je prazdny
	{
		*uk_prvni = noveAuto;
		return;
	}
	else if (strcmp(noveAuto->znacka, (*uk_prvni) ->znacka )< 0)// vlozime na zacatek
	{
		noveAuto->dalsi = *uk_prvni;
		*uk_prvni = noveAuto;
		return;
	}

	aktAuto = *uk_prvni;
	while (aktAuto) // prochazeni seznamu
	{
		if (aktAuto->dalsi == NULL) // jsme na poslednim aute
		{
			aktAuto->dalsi = noveAuto; // pridavame na konec
			return;
		}
		else if (strcmp(noveAuto->znacka, aktAuto->dalsi->znacka) < 0)
		{
			noveAuto->dalsi = aktAuto->dalsi; // vlozime za aktAuto
			aktAuto->dalsi = noveAuto;
			return;
		}
		aktAuto = aktAuto->dalsi; // posun na dalsi auto
	}
}

void del(char* album_ke_smazani, struct t_auto** uk_prvni)
{
	struct t_auto* aktAuto;

	
	while (*uk_prvni && strcmp((*uk_prvni)->znacka, album_ke_smazani) == 0)
	{
		struct t_auto* newPrvni = (*uk_prvni)->dalsi;
		free(*uk_prvni);      
		*uk_prvni = newPrvni; 
	}

	
	aktAuto = *uk_prvni;
	while (aktAuto && aktAuto->dalsi) 
	{
		
		if (strcmp(aktAuto->dalsi->album, album_ke_smazani) == 0)
		{
			struct t_auto* newDalsi = aktAuto->dalsi->dalsi;
			free(aktAuto->dalsi);      
			aktAuto->dalsi = newDalsi; 

			
		}
		else
		{
			
			aktAuto = aktAuto->dalsi;
		}
	}
}
