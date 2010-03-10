#include <stdio.h>
#include <unistd.h>

int main() {
	int i = 10;
	for(i; i >= 0; i--) {
		if(i == 0){
			printf("Simpsooons\n");
		}
		else {
		printf("%d\n", i);
		usleep(150000);
		}
	}
}
