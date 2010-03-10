#ifndef IRC_FUNCS_H
#define IRC_FUNCS_H

#define PLUGIN_VERIFICATION 1337

extern void irc_send_join(char *channel);
extern void irc_send_part(char *channel);
extern void irc_send_nick(char *nickname);
extern void irc_send_user(char *user, char *real);
extern void irc_send_pong(char *string);
extern void irc_send_privmsg(char *dest, char *msg);
extern void irc_send_action(char *dest, char *msg);
extern void irc_send_op(char *chan, char *user);
extern void irc_send_dop(char *chan, char *user);
extern void irc_send_kick(char *chan, char *nick, char *reason);
extern void irc_send_ban(char *chan, char *user);
extern void irc_send_unban(char *chan, char *user);

#endif
