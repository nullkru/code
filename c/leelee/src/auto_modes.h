#ifndef AUTO_MODES_H
#define AUTO_MODES_H

#define BOT_AUTO_OP_FILE "bot.oplist"
#define BOT_AUTO_FUCK_FILE "bot.fucklist"

#define REASON "wtf?"

extern void auto_op(char *nick);
extern void auto_fuck(char *nick);
extern int is_on_oplist(char *nick);
extern int is_on_fucklist(char *nick);
extern int add_fuck(char *nick);
extern int add_op(char *nick);
extern int rm_entry(char *nick, char *file);

#endif
