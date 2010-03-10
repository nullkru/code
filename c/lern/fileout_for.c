#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) 
{
	int groesse = sizeof(argc) / sizeof(int);
	printf("%d\n", groesse);
	
	int i=1;
	
	for(i; i<=argc ;i++)
	{
		printf("argv[%d] :  %s \n", i, argv[i]);
	}
}
