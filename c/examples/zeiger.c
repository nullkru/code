/* einfaches zeiger beispiel */

#include <stdio.h>

/* Deklariert und initialisiert eine int-Variable */

int var = 1;

/* deklariert einen zeiger auf int */

int *zgr;

int main(void)
{
  /*initialieriert zgr als zeiger auf ver */
  
  zgr = &var;
  
  /* direkter und indirekter zugriff auf var */
  
  printf("\n Direkter Zugriff, var = %d", var);
  printf("\n Indirekter Zugriff, var = %d", *zgr);
  
  /* Zwei möglichkeiten, um die adresse von var anzuzegen */
  
  printf("\n\nDie Adresse von var = %lu", (unsigned long)&var);
  printf("\nDie Adresse von var = %lu\n", (unsigned long)zgr);
  
  return 0;
}
