#include <stdio.h>

int main(int argc, char *argv[]) {
	int x, ergebnis;
	printf("Zahl eingeben: ");
	scanf("%d", &x);
	ergebnis = x>100 ? 100 : x;
	printf("ergebnis = %d\n", ergebnis);
}
