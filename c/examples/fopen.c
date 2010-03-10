#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;
  char ch, dateiname[40], modus[5];
  
  while (1)
  {
    
    /*eingabe des dateinamens und des modus. */
    
    printf("\nGeben Sie einen Dateinamen ein: ");
    fgets(dateiname,40,stdin);
    dateiname [strlen(dateiname)-1] = 0;
    printf("\nGeben Sie einen Modus ein (max. 3 Zeichen): ");
    fgets(modus,5,stdin);
    modus [strlen(modus)-1] = 0;
           
           /* Versucht die Datei zu öffnen */
           
           if ((fp = fopen( dateiname,modus)) != NULL)
           {
             printf("\n%s im MOdus %s erfolgreich geöffnet.\n", dateiname, modus);
             fclose(fp);
             puts("x für Ende, Weiter mit Eingabetaste.");
             if ((ch = getc(stdin)) == 'x')
               break;
             else
               continue;
           }
           
           else

           {
             fprintf(stderr, "\nFehler beim Oeffnen von %s im Modus %s. \n", dateiname, modus);
             perror("list1501");
           if((ch = getc(stdin)) == 'x')
              break;
              
           else
              continue;
            
           }
           }
  return 0;
}


  
