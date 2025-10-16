// praceSvektory.cpp : Defines the entry point for the application.
//

#include "praceSvektory.h"
#include <math.h>
using namespace std;

void soucet(double a[3], double b[3], double c[3]){
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
	c[2] = a[2] + b[2];

	}

double velikost(double a[3]) {
	return sqrt(pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2));

}

double skalarniSoucin(double a[3], double b[3]) {
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];


}

void vektorovySoucin(double a[3], double b[3], double d[3]) {
	d[0] = a[1] * b[2] - a[2] * b[1];
	d[1] = a[2] * b[0] - a[0] * b[2];
	d[2] = a[0] * b[1] - a[1] * b[0];


}
int main()
{
	double a[3], b[3], c[3], d[3];

	printf("Vektor A (3 hodnoty oddelene carkou) :");
	scanf_s("%lf, %lf, %lf", &a[0], &a[1], &a[2]);

	printf("\nVektor A (3 hodnoty oddelene carkou) :");
	scanf_s("%lf, %lf, %lf", &b[0], &b[1], &b[2]);
	printf("\n");
	soucet(a, b, c);
	printf("soucet A + B: %lf %lf %lf\n", c[0], c[1], c[2]);

	printf("\nvelikost A: %lf\n", velikost(a));

	printf("\nskalarni soucin A * B: %lf\n", skalarniSoucin(a, b));

	vektorovySoucin(a, b, d);
	printf("vektorovy soucin A*B: %lf %lf %lf\n", d[0], d[1], d[2]);

return 0;
}
