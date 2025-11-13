#include "VektorMath.h"
#include <cmath>
#include <stdio.h>


struct vector3d operace(struct vector3d u, struct vector3d v, enum typOperace typ)
{
    struct vector3d vysledek;

   switch(typ) {
        case soucet:
        vysledek.x = u.x + v.x;
        vysledek.y = u.y + v.y;
        vysledek.z = u.z + v.z;
        break;
        case vektorovySoucin:
        vysledek.x = u.y * v.z - u.z * v.y;
        vysledek.y = u.z * v.x - u.x * v.z;
        vysledek.z = u.x * v.y - u.y * v.x;
        break;
           

    }
   
    return vysledek;
}

void tisk(struct vector3d u)
{
    printf("w = (%.3f, %.3f, %.3f)\n", u.x, u.y, u.z);
    printf("|w| = %.3f\n", sqrt(u.x * u.x + u.y * u.y + u.z * u.z));
}


double vectorSize(struct vector3d u) {
    return sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
}

int vectorSizeComparation(struct vector3d u, struct vector3d v) {

    double sizeU = vectorSize(u);
    double sizeV = vectorSize(v);


    if (sizeU < sizeV)
        return 0;
    else if (sizeU > sizeV)
        return 1;
    else
        return -1;



}