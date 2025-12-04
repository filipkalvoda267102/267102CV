#ifndef SEZNAM_H
#define SEZNAM_H

#include "data.h"

// Funkce pøidá nový úkol na zaèátek seznamu a vrátí ukazatel na nový zaèátek
Ukol* pridat_ukol(Ukol* prvni, int id, const char* text, Datum d, int hodina, int minuta, int priorita);

// Funkce smaže úkol podle ID a vrátí nový zaèátek seznamu
Ukol* smazat_ukol(Ukol* prvni, int id);

// Funkce najde úkol podle ID a pøepne stav (Hotovo/Nehotovo)
void prepnout_stav_ukolu(Ukol* prvni, int id);

// Zmìní datum u existujícího úkolu
void presunout_ukol(Ukol* prvni, int id, Datum noveDatum);

// Vytvoøí kopii úkolu s novým ID a novým datem
Ukol* kopirovat_ukol(Ukol* prvni, int id_zdroj, int id_novy, Datum noveDatum);

// Funkce najde nejvyšší ID v seznamu a vrátí (max + 1)
int generuj_nove_id(Ukol* prvni);

#endif