#include <stdio.h>

void auswertung(int zahl);

int main(int argc, char *argv[]) {
	int eingabe = 0;
	printf("Gib die Zahl ein:\n");
	scanf("%d", &eingabe);
	auswertung(eingabe);
}

void auswertung(int zahl) {
	printf("Eingegeben wurde: %d\n", zahl);
}
