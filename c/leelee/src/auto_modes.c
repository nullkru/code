#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "auto_modes.h"
#include "api.h"
#include "log.h"
#include "variables.h"

extern char *bot_chan;

static FILE *fp;
static char buf[50];
static char *ptr = buf,
       *name;

static int entry_exists(char *entry, char *file)
{
   assert(entry != NULL && file != NULL);
   
   fp = fopen(file, "r");
   if(!fp)
     {
	log_print(LOG_WARN, "couldn't open %s", file);
	return 0;
     }
   
   setlinebuf(fp);
   
   while(!feof(fp))
     {	
	fgets(&buf[0], 50, fp);
	name = strtok(strdup(ptr), " \n");
	if(!strcasecmp(entry, name))
	  return 1;
     }
   
   fclose(fp);
   return 0;
}

/* event that checks if user should be auto-opped */
void auto_op(char *nick)
{   
   assert(nick != NULL);

   fp = fopen(BOT_AUTO_OP_FILE, "r");
   if(!fp)
     {
	log_print(LOG_WARN, "couldn't open %s", BOT_AUTO_OP_FILE);
	return;
     }
   
   setlinebuf(fp);   
   while(!feof(fp))
     {
	fgets(&buf[0], sizeof(buf), fp);
	name = strtok(strdup(ptr), " \n");
	if(name)
	  {
	     if(strcasecmp(nick, name)==0)
	       irc_send_op(bot_char_variables[CVAR_CHANNEL].var, nick);
	  }
     }   
   fclose(fp);
}

/* check if user is on oplist */
int is_on_oplist(char *nick)
{
   assert(nick != NULL);
   
   if(entry_exists(nick, BOT_AUTO_OP_FILE))
     return 1;
   else
     return 0;
}

/* check if user is on fucklist */
int is_on_fucklist(char *nick)
{
   assert(nick != NULL);
   
   if(entry_exists(nick, BOT_AUTO_FUCK_FILE))
     return 1;
   else
     return 0;  
}

/* add nick to oplist (if he isn't already there) */
int add_op(char *nick)
{
   assert(nick != NULL);

   if(is_on_oplist(nick))
     return 1;
   
   fp = fopen(BOT_AUTO_OP_FILE, "a");
   if(!fp)
     {
	log_print(LOG_WARN, "coudln't open %s", BOT_AUTO_OP_FILE);
	return -1;
     }
   fprintf(fp, "%s\n", nick);
   fflush(fp);
   fclose(fp);
   return 0;
}

/* event that checks if user should be auto-fucked */
void auto_fuck(char *nick)
{
   assert(nick != NULL);
   
   fp = fopen(BOT_AUTO_FUCK_FILE, "r");
   if(!fp)
     {
	log_print(LOG_WARN, "coudln't open %s", BOT_AUTO_OP_FILE);
	return;
     }
   
   setlinebuf(fp);
   while(!feof(fp))
     {
	fgets(&buf[0], 50, fp);
	name = strtok(strdup(ptr), " \n");
	if(strcasecmp(nick, name)==0)
	  {  
	     irc_send_dop(bot_char_variables[CVAR_CHANNEL].var, nick);
	     irc_send_kick(bot_char_variables[CVAR_CHANNEL].var, nick, REASON);
	     irc_send_ban(bot_char_variables[CVAR_CHANNEL].var, nick);
	  }
     }
   fclose(fp);
}

/* adds a nick to fucklist */
int add_fuck(char *nick)
{
   assert(nick != NULL);
   
   fp = fopen(BOT_AUTO_FUCK_FILE, "a");
   if(!fp)
     {
	log_print(LOG_WARN, "coudln't open %s", BOT_AUTO_FUCK_FILE);
	return -1;
     }
   
   fprintf(fp, "%s\n", nick);
   fflush(fp);
   fclose(fp);
   return 1;
}

/* remove a name from file */
int rm_entry(char *nick, char *file)
{
   char *lines[512];
   unsigned int i=0,j;
   
   assert(nick != NULL && file != NULL);
   
   if(entry_exists(nick, file))
     {
	
	fp = fopen(file, "r");
	if(!fp)
	  {
	     log_print(LOG_WARN, "coudln't open %s", file);
	     return -1;
	  }
	
	setlinebuf(fp);
	
	while(!feof(fp))
	  {
	     fgets(&buf[0], 50, fp);
	     name = strtok(strdup(ptr), " \n");
	     if(strcasecmp(nick, name)!=0)
	       {
		  if(name)
		    {
		       lines[i] = (char*) malloc(strlen(name));
		       strcpy(lines[i], name);
		       i++;
		    }
	       }
	  }
   
	fclose(fp);
	
	fp = fopen(file, "w");
	if(!fp) return -1;
   
	for(j=0; j<i; j++)
	  {
	     if(lines[j])
	       {
		  fprintf(fp, "%s\n", lines[j]);
		  fflush(fp);
	       }
	     
	     free(lines[j]);
     
	  }
	
	fclose(fp);
	return 0;
     }
   else
     return 1;
}
