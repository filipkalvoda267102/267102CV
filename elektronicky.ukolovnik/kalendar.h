#ifndef KALENDAR_H
#define KALENDAR_H

#include "data.h" // Potøebujeme znát strukturu Ukol

// Vykreslí mìsíèní kalendáø do konzole
// Parametry: seznam úkolù (pro barvení dní), mìsíc, rok, a aktuálnì vybraný den
void vykresli_kalendar(Ukol* seznam, int m, int r, int aktualni_den);

#endif