#include <stdio.h>

int main(void) {
	int a,b,c;

	printf("Addition zweier Zahlen \n\n");
	printf("a = ");
	scanf("%i", &a);
	printf("b = ");
	scanf("%i", &b);
	c = a + b;
	printf("%i + %i = %i\n", a,b,c);

	return 0;
}
