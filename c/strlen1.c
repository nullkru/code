#include <stdio.h>
#include <string.h>

int main() {
	char puffer[256];

	printf( "Bitte Name eingeben und <Enter> druecken:\n" );
	fgets ( puffer,256,stdin );

	printf( "\n Ihr Name enth�lt %d Zeichen (inkl. Leerzeichen).\n", 
			strlen( puffer));

	return 0;
}
