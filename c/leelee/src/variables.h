#ifndef VARIABLES_H
#define VARIABLES_H

#include <inttypes.h>

#define CHAR_VARIABLES 8 /* count of character variables */

#define CVAR_HOST 0
#define CVAR_NICK 1
#define CVAR_USER 2
#define CVAR_REAL 3
#define CVAR_CHANNEL 4
#define CVAR_LOGFILE 5
#define CVAR_NICKSERVPASSWD 6
#define CVAR_CONFIGFILE 7

#define INT16_VARIABLES 9 /* count of int16_t variables */

#define IVAR_PORT 0
#define IVAR_AUTOOP 1
#define IVAR_LOGLEVEL 2
#define IVAR_AUTODEOP 3
#define IVAR_USEOPLIST 4
#define IVAR_USEFUCKLIST 5
#define IVAR_USESERVICES 6
#define IVAR_USESSL 7
#define IVAR_OUTPUTRATE 8

#define CHAR_VARIABLE_SIZE 50
typedef struct char_variable
{
    char *name;
    char var[CHAR_VARIABLE_SIZE];
} bot_char_variable;

typedef struct int16_variable
{
    char *name;
    uint16_t var;
} bot_int16_variable;

extern bot_char_variable bot_char_variables[];
extern bot_int16_variable bot_int16_variables[];

#endif
