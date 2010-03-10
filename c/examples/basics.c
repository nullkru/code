#include <stdio.h>
#include <stdlib.h>

#define blah "blah bleh"*/

/* ich bin eine funktion */
int mean(int a, int b)

{
  return (a+b)/2;
}

int bleh()

{
  
  printf("%s",blah);
  printf("im the bleh function\n");
  
}


int main()

{
  int i, j;
    /*comments are done like this*/
    i = 7;
    j = 9;
 
    int answer;
    answer = mean(i,j);
    
  printf("The mean of %d and %d is %d\n", i, j, answer);
    bleh();
  exit(0);
}
