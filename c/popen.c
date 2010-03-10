#include <stdio.h>
#include <unistd.h>

#define SEPERATOR "+++"

int pause(void);
main(int argc, char **argv) {
	FILE *fp;
	char line[130];

	fp = popen("ls -l", "r");
	
	printf("%s", fp);
	/*while(fgets( line, sizeof line, fp )){
		printf("%s", line);
		printf("\n%s\n", SEPERATOR);
	}*/
	pclose(fp);
}
