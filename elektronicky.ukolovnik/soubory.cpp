#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "soubory.h"
#include "seznam.h"

void uloz_data(const char* nazev_souboru, Ukol* seznam) {
    FILE* f = fopen(nazev_souboru, "w");
    if (f == NULL) {
        printf("Chyba: Nelze otevrit soubor pro zapis!\n");
        return;
    }

    Ukol* aktualni = seznam;
    while (aktualni != NULL) {
        // OPRAVA: Musí tu být pøesnì tolik %d/%s, kolik je promìnných
        // id;popis;den;mesic;rok;hodina;minuta;priorita;hotovo
        fprintf(f, "%d;%s;%d;%d;%d;%d;%d;%d;%d\n",
            aktualni->id,
            aktualni->popis,
            aktualni->datum.den, aktualni->datum.mesic, aktualni->datum.rok,
            aktualni->hodina,  // Nové
            aktualni->minuta,  // Nové
            aktualni->priorita,
            aktualni->jeHotovo);

        aktualni = aktualni->dalsi;
    }
    fclose(f);
    printf("Data uspesne ulozena do '%s'.\n", nazev_souboru);
}

Ukol* nacti_data(const char* nazev_souboru) {
    FILE* f = fopen(nazev_souboru, "r");
    Ukol* seznam = NULL;

    if (f == NULL) return NULL; //pokud je soubor prázdný

    
    int id, den, mesic, rok, priorita, hotovo;
    int h, m; // èas daného úkolu
    char text[MAX_TEXT]; // text úkolu

    while (fscanf(f, "%d;%[^;];%d;%d;%d;%d;%d;%d;%d\n",
        &id, text, &den, &mesic, &rok, &h, &m, &priorita, &hotovo) == 9) { // ètení devíti hodnot v souboru

        Datum d = { den, mesic, rok };
        seznam = pridat_ukol(seznam, id, text, d, h, m, priorita);

        if (hotovo) seznam->jeHotovo = 1;
    }
    fclose(f);
    printf("Data nactena.\n");
    return seznam;
}