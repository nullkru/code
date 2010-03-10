#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PATH "/"
#define BUF "256"

FILE *pkgs;
char line[23][23];

int main(int argc, char *argv[])
{
  
  int arrayno = 0;
  char *pkg;
  
  pkgs = popen("ls /", "r");
  
  
  while(fgets(line[arrayno], 23, pkgs))
  {
    arrayno++;
  }
  
  
  //int i;
  
  //for(i = 0; i < arrayno; i++)
   // printf("line[%i] = %s", i, line[i]);
   
  int sizeofline = sizeof(line);
  printf("size of line[][] %d\n", sizeofline);  

  int puffer;  
  while( puffer != 99 ) 
  {
  	  printf("Enter number to print or exit with 99: ");
  	  scanf("%i", &puffer);
	  printf("%s\n", line[puffer]);
	  
  }
  
}
