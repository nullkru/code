#include "../../lib/int80.h"

int main()
{
   	char *a[] = {"/bin/sh", 0};        
        execve(*a, a, 0);
}

