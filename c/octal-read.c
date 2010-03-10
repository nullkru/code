#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main()
{
  char size_str[64];
  size_t size;
  char buf;

  if(fgets(size_str, sizeof(size_str), stdin) == NULL)
    return 1;

  if((size = strtoul(size_str, NULL, 10)) == 0 || size == ULONG_MAX)
    return 1;

  setvbuf(stdin, &buf, _IONBF, 1);

  while(size--)
  {
    int c = fgetc(stdin);
  
    printf("%03o\n", (unsigned char)c);
  }

  return 0;
}
