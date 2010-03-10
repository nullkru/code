/* zeiger zeugs */

/* blah zeiger */

int *blahzgr;

int blah()
{
  printf("blah blah blah");
}


int main()
{
  
 blahzgr = &blah; 
 printf("\n indirekte ausgabe von blah = %s", *blahzgr);
}
