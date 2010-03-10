#include "../../lib/int80.h"

int main()
{
	char *sh = "/tmp/sh",
	     *owner = "root";
	
	chown(sh, 0, 0);
	chmod(sh, 06755);
}

