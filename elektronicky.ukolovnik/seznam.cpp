#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seznam.h"

Ukol* pridat_ukol(Ukol* prvni, int id, const char* text, Datum d, int hodina, int minuta, int priorita) {
    // 1. Alokace pamìti pro nový úkol
    Ukol* novy = (Ukol*)malloc(sizeof(Ukol)); //vytvoøí v pamìti prostor pro uložení úkolu

    if (novy == NULL) {
        printf("Chyba: Nedostatek pameti!\n");
        return prvni; // Vracíme pùvodní seznam beze zmìny
    }

    //Naplnìní daty
    novy->id = id;
    strcpy(novy->popis, text); // Kopírování textu (string copy)
    novy->datum = d;
    novy->hodina = hodina;
    novy->minuta = minuta;
    novy->priorita = priorita;
    novy->jeHotovo = 0; // Nový úkol není hotový

    // 3. Zapojení do seznamu
    novy->dalsi = prvni; // Nový úkol ukazuje na ten, co byl doteï první

    return novy; // Nový úkol je teï novým zaèátkem seznamu
}
Ukol* smazat_ukol(Ukol* prvni, int id) {
    Ukol* aktualni = prvni;
    Ukol* predchozi = NULL;

    while (aktualni != NULL) {
        if (aktualni->id == id) {
            // NAŠLI JSME ÚKOL K SMAZÁNÍ

            if (predchozi == NULL) {
                // 1. Mazeme hned prvni ukol v seznamu
                Ukol* novy_zacatek = aktualni->dalsi;
                free(aktualni); // Uvolníme pamì
                return novy_zacatek;
            }
            else {
                // 2. Mazeme ukol uprostred nebo na konci
                predchozi->dalsi = aktualni->dalsi; // "Obejdeme" mazaný úkol
                free(aktualni);
                return prvni; // Zaèátek se nezmìnil
            }
        }

        // Posun na další
        predchozi = aktualni;
        aktualni = aktualni->dalsi;
    }

    return prvni; // Pokud jsme nic nenašli, vracíme seznam beze zmìny
}

void prepnout_stav_ukolu(Ukol* prvni, int id) {
    Ukol* aktualni = prvni;
    while (aktualni != NULL) {
        if (aktualni->id == id) {
            // Pøepínaè (pokud je 0, dá 1, pokud 1, dá 0)
            if (aktualni->jeHotovo == 0) {
                aktualni->jeHotovo = 1;
            }
            else {
                aktualni->jeHotovo = 0;
            }
            return; // Hotovo, konèíme hledání
        }
        aktualni = aktualni->dalsi;
    }
}
void presunout_ukol(Ukol* prvni, int id, Datum noveDatum) {
    Ukol* aktualni = prvni;
    while (aktualni != NULL) {
        if (aktualni->id == id) {
            aktualni->datum = noveDatum; // Pouze zmìníme datum
            return;
        }
        aktualni = aktualni->dalsi;
    }
}

Ukol* kopirovat_ukol(Ukol* prvni, int id_zdroj, int id_novy, Datum noveDatum) {
    Ukol* aktualni = prvni;

    // Hledáme vzorový úkol, který chceme zkopírovat
    while (aktualni != NULL) {
        if (aktualni->id == id_zdroj) {
            // Našli jsme ho -> Vytvoøíme nový úkol se stejnými daty, ale novým ID a Datem
            return pridat_ukol(prvni,
                id_novy,
                aktualni->popis,
                noveDatum,
                aktualni->hodina,
                aktualni->minuta,
                aktualni->priorita);
        }
        aktualni = aktualni->dalsi;
    }
    return prvni; // Pokud jsme zdroj nenašli, nic se nestane
}
int generuj_nove_id(Ukol* prvni) {
    int max_id = 0;
    Ukol* aktualni = prvni;

    while (aktualni != NULL) {
        if (aktualni->id > max_id) {
            max_id = aktualni->id;
        }
        aktualni = aktualni->dalsi;
    }

    return max_id + 1; // Vrátíme o jedno víc než je maximum
}