#ifndef VARIABLES_DATA_H
#define VARIABLES_DATA_H

#include "log.h"
#include "variables.h"

bot_char_variable bot_char_variables[] = {
     /* index 0 */
     { "host", "paranoya.homelinux.org" },
     /* index 1 */
     { "nick", "leelee" },
     /* index 2 */
     { "user", "leelee" },
     /* index 3 */
     { "real", "leelee" },
     /* index 4 */
     { "channel", "#blah" },
     /* index 5 */
     { "logfile", "bot.log" },
     /* index 6 */
     { "nickservpasswd", "" },
     /* index 7 */
     { "configfile", "bot.conf" }
};

bot_int16_variable bot_int16_variables[] = {
     /* index 0 */
     { "port", 6667 },
     /* index 1 */
     { "autoop", 0 },
     /* index 2 */
     { "loglevel", LOG_WARN },
     /* index 3 */
     { "autodeop", 0 },
     /* index 4 */
     { "useoplist", 0 },
     /* index 5 */
     { "usefucklist", 0 },
     /* index 6 */
     { "useservices", 0 },
     /* index 7 */
     { "usessl", 0 },
     /* index 8 */
     { "outputrate", 0 }
};

#endif
