#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int i;
	for(i=0; i < argc; i++) {
		printf("argv[%d] = %s", i, argv[i]);
		printf("\n");
	}
	return EXIT_SUCCESS;
}
