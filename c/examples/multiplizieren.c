/* berechnet das produkt zweier zahlen. */
#include <stdio.h>

int a,b,c;

int produkt(int x, int y);

int main()

{
  /* erste zahl einlese */
  printf("Geben Sie eine Zahl zwischen 1 und 100 ein: ");
  scanf("%d", &a);
  
  /* zweite uahl einlesse */
  printf("Geben Sie eine Zahl zwischen 1 und 100 ein: ");
  scanf("%d", &b);
  
  /* produkt berechnen und anzeigen */
  c = produkt(a, b);
  
  printf("%d mal %d = %d\n", a, b, c);
  
  return 0;
}

/* funtion gibt produkt der beiden bereitgestellten werte zurück */
int produkt(int x, int y)

{
  return (x * y);
}
