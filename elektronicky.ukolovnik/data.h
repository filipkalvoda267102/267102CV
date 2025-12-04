#ifndef DATA_H
#define DATA_H

#define MAX_TEXT 100

// Struktura pro datum
typedef struct {
    int den;
    int mesic;
    int rok;
} Datum;

// Struktura pro úkol
typedef struct Ukol {
    int id;
    char popis[MAX_TEXT];
    Datum datum;
    int hodina;  // 0-23, nebo -1 pokud je "bez èasu"
    int minuta;  // 0-59
    int priorita;
    int jeHotovo;

    struct Ukol* dalsi;
} Ukol;

#endif