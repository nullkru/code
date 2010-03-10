#include <stdio.h>

int main(int argc, char **argv) {
char *args[] = {
	"-la",
	NULL,
};

execve("/bin/ls", args, NULL);

printf("exit\n\n");
}
