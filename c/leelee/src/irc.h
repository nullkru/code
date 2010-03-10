#ifndef IRC_H
#define IRC_H

#define IRC_MAXARGS 16

struct irc_name {
  char *nick;
  char *user;
  char *host;
};

struct irc_msg {
  char *prefix;
  char *nick;
  char *user;
  char *host;
  char *cmd;
  char *dest;
  int   argc;
  char *argv[IRC_MAXARGS];
};

extern void irc_print(struct irc_msg *m);
extern void irc_parse_packet(char *buffer);
extern void irc_send(char *cmd, char *dest, char *fmt, ...);

#define IRC_CMD_PRIVMSG    "PRIVMSG"
#define IRC_CMD_JOIN       "JOIN"
#define IRC_CMD_NICKINUSE  "443"

#endif /* #ifndef IRC_H */
