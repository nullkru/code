#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "irc.h"
#include "cmd.h"

extern void setup_hooks  (void);
extern void fct_login    (void);
extern void fct_ping     (struct irc_msg *imptr);
extern void fct_privmsg  (struct irc_msg *imptr);
extern void fct_loggedin (struct irc_msg *m);
extern void fct_mode     (struct irc_msg *imptr);
extern void fct_join     (struct irc_msg *imptr);
extern void fct_nick     (struct irc_msg *imptr);

extern int opped; /* if last action was op someone , 1 */
extern char *msg, *dest, *from, *answer;


#endif
