#include <stdio.h>

int radius, flaeche;

int main(void)
{
	printf( " Geben Sie ein Radius ein (z.B.10): ");
	scanf( "%d", &radius );
	flaeche = (int) (3.14159 * radius * radius );
	printf( "\n\nFläche = %d\n", flaeche );
	return 0;
}

