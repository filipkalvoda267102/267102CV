

#include "Bourka.h"

using namespace std;

int main()
{
	int cas;
	printf("zadej cas v sekundach:");
	scanf("%d",&cas);
	int vysledek = cas * 340;
	printf("\nvzdalenost mista kam hrom uhodil: %d metru\n", vysledek);
	
	return 0;
}
