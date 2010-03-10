#include <stdio.h>

void zahlen_addieren(int a, int b, int c);

int main(int argc, char *argv[]) {
	zahlen_addieren(10, 234, 1342);
	zahlen_addieren(234, 2345, 23);
	return 0;
}

void zahlen_addieren(int a, int b, int c) {
	printf("%d + %d + %d = %d\n", a, b, c, a + b + c);
}
