#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"
#include "auth.h"

char *authorized_users[MAX_OWNER];
unsigned int owner;

static void mdprint(unsigned char digest[16], char *result)
{

   unsigned int i, j=0;
   int val;
   
   for(i=0; i<16; i++)
     {
	val = digest[i];
	sprintf(&result[j], "%02x", (unsigned char) val);
	j += 2;
     }

}

int auth(char *user, char *passwd)
{
    
   FILE *fp;
   char *username, *passwdhash;
   char buf[100];
   char *ptr = buf;
   
   MD5_CTX md5;
   char md5digest[16];
   char md5sum[32];
   
   if(passwd==NULL) return 0;
   
   fp = fopen(OWNER_FILE, "r");
   if(!fp) return 0;
       
   MD5Init(&md5);
   MD5Update(&md5 , passwd, strlen(passwd));
   MD5Final(md5digest, &md5);
   
   mdprint(md5digest, &md5sum[0]);

   setlinebuf(fp);
   
   while(!feof(fp))
     {
	if(fgets(ptr, sizeof(buf), fp)==NULL) return-1;
	
	username = strtok(strdup(ptr), "|");
	passwdhash = strtok(NULL, " \n");
		
        if(username != NULL && passwdhash != NULL)
	  if(strcmp(passwdhash, md5sum)==0 && strcasecmp(username, user)==0)
	    {
	       fclose(fp);
	       return 1;
	    }
     }
   
   fclose(fp);
   return 0;
   
}

int is_owner(char *nick)
{
   unsigned int i;
   
   if(nick==NULL) return 0;
   
   for(i=0; i<=MAX_OWNER; i++)
     {
	if(authorized_users[i] != NULL)
	  {
	     if(strcasecmp(authorized_users[i], nick)==0)
	       return 1;
	  }
     }
   
   return 0;
}
