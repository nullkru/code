#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "bot.h"
#include "client.h"
#include "irc.h"
#include "variables.h"

static char cmdbuf[512];

void irc_send_join(char *channel)
{
   irc_send("JOIN", channel, "");
}

void irc_send_part(char *channel)
{
   irc_send("PART", channel, "");
}

void irc_send_nick(char *nickname)
{
   irc_send("NICK", nickname, "");
}

void irc_send_user(char *user, char *real)
{
   irc_send("USER", "", "%s x x %s", user, real);
}

void irc_send_pong(char *string)
{
  irc_send("PONG", "", string);
}

void irc_send_privmsg(char *dest, char *msg)
{
   int outputrate = 0;
   
   char *tok = (char*)strtok(strdup(msg), "\n");
   if(!tok)
     return;
   
   do
     {
	if(bot_int16_variables[IVAR_OUTPUTRATE].var != 0)
	if(outputrate > bot_int16_variables[IVAR_OUTPUTRATE].var)
	  {
	     outputrate = 0;
	     usleep(200);
	  }
	irc_send("PRIVMSG", dest, ":%s", tok);
	outputrate++;
     }
   while((tok = (char*)strtok(NULL, "\n")) != NULL);
   /*  irc_send("PRIVMSG", dest, ":%s", tok); */
}

void irc_send_action(char *dest, char *msg)
{
   irc_send("PRIVMSG %s :ACTION %s", dest, msg);
}

void irc_send_op(char *chan, char *user)
{
  if(bot_int16_variables[IVAR_USESERVICES].var)
     {
        sprintf(cmdbuf, "op %s %s", chan, user);
        irc_send_privmsg("ChanServ", cmdbuf);
     }
  else
     irc_send("MODE", chan, "+o %s", user);
}

void irc_send_dop(char *chan, char *user)
{
   if(bot_int16_variables[IVAR_USESERVICES].var)
     {
	sprintf(cmdbuf, "deop %s %s", chan, user);
	irc_send_privmsg("ChanServ", cmdbuf);
     }
   else
     irc_send("MODE", chan, "-o %s", user);
}

void irc_send_ban(char *chan, char *user, char *reason)
{   
   if(bot_int16_variables[IVAR_USESERVICES].var)
     {
	sprintf(cmdbuf, "ban %s %s", chan, user);
	irc_send_privmsg("Chanserv", cmdbuf);
     }
   else
     irc_send("MODE", chan, "+b %s :%s", user, reason);
}

void irc_send_unban(char *chan, char *user)
{ 
   irc_send("MODE", chan, "-b %s", user);
}

void irc_send_kick(char *chan, char *user, char *reason)
{
   if(bot_int16_variables[IVAR_USESERVICES].var)
     {
	sprintf(cmdbuf, "kick %s %s", chan, user);
	irc_send_privmsg("ChanServ", cmdbuf);
     }
   else
     irc_send("KICK", chan, "%s :%s", user, reason);
}
