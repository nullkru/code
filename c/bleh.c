#include <stdio.h>
#include <getopt.h>
int usage()
{
  printf("Usage:");
  printf("\t -e echo something\n");
  return 0;
}


int main(int argc, char *argv[])
{
  
  int option;
  
  while ((option = getopt (argc, argv, "he:")) != EOF)
  {
    switch(option)
    {
      case 'e':
           printf("echo \"%s\"\n", optarg);
           break;
      case 'h':
           usage();
           break;
      default:
           usage();
      
    }
  }
  
  return 0;
}

