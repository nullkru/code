/* besipiel für gängige escape sequenzen */

#include <stdio.h>

#define VERLASSEN 3

int menue_option_einlesen( void );
void bericht_anzeigen ( void );

int main(void)
{
  int option = 0;
  
  while (option != VERLASSEN)
  {
    option = menue_option_einlesen();
    
    if (option == 1)
      printf("\n Akustisches Signal des Computers\a\a\a");
    else
    {
      if (option == 2)
        bericht_anzeigen();
    }
  }
  printf("Sie haben die Option Verlassen gewählt! \n");
  
  return 0;
  
}

int menue_option_einlesen( void )
{
  int auswahl = 0;
  
  do
  {
    printf( "\n" );
    printf("\n[1] - Akustisches Signal des Computers");
    printf("\n[2] - Bericht anzeigen");
    printf("\n[3] - Verlassen");
    printf("\n");
    printf("Geben Sie ihre wahl ein:\t");
    
    scanf("%d", &auswahl);
    
  }
  while( auswahl < 1 || auswahl > 3);
  
  return auswahl;
}

void bericht_anzeigen(void)
{
  printf("\nMUSTERBERICHT                    ");
  printf("\n\n Sequenz\tBedeutung");
  printf("\n=========\t==========");
  printf("\n\\a\t\tBeep (Akustisches Signal)");
  printf("\n\\b\t\tBackspace");
  printf("\n...\t\t...");
}
