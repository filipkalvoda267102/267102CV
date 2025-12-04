#ifndef SOUBORY_H
#define SOUBORY_H

#include "data.h"

// Uloží celý seznam do textového souboru
void uloz_data(const char* nazev_souboru, Ukol* seznam);

// Naète data ze souboru a vrátí naplnìný seznam
Ukol* nacti_data(const char* nazev_souboru);

#endif