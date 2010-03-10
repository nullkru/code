#ifndef AUTH_H
#define AUTH_H

#define MAX_OWNER 20
#define OWNER_FILE "bot.owner"

extern char *authorized_users[MAX_OWNER];
extern unsigned int owner;

int auth(char *user, char *passwd);
int is_owner(char *nick);

#endif
