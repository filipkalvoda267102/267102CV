#include "kalvoda.h"
#include <stdio.h>


void podminka(double* zacatek, double* konec) {
    if (*zacatek > *konec) {
        double zmena = *zacatek;
        *zacatek = *konec;
        *konec = zmena;



    }
}

int prunik(double zacatek1, double konec1, double zacatek2, double konec2,
    double* vysl_zacatek, double* vysl_konec) {

    printf("Prunik intervalu (%.1f, %.1f) a (%.1f, %.1f)\n", zacatek1, konec1, zacatek2, konec2);

   podminka(&zacatek1, &konec1);
   podminka(&zacatek2, &konec2);

    double max_z, min_k;

    if (zacatek1 > zacatek2) {
        max_z = zacatek1;
    }
    else {
        max_z = zacatek2;
    }


    if (konec1 < konec2) {
        min_k = konec1;
    }
    else {
        min_k = konec2;
    }


    if (max_z <= min_k) {
        *vysl_zacatek = max_z;
        *vysl_konec = min_k;
        printf("je (%.1f, %.1f)\n", *vysl_zacatek, *vysl_konec);
        return 1;
    }
    else {
        printf("neexistuje\n");
        return 0;
    }


}