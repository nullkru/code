#ifndef CMD_H
#define CMD_H

typedef void (cmd_callback)(struct irc_msg *);

void cmd_call(struct irc_msg *imptr);
void add_hook(char *cmd, cmd_callback* func);

#endif
