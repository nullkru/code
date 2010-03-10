#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdarg.h>

#include "../../api.h"
#include "../../irc.h"
#include "../../log.h"
#include "../../variables.h"

#include "seen.h"

static FILE *fseen = NULL;
static char *destination, *sender, *message;

static void tell_seen(char *nickname)
{
   char linebuf[512], answer[512], *blah=NULL, *ptr;
   char laction;
   char *lnick, *ltimestamp, *llastmsg;
   struct seen_entry *user;
   int seen=0;
      
   if(sender==NULL||destination==NULL)
      return;
      
   if(!(fseen = fopen(SEEN_FILE, "r")))
      return;
      
   setlinebuf(fseen);
   user = (struct seen_entry*) malloc(sizeof(struct seen_entry));
      
   while(!feof(fseen))
   {
       ptr = linebuf;
       fgets(ptr, sizeof(linebuf), fseen);
       blah = (char*)strdup(ptr);
 
       laction = *(char*)strtok(blah, DELIM);
       lnick = strtok(NULL, DELIM);
       ltimestamp = strtok(NULL, DELIM);
       llastmsg = strtok(NULL, DELIM"\n");
	
      if(!strcasecmp(nickname, lnick))
       {
	 user->action = laction;
	 strncpy(user->nick,  lnick, sizeof(user->nick));
	 strncpy(user->timestamp, ltimestamp, sizeof(user->timestamp));
	 strncpy(user->lastmsg, llastmsg, sizeof(user->lastmsg));
         seen = 1;
       }	
   }
   
   fclose(fseen);
   if(seen)
     {
	if(user->action == ACTION_JOIN)
	  sprintf(answer, "user %s was last seen joining %s at %s.", user->nick, user->lastmsg, user->timestamp);
	else if(user->action == ACTION_PRIVMSG)
	   sprintf(answer, "user %s was last seen on %s at %s saying '%s'.", user->nick, bot_char_variables[CVAR_CHANNEL].var, user->timestamp, user->lastmsg);
     }
   else
      sprintf(answer, "never seen user %s", nickname);
        
   irc_send_privmsg(destination, answer);
   free(user);
}

static void notice_user(char action, char *nickname, char *data)
{
   static char timebuf[40];
   struct seen_entry *user;
   struct tm *tm;
   size_t len;
   time_t now;   
   char logstr[512], *ptr;
   ptr = logstr;
      
   now = time(NULL);   
   tm = (struct tm*) localtime (&now);
   len = strftime (timebuf, sizeof(timebuf), "%d %B %Y %I:%M:%S %p", tm);
   
   user = (struct seen_entry*) malloc(sizeof(struct seen_entry));
   
   user->action = action;
   strncpy(user->nick, nickname, sizeof(user->nick));
   strncpy(user->timestamp, timebuf, sizeof(user->timestamp));
   strncpy(user->lastmsg, data, sizeof(user->lastmsg));
   
   sprintf(logstr, "%c|%s|%s|%s\n",
           action, user->nick, user->timestamp,  user->lastmsg);
   fseen = fopen(SEEN_FILE, "a");
   if(fseen) fputs(ptr, fseen);
   fclose(fseen);
   
   free(user);
}

/* to offer check if this is our plugin */
int plugin_check(void)
{
   return PLUGIN_VERIFICATION;
}

void privmsg_callback(struct irc_msg *imptr)
{
   /* privmsg parsing code */
   char *args[10];
   char *ptr;
   int i=0;
   
   ptr = strtok(strdup(imptr->argv[0]), " \n");
   if(!ptr) return;   
   bzero(args, sizeof(args));
   
   args[0] = (char*) malloc(strlen(ptr)+1);
   strcpy(args[0], ptr);
   while(ptr != NULL && i <= 10)
     {
        args[i] = (char*) malloc(strlen(ptr)+1);
        strcpy(args[i], ptr);
        ptr = strtok(NULL, " \n");
        i++;
     }
   if(args[0] == NULL) return;
   message = imptr->argv[0];
   sender = strtok(strdup(imptr->prefix), "!");
   
   /* if bot gets a message in query, set destination to his nick, else to channel */
   if(imptr->dest[0]=='#')
      destination = imptr->dest;
   else
      destination = sender; 
   /* end of privmsg parsing */   
   log_print(LOG_INFO, "privmsg event catched");
   if(!strcasecmp(args[0], "!seen"))
       tell_seen(args[1]); 
   else if(imptr->dest[0]=='#')
       notice_user(ACTION_PRIVMSG, sender, message);
}

void join_callback(struct irc_msg *imptr)
{
   char *from = strtok(strdup(imptr->prefix), "!");
   log_print(LOG_INFO, "join event catched");
   notice_user(ACTION_JOIN, from, imptr->dest+1);
}

void plugin_init(void)
{
   /* initialization */
   add_hook(IRC_CMD_PRIVMSG, &privmsg_callback);
   add_hook(IRC_CMD_JOIN, &join_callback);
   return;
}


void plugin_fini(void)
{
   /* cleanup */
   remove_hook(IRC_CMD_PRIVMSG);
   remove_hook(IRC_CMD_JOIN);
   return;
}
