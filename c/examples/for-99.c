#include <stdio.h>

int main()
{
  int wert[10];
  int ctr, nbr=0;
  for (ctr = 0; ctr < 10 && nbr != 99; ctr++)

  {
    puts("Geben Sie eine Zahl ein oder verlassen sie mit 99");
    scanf("%d", &nbr);
    wert[ctr] = nbr;
  }
}
