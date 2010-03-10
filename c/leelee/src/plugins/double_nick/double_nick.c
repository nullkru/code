#include <stdio.h>

#include "../../api.h"
#include "../../irc.h"
#include "../../log.h"

/* to offer check if this is our plugin */
int plugin_check(void)
{
   return PLUGIN_VERIFICATION;
}

void double_nick_callback(struct irc_msg *imptr)
{
 int len = strlen(imptr->argv[0]);
   char buffer[len + 2];

   memcpy(buffer, imptr->argv[0], len);
   
   buffer[len++] = '_';
   buffer[len]   = '\0';
   
   irc_send_nick(buffer);
   
   log_print(LOG_INFO, "changed nick to %s", buffer);
}

void plugin_init(void)
{
   /* initialization */
   add_hook(IRC_CMD_NICKINUSE, &double_nick_callback);
   return;
}


void plugin_fini(void)
{
   /* cleanup */
   remove_hook(IRC_CMD_NICKINUSE);
   return;
}
