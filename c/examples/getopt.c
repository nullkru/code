#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
  int option;
  
  while ((option = getopt (argc, argv, "abi:o:z")) != EOF)
  {
    switch (option)
    {
      case 'a':
      case 'b':
      case 'z':
           printf("Option : %c\n", option);
           break;
      
      case 'i':
           printf("Eingabe : %s\n", optarg);
           break;
      
      case 'o':
           printf("Ausgabe : %s\n", optarg);
           break;
      
      default:
           usage();
    }
  }
  
  for ( ; optind < argc ; optind++)
    printf ("Opt %2d : %s\n", optind, argv[optind]);
  
  return 0;
}
