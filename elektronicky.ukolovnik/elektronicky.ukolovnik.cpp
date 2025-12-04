#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>       // Pro práci s časem
#include <windows.h>    // Pro barvy v konzoli
#include <conio.h>  //  _getch()
#include "data.h" 
#include "seznam.h"
#include "soubory.h"
#include "elektronicky.ukolovnik.h"
#include "kalendar.h"

using namespace std;

// --- POMOCNÉ FUNKCE ---
// Funkce posune datum o +1 nebo -1 den a vyřeší přechody měsíců
Datum posun_datum(Datum d, int smer) {
    // Počet dní v měsících (index 0 ignorujeme, leden je index 1)
    int dny_v_mesici[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    //přestupný rok roku pro únor
    if ((d.rok % 4 == 0 && d.rok % 100 != 0) || (d.rok % 400 == 0)) {
        dny_v_mesici[2] = 29;
    }

    d.den += smer; // Přičteme nebo odečteme den

    // Logika pro posun dopředu (přetekl počet dní v měsíci)
    if (d.den > dny_v_mesici[d.mesic]) {
        d.den = 1;
        d.mesic++;
        if (d.mesic > 12) {
            d.mesic = 1;
            d.rok++;
        }
    }
    // Logika pro posun dozadu (den je 0)
    else if (d.den < 1) {
        d.mesic--;
        if (d.mesic < 1) {
            d.mesic = 12;
            d.rok--;
        }
        d.den = dny_v_mesici[d.mesic]; // Nastavíme na poslední den předchozího měsíce
    }

    return d;
}


// Funkce pro nastavení barvy textu podle priority
void nastav_barvu(int priorita) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int kód_barvy = 7; // 7 = bílá (výchozí)

    switch (priorita) {
    case 3: kód_barvy = 12; break; // 12 = Červená (Vysoká)
    case 2: kód_barvy = 14; break; // 14 = Žlutá (Střední)
    case 1: kód_barvy = 10; break; // 10 = Zelená (Nízká)
    default: kód_barvy = 7; break;
    }
    SetConsoleTextAttribute(hConsole, kód_barvy);
}

// Funkce vrátí dnešní datum
Datum dnesni_datum() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    Datum d;
    d.den = tm.tm_mday;
    d.mesic = tm.tm_mon + 1; // Měsíce jsou 0-11, proto +1
    d.rok = tm.tm_year + 1900; // Roky jsou od 1900
    return d;
}

void nacti_text(char* buffer, int max_len) {
    scanf(" %[^\n]", buffer);
}



// Vypíše jen úkoly, které odpovídají zadanému datu
void vypis_den(Ukol* seznam, Datum d) {
    Ukol* aktualni = seznam;
    int nalezeno = 0;

    printf("\n--- UKOLY PRO %02d.%02d.%d ---\n", d.den, d.mesic, d.rok);

    while (aktualni != NULL) {
        if (aktualni->datum.den == d.den &&
            aktualni->datum.mesic == d.mesic &&
            aktualni->datum.rok == d.rok) {

            // Barvy: Pokud je hotovo, bude zelená (10), jinak podle priority
            if (aktualni->jeHotovo) {
                nastav_barvu(10); // Zelená
                printf("[HOTOVO] ");
            }
            else {
                nastav_barvu(aktualni->priorita);
                //printf("[     ] ");
            }
            if (aktualni->hodina != -1) {
                printf("%02d:%02d | ", aktualni->hodina, aktualni->minuta);
            }
            else {
                printf("--:-- | "); // Nebo prázdné místo
            }
           
            printf("%s (ID:%d)\n", aktualni->popis, aktualni->id);

            nastav_barvu(0); // Reset
            nalezeno = 1;
        }
        aktualni = aktualni->dalsi;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    if (!nalezeno) printf("(Zadne ukoly pro tento den)\n");
    printf("----------------------------\n");
}

Ukol* dialog_pridat_ukol(Ukol* seznam)  {
    // 1. Získáme automatické ID
    int id = generuj_nove_id(seznam);

    int priorita;
    int h = -1, m = 0;
    char text[MAX_TEXT];
    char cas_vstup[20];
    Datum d;

    system("cls");
    printf("--- PRIDANI NOVEHO UKOLU ---\n");
    printf("Pridelene ID: %d\n", id);
    printf("----------------------------\n");

    printf("Zadej text ukolu: ");
    nacti_text(text, MAX_TEXT);

    printf("Zadej datum (den mesic rok): ");
    scanf("%d %d %d", &d.den, &d.mesic, &d.rok);

    printf("Zadej CAS (HH:MM) nebo 'x' pro ukol bez casu: ");
    scanf("%s", cas_vstup);

    if (cas_vstup[0] == 'x' || cas_vstup[0] == 'X') {
        h = -1;
        m = 0;
    }
    else {
        if (sscanf(cas_vstup, "%d:%d", &h, &m) != 2) {
            h = -1;
        }
    }

    printf("Zadej prioritu (1=Nizka, 2=Stredni, 3=Vysoka): ");
    scanf("%d", &priorita);

    return pridat_ukol(seznam, id, text, d, h, m, priorita);
}



int main()
{
    Ukol* mujSeznam = NULL;
    Datum zobrazeneDatum = dnesni_datum(); // Začínáme na dnešku
    int klavesa; // Proměnná pro načtení kódu klávesy
    const char* JMENO_SOUBORU = "data.txt"; 
    // 1. NAČTENÍ DAT PŘI STARTU
    mujSeznam = nacti_data(JMENO_SOUBORU);

    // 0 = Denní výpis, 1 = Kalendář
    int rezim_zobrazeni = 0;
    
    mujSeznam = nacti_data(JMENO_SOUBORU);
    if (mujSeznam == NULL) {
        mujSeznam = pridat_ukol(mujSeznam, 1, "Vitejte...", zobrazeneDatum, -1, 0, 1);
    }

    // Hlavní smyčka programu
    do {
        system("cls"); // Smažeme obrazovku

        // 1. Vykreslení hlavičky a úkolů
        printf("=== ELEKTRONICKY UKOLOVNIK ===\n");
        printf("[<] [>] Navigace  [1] Pridat  [2] Datum  [3] Hotovo  [4] Smazat\n");
        printf("[5] Presun  [6] Kopirovat  [7] Zmenit pohled (Den/Mesic)  [Esc] Konec\n");
        printf("==============================\n");

        // --- ROZHODOVÁNÍ CO VYKRESLIT ---
        if (rezim_zobrazeni == 0) {
            vypis_den(mujSeznam, zobrazeneDatum);
        }
        else {
            // Voláme funkci z nového souboru kalendar.c
            vykresli_kalendar(mujSeznam, zobrazeneDatum.mesic, zobrazeneDatum.rok, zobrazeneDatum.den);

            printf("\nDetail pro vybrany den:\n");
            vypis_den(mujSeznam, zobrazeneDatum);
        }
        // --------------------------------

        // 2. Čekání na stisk klávesy (bez nutnosti Enteru)
        klavesa = _getch();

        // 3. Rozhodování co udělat
        if (klavesa == 224) {
            // 224 znamená, že byla stisknuta šipka (nebo funkční klávesa).
            // Musíme zavolat _getch() znovu, abychom zjistili, která to byla.
            klavesa = _getch();

            switch (klavesa) {
            case 75: // Šipka vlevo (Code 75)
                zobrazeneDatum = posun_datum(zobrazeneDatum, -1);
                break;
            case 77: // Šipka vpravo (Code 77)
                zobrazeneDatum = posun_datum(zobrazeneDatum, 1);
                break;
                // Šipky nahoru/dolů posouvají o týden (hodí se v kalendáři)
            case 72: // Nahoru
                for (int i = 0; i < 7; i++) zobrazeneDatum = posun_datum(zobrazeneDatum, -1);
                break;
            case 80: // Dolu
                for (int i = 0; i < 7; i++) zobrazeneDatum = posun_datum(zobrazeneDatum, 1);
                break;
            }
        }
        else {
            // Bylo stisknuto normální písmeno nebo číslo
            switch (klavesa) {
            case '1': // Přidat
                mujSeznam = dialog_pridat_ukol(mujSeznam);
                // Po návratu z dialogu se obrazovka překreslí
                break;
            case '2': // Skok na konkrétní datum
                printf("\nZadej datum k zobrazeni (den mesic rok): ");
                // Načteme do pomocných proměnných
                int d, m, r;
                // scanf vrátí 3, pokud se podařilo načíst všechna 3 čísla
                if (scanf("%d %d %d", &d, &m, &r) == 3) {
                    zobrazeneDatum.den = d;
                    zobrazeneDatum.mesic = m;
                    zobrazeneDatum.rok = r;
                }
                break;

            case '3': // Hotovo
                printf("\nZadej ID ukolu pro zmenu stavu: ");
                int id_zmena;
                if (scanf("%d", &id_zmena) == 1) prepnout_stav_ukolu(mujSeznam, id_zmena);
                break;

            case '4': // Smazat
                printf("\nZadej ID ukolu pro smazani: ");
                int id_smazat;
                if (scanf("%d", &id_smazat) == 1) mujSeznam = smazat_ukol(mujSeznam, id_smazat);
                break;
            case '5': // PŘESUN (MOVE)
            {
                printf("\n--- PRESUN UKOLU ---\n");
                printf("Zadej ID ukolu, ktery chces presunout: ");
                int id_move;
                if (scanf("%d", &id_move) == 1) {
                    printf("Zadej NOVE datum (den mesic rok): ");
                    Datum d_move;
                    if (scanf("%d %d %d", &d_move.den, &d_move.mesic, &d_move.rok) == 3) {
                        presunout_ukol(mujSeznam, id_move, d_move);
                        printf("Ukol presunut.\n");
                    }
                }
                break;
            }

            case '6': // KOPÍROVÁNÍ
            {
                printf("\n--- KOPIROVANI UKOLU ---\n");
                printf("Zadej ID kopirovaneho ukolu: ");
                int id_src;
                if (scanf("%d", &id_src) == 1) {
                    printf("Zadej datum pro kopii (den mesic rok): ");
                    Datum d_copy;
                    scanf("%d %d %d", &d_copy.den, &d_copy.mesic, &d_copy.rok);

                    // --- AUTOMATICKÉ ID I TADY ---
                    int id_new = generuj_nove_id(mujSeznam);
                    printf("Kopii prideleno ID: %d\n", id_new);
                    // -----------------------------

                    mujSeznam = kopirovat_ukol(mujSeznam, id_src, id_new, d_copy);
                    printf("Ukol uspesne zkopirovan.\n");
                    _getch(); // Čekání, ať si to uživatel přečte
                }
                break;
            }
            case '7': // PŘEPÍNAČ POHLEDU
                rezim_zobrazeni = !rezim_zobrazeni; // Přepne 0->1 nebo 1->0
                break;

            case 27: // Klávesa ESC (ASCII kód 27) - Konec
                printf("\nKoncim program...\n");
                // 2. ULOŽENÍ DAT PŘI UKONČENÍ
                system("cls");
                uloz_data(JMENO_SOUBORU, mujSeznam);
                printf("\nProgram ukoncen. Stisknete libovolnou klavesu...");
                _getch();
                return 0;
            }
        }

    } while (1); // Nekonečná smyčka, ukončí se přes return 0 u ESC

    return 0;
}
