#include <stdio.h>

void text_aus(int a);

int main(int argc, char *argv[]) {
	text_aus("blah bleh blih");
	printf("ende pende\n");
	int blah = argv[1,2,3];
	printf("%s\n", blah);
}

void text_aus(int a) {
	printf("\n\tText: %s\n", a);
}
