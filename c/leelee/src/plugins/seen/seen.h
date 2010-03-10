#ifndef SEEN_H
#define SEEN_H

#define SEEN_FILE "bot.seen"
#define DELIM "|"

#define ACTION_JOIN    '0'
#define ACTION_PRIVMSG '1'

struct seen_entry
{
   char action;
   char nick[100];
   char timestamp[40];
   time_t t_timestamp;
   char lastmsg[1024];
};

static void notice_user(char action, char *nickname, char *data);
static void tell_seen(char *nick);

#endif
