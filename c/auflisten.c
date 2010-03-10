#include <stdio.h>
#include <stdlib.h>

void usage(void);
int line;

int main( int argc, char *argv[]) {
	char puffer[256];
	FILE *fp;

	if( argc < 2 ) {
		usage();
		return 1;
	}

	if (( fp = fopen( argv[1], "r" )) == NULL ) {
		fprintf(stderr, "Fehler beim Öffnen der Datei, %s!\n", argv[1]);
	
	return 1;
	}

	line = 1;
	while(fgets( puffer, 256, fp ) != NULL )
		fprintf ( stdout, "%4d:\t%s", line++, puffer );
	
	fclose(fp);
	return 0;
	
}
void usage(void) {
	fprintf(stderr, "\nUsage: ");
	fprintf(stderr, "\n\nauflisten <file to print>\n" );
}
