#include <stdio.h>

#define MAX 10

int array[MAX], count;

int groesster( int x[], int y);

int main(void){
	for ( count = 0; count < MAX; count++) {
		printf("Geben Sie einen Integerwert ein: ");
		scanf("%d", &array[count]);
	}

	/* Ruft die Funktion auf und zeigt den Rückgabewert an. */
	printf("\n\nGrösster Wert = %d\n", groesster(array, MAX));
	return 0;
}

int groesster(int x[], int y) {
	int count, max = x[0];

	for( count = 0; count < y; count++) {
		if( x[count] > max)
			max = x[count];
	}
	return max;
}
