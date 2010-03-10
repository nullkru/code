#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "irc.h"
#include "cmd.h"
#include "functions.h"
#include "log.h"


static struct hooklist
{
   char *command;
   cmd_callback *callback;
   struct hooklist *last, *next;
} hook_list = { NULL, NULL, NULL };

#define FOR_EACH_HOOK for(hptr = &hook_list; hptr->next != NULL; hptr = hptr->next)

static struct hooklist *hptr;

static struct hooklist *gethookbycmd(char *cmd)
{
   FOR_EACH_HOOK
     {
	if(!strcasecmp(hptr->command, cmd))
	   return hptr;
     }
   return NULL;
}

static int hook_exists(char *cmd, cmd_callback *func)
{
   hptr = gethookbycmd(cmd);
   if(!hptr)
     return 0;
   else if(hptr->callback == func)
     return 1;
   else
     return 0;
}

void cmd_call(struct irc_msg *imptr)
{
    FOR_EACH_HOOK
      {
         if(!strcasecmp(hptr->command, imptr->cmd))
	   (hptr->callback)(imptr);
      }
}

void remove_hook(char *cmd)
{
   hptr = gethookbycmd(cmd);
   if(!hptr)
     {
	log_print(LOG_WARN, "no such hook");
	return;
     }
   
   if(hptr->last != NULL)
     {
	
        /* wenn aktuelles element naechstes element hat, next vom letzten element darauf setzen, sonst NULL */
	hptr->last->next = (hptr->next != NULL ? hptr->next : NULL);
	/* wenn aktuelles element naechstes element hat, last pointer vom naechsten auf last pointer vom aktuellen setzen*/
	if(hptr->next != NULL)
	hptr->next->last = hptr->last;
	free(hptr->command);
	hptr->command = NULL;
     }
   else
     {
	/* erstes element */
	if(hptr->next != NULL)
	  hptr->next->last = hptr->last;
	free(hptr->command);
	hptr->command = NULL;
     }   
   
   hptr->callback = NULL;
   log_print(LOG_INFO, "removed hook %s", cmd);
}

static struct hooklist *getlastitem(void)
{
   FOR_EACH_HOOK
     {}
   
   return hptr;
}

void add_hook(char *cmd, cmd_callback* func)
{
   struct hooklist *newitem;
   if(hook_exists(cmd, func))
      {
          log_print(LOG_WARN, "hook already exists\n");
	  return;
      }

	/*
	FOR_EACH_HOOK
	  {
	     if(!strcasecmp(hptr->command, cmd))
	       {
	          //add another hook to the existing entry
		  return;
	       }
	  }
         */
   getlastitem();
   log_print(LOG_INFO, "hooked command %s", cmd);
   hptr->command = (char*) malloc(strlen(cmd)+1);
   strcpy(hptr->command, cmd);
   hptr->callback = func;
   newitem = (struct hooklist*) malloc(sizeof(struct hooklist));
   newitem->last = hptr;
   newitem->next = NULL;
   hptr = (hptr->next = newitem);  
}
