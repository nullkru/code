#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) 
{
	//int groesse = sizeof(argc) / sizeof(int);
	//printf("%d\n", groesse);
	
	char puffer[16];

	while(puffer[0])
	{	
		int i=1;
		
		printf("[N]ext,[P]re or exit : ");
		scanf("%15s", &puffer);
		

                /* zeichenweise 

		if( puffer[0] == 'N' || puffer[0] == 'n' )
                        i++;*/

              /* strings bel. länge case-insensitive vergleichen brauch <strings.h> */

              	if( !strncasecmp(puffer, "n", 1) )
		{	
			i++;
		}
	
		if(i>0 && i<=argc)
			printf("argv[%d] :  %s \n", i, argv[i]);
	}
}
