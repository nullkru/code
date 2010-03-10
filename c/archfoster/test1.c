#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PATH "/"
#define BUF "256"

FILE *pkgs;
char line[23];

int main(void) {
	int arrayno = 0;
	char *pkg;
	
	pkgs = popen("ls /", "r");
	

	while(fgets(line, sizeof line, pkgs)) {

		/* ... char blah[arrayno] = line */
		printf("%d --> %s", arrayno, line);
		/* ...printf("%s", blah[0]); */
		arrayno++;

	}
}

