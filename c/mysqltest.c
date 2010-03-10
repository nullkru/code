#include <stdio.h>
#include <mysql.h>
#include <stdlib.h>
#include <string.h>
int main()
{

MYSQL *my;
my = mysql_init(NULL);
if (my == NULL)
{
	   fprintf(stderr, "Initialisierung fehlgeschlagen\n");
	   exit (EXIT_FAILURE);
}
if ( mysql_real_connect (
			my,
			localhost,
			root,
			blahbleh,
			hashtable,
			0,
			NULL,
			0 ) == NULL )

void mysql_close(MYSQL *mysql);
}
