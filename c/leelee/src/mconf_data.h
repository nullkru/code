#ifndef MCONF_DATA_H
#define MCONF_DATA_H

#include <inttypes.h>

#include "variables.h"
#include "mconf.h"
#include "bot.h"

/* change the count! */
#define MCONF_LISTCOUNT   17
#define MCONF_ALIASCOUNT  3


int mconf_conf_help(struct mconf_item *, char *);

extern int log_conf_level(struct mconf_item *, char *);

extern char     *mconf_filename;
extern int       log_level;

static struct mconf_item mconf_list[] = {
  /* index 0 */
  { 'c', "configfile",
      MCONF_LINE | MCONF_INPUT,
      NULL,
      &bot_char_variables[CVAR_CONFIGFILE].var, MCONF_CHARARRAY,
      "filename", "use \"filename\" instead of the default config file"  },
  /* index 1 */
  { 'H', "help",
      MCONF_LINE | MCONF_INPUT,
      mconf_conf_help,
      NULL, MCONF_NOTYPE,
      "", "print this help page" },
  /* index 2 */
  { 's', "host",
      MCONF_LINE | MCONF_FILE,
      NULL,
      &bot_char_variables[CVAR_HOST].var, MCONF_CHARARRAY,
      "host", "irc server" },
  /* index 3 */
  { 'p', "port",
      MCONF_LINE | MCONF_FILE,
      NULL,
      &bot_int16_variables[IVAR_PORT].var, MCONF_UINT16,
      "port", "irc server port" },
  /* index 4 */
  { 'n', "nick",
      MCONF_LINE | MCONF_FILE | MCONF_INPUT,
      NULL,
      &bot_char_variables[CVAR_NICK].var, MCONF_CHARARRAY,
      "nickname", "nickname" },
  /* index 5 */
  { 'C', "channel",
      MCONF_LINE | MCONF_FILE | MCONF_INPUT,
      NULL,
      &bot_char_variables[CVAR_CHANNEL].var, MCONF_CHARARRAY,
      "channame", "channel" },
  /* index 6 */
  { 'o', "logfile",
      MCONF_LINE | MCONF_FILE,
      NULL,
      &bot_char_variables[CVAR_LOGFILE].var, MCONF_CHARARRAY,
      "path", "logfile" },
  /* index 7 */
  { 'l', "loglevel",
      MCONF_LINE | MCONF_FILE | MCONF_INPUT,
      &log_conf_level,
      &bot_int16_variables[IVAR_LOGLEVEL].var, MCONF_UINT16,
      "level", "use a number from 0 to 5 or one of LOG_FATAL, LOG_STATUS, "
      "LOG_WARN, LOG_INFO, LOG_DEBUG1 or LOG_DEBUG2"  },
  /* index 8 */
  { 'u', "user",
      MCONF_LINE | MCONF_FILE,
      NULL,
      &bot_char_variables[CVAR_USER].var, MCONF_CHARARRAY,
      "name", "username" },
  /* index 9 */
  { 'r', "real",
      MCONF_LINE | MCONF_FILE,
      NULL,
      &bot_char_variables[CVAR_REAL].var, MCONF_CHARARRAY,
      "name", "realname" },
  /* index 10 */
  { 'N', "nickservpasswd",
      MCONF_LINE | MCONF_FILE,
      NULL,
      &bot_char_variables[CVAR_NICKSERVPASSWD].var, MCONF_CHARARRAY,
      "password", "nickservpasswd" },
  /* index 11 */
   {
     'a', "autoop",
      MCONF_LINE | MCONF_FILE,
      NULL,
      &bot_int16_variables[IVAR_AUTOOP].var, MCONF_UINT16,
      "autoop", "if auto-op is enabled the bot will op itself using services"
   },
  /* index 12 */
   {
      'u', "usefucklist",
       MCONF_LINE | MCONF_FILE,
       NULL,
       &bot_int16_variables[IVAR_USEFUCKLIST].var, MCONF_UINT16,
       "usefucklist", "if usefucklist is enabled the bot will deop / kick / ban all people on bot.fucklist"	
   },
  /* index 13 */
   {
      'S', "useservices",
       MCONF_LINE | MCONF_FILE,
       NULL,
       &bot_int16_variables[IVAR_USESERVICES].var, MCONF_UINT16,
       "useservices", "if useservices is enabled the bot will do its actions through services (chanserv etc)"
   },
  /* index 14 */
   {
      'O', "useoplist",
      MCONF_LINE | MCONF_FILE,
      NULL,
      &bot_int16_variables[IVAR_USEOPLIST].var, MCONF_UINT16,
      "useoplist", "if useoplist is enabled the bot will use people from bot.oplist as channel operators"
   },
  /* index 15 */
   {
      'l', "usessl",
      MCONF_LINE | MCONF_FILE,
      NULL,
      &bot_int16_variables[IVAR_USESSL].var, MCONF_UINT16,
      "usessl", "enable this if you want to use ircs"
   },
  /* index 16 */
   {
      'R', "outputrate",
      MCONF_LINE | MCONF_FILE,
      NULL,
      &bot_int16_variables[IVAR_OUTPUTRATE].var, MCONF_UINT16,
      "outputrate", "enable this if you want to limit msgs / sec (avoids the bot getting kicked because of flooding)"
   }
   
};

static struct mconf_alias mconf_aliaslist[] = {
  { 'h', &mconf_list[1], "all" },
  { 'v', &mconf_list[7], "Info" },
  { 'd', &mconf_list[7], "Debug1" },
};



#endif /* #ifndef MCONF_DATA_H */
