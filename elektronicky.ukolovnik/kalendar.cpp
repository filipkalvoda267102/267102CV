#include <stdio.h>
#include <time.h>
#include <windows.h> // Pro barvièky
#include "kalendar.h"

// --- INTERNÍ POMOCNÉ FUNKCE (nejsou v .h souboru) ---

// Zjistí, zda je pro dané datum v seznamu nìjakı úkol
int ma_ukol(Ukol* seznam, int d, int m, int r) {
    Ukol* aktualni = seznam;
    while (aktualni != NULL) {
        if (aktualni->datum.den == d &&
            aktualni->datum.mesic == m &&
            aktualni->datum.rok == r) {
            return 1; // Ano, našli jsme úkol
        }
        aktualni = aktualni->dalsi;
    }
    return 0; // Ne
}

// Zjistí poèet dní v mìsíci
int pocet_dni_v_mesici(int m, int r) {
    if (m == 2) {
        if ((r % 4 == 0 && r % 100 != 0) || (r % 400 == 0)) return 29;
        return 28;
    }
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    return 31;
}

// Zjistí, kterım dnem v tıdnu zaèíná mìsíc (0=Po, ... 6=Ne)
int prvni_den_v_tydnu(int m, int r) {
    struct tm time_in = { 0 };
    time_in.tm_mday = 1;
    time_in.tm_mon = m - 1;
    time_in.tm_year = r - 1900;
    mktime(&time_in);

    int den = time_in.tm_wday - 1;
    if (den < 0) den = 6;
    return den;
}

// --- HLAVNÍ FUNKCE PRO VYKRESLENÍ ---

void vykresli_kalendar(Ukol* seznam, int m, int r, int aktualni_den) {
    int dny = pocet_dni_v_mesici(m, r);
    int odsazeni = prvni_den_v_tydnu(m, r);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("\n--- KALENDAR: %02d / %d ---\n", m, r);
    printf(" Po Ut St Ct Pa So Ne\n");
    printf("---------------------\n");

    // Mezery pøed prvním dnem
    for (int i = 0; i < odsazeni; i++) printf("   ");

    for (int den = 1; den <= dny; den++) {
        int ma_neco = ma_ukol(seznam, den, m, r);

        // Logika barev
        if (den == aktualni_den) {
            // Tyrkysová pro vybranı den (kurzor)
            SetConsoleTextAttribute(hConsole, 3 + (ma_neco ? 128 : 0));
        }
        else if (ma_neco) {
            // Èervená pro dny s úkolem
            SetConsoleTextAttribute(hConsole, 12);
        }
        else {
            // Bílá pro ostatní
            SetConsoleTextAttribute(hConsole, 7);
        }

        printf("%3d", den);

        SetConsoleTextAttribute(hConsole, 7); // Reset barvy

        // Odøádkování po nedìli
        if ((odsazeni + den) % 7 == 0) printf("\n");
    }
    printf("\n---------------------\n");
}