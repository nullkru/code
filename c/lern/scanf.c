#include <stdio.h>

int a=0, b=0;
int ergebnis=0;


int main(int argc, char *argv[]) {
	printf("Erste Zahl eingeben:\n");
	scanf("%d", &a);
	printf("Zweite Zahl eingeben:\n");
	scanf("%d", &b);

	ergebnis = a + b;

	printf("%d + %d = %d\n", a, b, ergebnis);

	return 0;
}
