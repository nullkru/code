%{
/* turning the '.section data' into .text section,
 * so all strings are in code. Necessary for shellcodes.
 */
#include <stdio.h>

int datafound = 0;
%}

%%

\.section[^\n]+data	{ 
			  printf(".text\n.align 4\n");
			  printf("main: jmp .L666\n");
			  datafound++;
                        }
\.text		        {
			   /* We need a stackpointer below the shellcode, coz
			    * gcc may generate stackframes in our shellcode
			    */
			   printf(".L666: subl $11111, %cesp\n\n", '%');
		          
		        }
main\:		        {
			  /* we already have a main, so skip the label
			   */
			  if (!datafound)
				printf("%s", yytext);
		        }
[ \t]	ECHO;
\n	ECHO;
.	ECHO;

%%

int main(int argc, char **argv)
{
	return yylex();
}
