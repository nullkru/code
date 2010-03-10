#include <stdio.h>

void ausgabe(void) {
	printf("Die Funktion ausgabe wurde aufgerufen!\n");
}

int main(int argc, char *argv[]) {
	printf("start\n");
	ausgabe();
	printf("ende\n");
}


