#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bot.h"
#include "irc.h"
#include "cmd.h"
#include "log.h"
#include "functions.h"
#include "api.h"
#include "auto_modes.h"
#include "auth.h"
#include "variables.h"
#include "plugin_load.h"

#define MAX_ARGS 16
/* pointer to arguments splittet by spaces */
char *args[MAX_ARGS];
/* variable pointer for  message, destination, answer */
char *msg, *dest, *from, *answer;
/* buffer for answers */
char blah[255];
int opped;

void setup_hooks(void)
{
   log_print(LOG_STATUS, "setting up default events...");
   add_hook("001",  &fct_loggedin); 
   add_hook("PING", &fct_ping);
   add_hook("JOIN", &fct_join);
   add_hook("MODE", &fct_mode);
   add_hook("NICK", &fct_nick);
   add_hook("PRIVMSG", &fct_privmsg);
}

static inline void send_status_msg(char *msg)
{   
   irc_send_privmsg(dest, msg);
}

void fct_login(void)
{
  irc_send_nick(bot_char_variables[CVAR_NICK].var);
  irc_send_user(bot_char_variables[CVAR_USER].var, bot_char_variables[CVAR_REAL].var);
}

/* care for op-/fucklist when someone joines the channel */
void fct_join(struct irc_msg *imptr)
{
  from = strtok(strdup(imptr->prefix), "!");
  
  if(bot_int16_variables[IVAR_USEFUCKLIST].var)
     auto_op(from);
   
  if(bot_int16_variables[IVAR_USEFUCKLIST].var)
     auto_fuck(from);
   
  /* log if the bot has joined a channel */
  if(from != bot_char_variables[CVAR_NICK].var)
      log_print(LOG_INFO, "user %s joined channel %s", from, bot_char_variables[CVAR_CHANNEL].var);
}

/* event called when the bot logged in successfully to irc */
void fct_loggedin(struct irc_msg *imptr)
{
    char blah[50];
   
    if(strlen(bot_char_variables[CVAR_NICKSERVPASSWD].var))
     {
	sprintf(blah, "identify %s", bot_char_variables[CVAR_NICKSERVPASSWD].var);
	irc_send_privmsg("NickServ", blah);
     }
   
   irc_send_join(bot_char_variables[CVAR_CHANNEL].var);
     
   if(bot_int16_variables[IVAR_AUTOOP].var)
     {
	   sprintf(blah, "op %s %s", bot_char_variables[CVAR_CHANNEL].var, bot_char_variables[CVAR_NICK].var);
	   irc_send_privmsg("ChanServ", blah);   
     }
     
}

/* oberve usermodes set by the chanops */
void fct_mode(struct irc_msg *imptr)
{   
   if(bot_int16_variables[IVAR_AUTODEOP].var)
     {	
	if(opped==0) /* if bot didn't op someone */
	  { 
	     
	     if(imptr->argv[1]!=NULL)
	       if(!strcasecmp(imptr->argv[1], bot_char_variables[CVAR_NICK].var)) return;
	     
	     if(is_on_oplist(imptr->argv[1]) != 1 && strstr(imptr->argv[0], "+o"))
	       /* show who's yer daddy :P */
	       irc_send_dop(bot_char_variables[CVAR_CHANNEL].var, imptr->argv[1]);
	  }
	     else
	  {
	     opped = 0;
	  }
	
     }
}

/* prevent ping timeouts */
void fct_ping(struct irc_msg *imptr)
{
  irc_send_pong(imptr->dest);
}

/* private messages */
void fct_privmsg(struct irc_msg *imptr)
{
  char *ptr;
  int i=0;
  
  ptr = strtok(strdup(imptr->argv[0]), " \n");
  if(!ptr) return;
   
  bzero(args, sizeof(args));

  args[0] = (char*) malloc(strlen(ptr)+1);
  strcpy(args[0], ptr);
   
  while(ptr != NULL && i <= MAX_ARGS)
     {
	args[i] = (char*) malloc(strlen(ptr)+1);
	strcpy(args[i], ptr);
	ptr = strtok(NULL, " \n");
	i++;
     }
   
  if(args[0] == NULL) return;
   
  msg = imptr->argv[0];
  from = strtok(strdup(imptr->prefix), "!");

  /* if bot gets a message in query, set destination to his nick, else to channel */ 
  if(imptr->dest[0]=='#')
     dest = imptr->dest;
  else
     dest = from;

  /* commands without args */
   /*if(!strcasecmp(args[0], "!usage") || !strcasecmp(args[0], "!help"))
     {
	usage(from);
     }*/
  if(!strcasecmp(args[0], "!modules"))
     {
	FOR_EACH(plugins)
	  {
	     send_status_msg(plugin_listptr->name);
	  }
	
     }
  else if(!strcasecmp(args[0], "!logout"))
     {
	/* check if user is logged in */
	if(is_owner(from)==0)
	  {
	     send_status_msg("you're not logged in!");
	     return;
	  }
	     
	for(i=0; i<=MAX_OWNER; i++)
	  {
	     if(authorized_users[i] != NULL)
	       {
		  
		  if(!strcasecmp(authorized_users[i], from))
		    {
		       log_print(LOG_INFO, "user %s logged out", authorized_users[i]);
		       irc_send_privmsg(dest, "you are no longer authorized");
		       bzero(authorized_users[i], sizeof(authorized_users[i]));
		       free(authorized_users[i]);
		       owner--;
		       break;
		    }
		  
	       }
	     
	  }
	
     } else
    
  /* end (no args) */
   
  if(!strcasecmp("!vars", args[0]))
      {
	 char buf[CHAR_VARIABLES * sizeof(bot_char_variable) + INT16_VARIABLES * sizeof(bot_int16_variable) + 10];
	 char *bufptr = buf;
	 
         if(args[1] == NULL)
	   {
	      bufptr += sprintf(bufptr, "character variables:\n");
	      
	      for(i=0; i < CHAR_VARIABLES; i++)
	        bufptr += sprintf(bufptr, "  %s: %s\n", strlen(bot_char_variables[i].name) ? bot_char_variables[i].name : "(null)" ,
                                                                                   strlen(bot_char_variables[i].var) ? bot_char_variables[i].var : "(null)") ;
	      bufptr += sprintf(bufptr, " \ninteger variables:\n");
	      for(i=0; i < INT16_VARIABLES; i++)
	        bufptr += sprintf(bufptr, "  %s: %u\n", strlen(bot_int16_variables[i].name) ? bot_int16_variables[i].name : "(null)",
                                                                                    bot_int16_variables[i].var);
	      if(!strlen(buf))
		sprintf(buf, "no variables!");
	            
	      irc_send_privmsg(dest, buf);
	   }
	 else
	   {
	      for(i=0; i < CHAR_VARIABLES; i++)
		{
		   if(!strcasecmp(bot_char_variables[i].name, args[1]))
		     {
			sprintf(buf, "%s: %s (type: character)\n", bot_char_variables[i].name, bot_char_variables[i].var);
			break;
		     }
		}
	      
	      for(i=0; i < INT16_VARIABLES; i++)
		{
		   if(!strcasecmp(bot_int16_variables[i].name, args[1]))
		     {
			sprintf(buf, "%s: %u (type: integer)\n", bot_int16_variables[i].name, bot_int16_variables[i].var);
			break;
		     }
		}
	      
	      if(!strlen(buf))
		sprintf(buf, "no such variable!");
	      
	      irc_send_privmsg(dest, buf);
	   }
	      
      }
   
  /* commands with 1 arg */
  if(args[1] != NULL)
     {

	/* privileged commands */
	if(is_owner(from)==1)
	  {
	     if(!strcasecmp(args[0], "!nick"))
	       { 
		  irc_send_nick(args[1]);
	       }
	     else if(!strcasecmp(args[0], "!join"))
	       irc_send_join(args[1]);
	     else if(!strcasecmp(args[0], "!ban"))
	       {
		  irc_send_ban(bot_char_variables[CVAR_CHANNEL].var, args[1]);
		  sprintf(blah, "banned user %s from %s", args[1], bot_char_variables[CVAR_CHANNEL].var);
		  send_status_msg(blah);
	       }
	     else if(!strcasecmp(args[0], "!unban"))
	       { 
		  irc_send_unban(bot_char_variables[CVAR_CHANNEL].var, args[1]);
		  sprintf(blah, "user %s unbanned from %s", args[1], bot_char_variables[CVAR_CHANNEL].var);
		  send_status_msg(blah);
	       }
	     else if(!strcasecmp(args[0], "!addmodule"))
		  add_plugin(args[1]);
	     else if(!strcasecmp(args[0], "!rmmodule"))
	          remove_plugin(args[1]);
	     /* add to fucklist, all in this list will get /fuck'ed =) */
	     if(!strcasecmp(args[0], "!addfuck"))
	       {
		  int addfuck;
		  addfuck = add_fuck(args[1]);
		  
		  if(addfuck==1)
		    sprintf(blah, "user %s is already contained in auto-fuck list", args[1]);
		  
		  else if(addfuck==0)
		    sprintf(blah, "user %s added to auto-fuck list", args[1]);
		  
		  else if(addfuck==-1)
		    sprintf(blah, "error adding user %s to auto-fuck list", args[1]);
		  
		  send_status_msg(blah);
	       } else
	     
	     /* add to oplist, they'll get auto-oped in future */
	     if(!strcasecmp(args[0], "!addop"))
	       { 
		  int add;
		  add = add_op(args[1]);
		  
		    if (add==1)
		      sprintf(blah, "user %s is already contained in auto-op list!", args[1]);
		  
		  else if (add==0)
		    sprintf(blah, "user %s added to auto-op list", args[1]);
		  
		  else if (add==-1)
		    sprintf(blah, "error adding user %s to auto-op list", args[1]);
		  
		  send_status_msg(blah);
		  
	       } else
	     
	     /* remove entry from fucklist */
	     if(!strcasecmp(args[0], "!rmfuck"))
	       {
		  int fuck;
		  fuck = rm_entry(args[1], BOT_AUTO_FUCK_FILE);
		  
		  if (fuck==1)
		    sprintf(blah, "no such user");
		  
		  else if (fuck==0)
		    sprintf(blah, "user %s removed from auto-fuck list", args[1]);
		  
		  else if (fuck==-1)
		    sprintf(blah, "error removing user %s from auto-fuck list", args[1]);
		  
		  send_status_msg(blah);
		  irc_send_unban(dest, args[1]);
	       } else
	     
	     /* remove entry from auto-op list */
	     if(!strcasecmp(args[0], "!rmop"))
	       {
		  int rmop;
		  rmop = rm_entry(args[1], BOT_AUTO_OP_FILE);
		  
		  if (rmop==1)
		    sprintf(blah, "no such user");
		  
		  else if (rmop==0)
		    sprintf(blah, "user %s removed from auto-op list", args[1]);
		  
		  else if (rmop==-1)
		    sprintf(blah, "error removing user %s from auto-op list", args[1]);
		  
		  send_status_msg(blah);
	       }
	     
	  }
	/* end privileged (1 arg) */
	
/* unprivileged (1 arg) */
	
	/* 1 args unprivileged code... blah blah */  
	
/* end unprivileged (1 arg) */
	
	}
 /* end (1 arg) */


 /* start (2 args) */
   
         /* 2 args code ... blah blah */
   
 /* end (2 args) */
   
        /* commands with opt args */
 
        int login=0;
        if(strcasecmp(args[0], "!auth")==0 || strcasecmp(args[0], "!login")==0 )
	  {

	     /* check if user is already logged in */
	     if(is_owner(args[1]))
	       { 
		  send_status_msg("please log out first!");
		  return;
	     }
	     
	     login = auth(args[1], args[2]);
	     send_status_msg(login == 1 ? "you are now authorized\n" : "wrong user / passwd\n");
	     
	     if(login==1)
	       {
		  
		  if(owner >= MAX_OWNER)
		    {  
		       send_status_msg("there are too many users logged in!");
		       log_print(LOG_INFO, "too many users logged in!", "");
		       return;
		    }
		  
		  for(i=0; i<=MAX_OWNER; i++)
		    {
		       if(authorized_users[i]==NULL)
			 {
			    char blah[50];
			    authorized_users[i] = (char*) malloc(strlen(args[1])+1);
			    strcpy(authorized_users[i],  args[1]);
			    owner++;
			    sprintf(blah, "user %s logged in", from);
			    log_print(LOG_INFO, "owner %s logged in", from);
			    break;
			 }
		            
		    }
		    
	       }
	     
	  }
   
   /* privileged commands (opt args)*/
  if(is_owner(from))
     {
	if(strcasecmp(args[0], "!part")==0)
	  irc_send_part(args[1]!=NULL ? args[1] : bot_char_variables[CVAR_CHANNEL].var);
	else if(strcasecmp(args[0], "!op")==0)
	  { 
	     if(args[1] == NULL)
		  irc_send_op(bot_char_variables[CVAR_CHANNEL].var, from);
	     	  
	     for(i=1; i<=MAX_ARGS; i++)
	       {
		  if(args[i] == NULL) break;
		  irc_send_op(bot_char_variables[CVAR_CHANNEL].var, args[i]);
	       }
	     
	     opped = 1;
          }
	else if(strcasecmp(args[0], "!dop")==0||strcasecmp(args[0], "!deop")==0)
	  {
	     if(args[1] == NULL)
		  irc_send_dop(bot_char_variables[CVAR_CHANNEL].var, from);
		  
	     for(i=1; i<=MAX_ARGS; i++)
	       {
		  if(args[i] == NULL) break;
		  irc_send_dop(bot_char_variables[CVAR_CHANNEL].var, args[i]);
	       }     
	  }
	else if(strcasecmp(args[0], "!kick")==0)
	  { irc_send_kick(bot_char_variables[CVAR_CHANNEL].var, args[1], args[2] == NULL ? REASON : args[2]); }
	else if(strcasecmp(args[0], "!fuck")==0)
	  {
	     irc_send_dop(bot_char_variables[CVAR_CHANNEL].var, args[1]);
	     irc_send_kick(bot_char_variables[CVAR_CHANNEL].var, args[1], args[2] == NULL ? REASON : args[2]);
	     irc_send_ban(bot_char_variables[CVAR_CHANNEL].var, args[1]);
	  }
	  
     }
  /* end privileged (opt args)*/

/* end (opt args) */
}

void fct_nick(struct irc_msg *imptr)
{

   unsigned int i;
   char *newnick;
   
   from = strtok(strdup(imptr->prefix), "!");
   newnick = strtok(strdup(imptr->dest), ":");
      
   if(from==NULL || newnick==NULL)
     return;
   
   for(i=0; i<=MAX_OWNER; i++)
     {            
	if(authorized_users[i]!=NULL)
	if(strcasecmp(authorized_users[i], from)==0)
	  {
	     free(authorized_users[i]);
	     authorized_users[i] = (char*) malloc(strlen(newnick)+1);
	     strncpy(authorized_users[i], newnick, strlen(authorized_users[i])+1);
	  }
	
     }

}
