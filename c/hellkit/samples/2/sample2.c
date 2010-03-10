#include "../../lib/int80.h"

int main()
{
   	int fd, nfd;
        char *a[] = {"/bin/sh", 0};
	char *s = "Hello world!";
	
        fd = open("./x", O_RDWR|O_CREAT, 0600);
        nfd = dup(fd);
        write(nfd, s, 12);
        close(nfd);
        close(fd);
        execve(a[0], a, 0);
}

