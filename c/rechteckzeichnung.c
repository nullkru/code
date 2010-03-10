#include <stdio.h>

void rechteck_zeichnen( int, int);

int main(void) {
	rechteck_zeichnen( 8, 35);

	return 0;
}

void rechteck_zeichnen( int reihe, int spalte ) {
	int spa;
	for ( ; reihe > 0; reihe --) {
		for( spa = spalte; spa > 0; spa -- )
			printf ("#");

		printf("\n");
	}
}
