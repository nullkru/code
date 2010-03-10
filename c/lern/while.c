#include <stdio.h>

int main(int argc, char *argv[]) {
	int x;
	int ergebnis = 0;

	printf("Gib 0 zum Beenden ein \n");

	do {
		printf("Zahl: ");
		scanf("%d", &x);
		ergebnis+=x;
		printf("Ergebnis: %d\n", ergebnis);

	} while(x != 0);
}
