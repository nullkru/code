#include <stdio.h>

int main(int argc, char *argv[]) {
	int x;
	printf("Gib eine 1,2 oder 3 ein!\n");

	scanf("%d", &x);

	switch(x) {
		case 1:
			printf("Du hast eine 1 gew�hlt\n");
			break;
		case 2:
			printf("Du hast eine 2 gew�hlt\n");
			break;
		case 3:
			printf("Du hast eine 3 gew�hlt\n");
			break;
		default:
			printf("Nix gew�hlt\n");
	}
	return 0;
}
