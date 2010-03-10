#include <stdio.h>

main(int argc, char *argv[]) {
	char *Width;
	*Width = 23;

	printf("Data stored at *Width is %d\n", *Width);
	printf("Address of Width is %p\n", &Width);
	printf("Address stored at Width is %p\n", Width);
	return 0;
}
