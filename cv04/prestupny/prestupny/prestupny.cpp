
#include "prestupny.h"

using namespace std;

int main()
{
	int jePrestupny(int rok);
	int jeLichy(int rok);
	printf("1000  %d\n", jePrestupny(1000));
	printf("2000  %d\n", jePrestupny(2000));
	printf("2002  %d\n", jePrestupny(2002));
	printf("2012  %d\n", jePrestupny(2012));
	printf("2022  %d\n", jePrestupny(2022));
	printf("2200  %d\n\n", jePrestupny(2200));

	printf("lichy/sudy: 1001\t %d\n", jeLichy(1001));
	printf("lichy/sudy: 2544\t %d\n", jeLichy(2544));
	printf("lichy/sudy: 9873\t %d\n", jeLichy(9873));
	printf("lichy/sudy: 1142\t %d\n", jeLichy(1142));
}
int jePrestupny(int rok) {
	int d4 = rok % 4;
	int d100 = rok % 100;
	int d400 = rok % 400;

	if (d4 == 0 && d100 != 0) {
		return 1;
	}
	else {
		if (d400 == 0) {
			return 1;
	 }
		return 0;
	}
	
}

int jeLichy(int rok) {
	int lichy = rok % 2;
	if (lichy == 0) {
		return 0;
		}
	return 1;

}