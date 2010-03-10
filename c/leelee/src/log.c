#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#include "bot.h"
#include "log.h"
#include "mconf.h"
#include "variables.h"

#define LOG_BUFSIZE 512


extern int errno;

int   log_filelevel = LOG_DEBUG2;
char *log_logfile   = "log_logfile";
int   log_fdfile    = -1;

char *log_name[] = {
  "Fatal",
  "Status",
  "Warn",
  "Info",
  "Debug1",
  "Debug2"
};

char *log_prefix[] = {
  "!!!",
  "***",
  " ! ",
  " * ",
  "DDD",
  " D "
};

int log_fds[] = {
  STDERR_FILENO,
  STDOUT_FILENO,
  STDERR_FILENO,
  STDOUT_FILENO,
  STDOUT_FILENO,
  STDOUT_FILENO,
};

static int log_write(int fd, char *buffer, size_t buflen)
{
   FILE *logfile;
 
   logfile = fopen(bot_char_variables[CVAR_LOGFILE].var, "a");
   if(logfile)
     fputs(buffer, logfile);
   fclose(logfile);

  int ret;
  
  if((ret = write(fd, buffer, buflen)) == -1)
    log_perror(LOG_WARN, "log write error");
  else if(!ret)
    log_perror(LOG_WARN, "log file descriptor closed");
  
  return ret;

}

void log_printf(int llevel, int errstr, const char *fmt, ...)
{
  const int lerrno = errno;
  char buffer1[LOG_BUFSIZE + 1];
  char buffer2[LOG_BUFSIZE + 1];
  va_list ap;
  size_t buflen2;
  
  /* valid? */
  if(llevel < LOG_FATAL || llevel > LOG_DEBUG2)
    return;
  
  /* do we log this level? */
  if(llevel > bot_int16_variables[IVAR_LOGLEVEL].var && llevel > log_filelevel)
    return;
  
  va_start(ap, fmt);
  vsnprintf(buffer1, LOG_BUFSIZE, fmt, ap);
  va_end(ap);
  
  if(errstr)
    buflen2 = snprintf(buffer2, LOG_BUFSIZE, "%s %s: %s\n",
                       log_prefix[llevel], buffer1, strerror(lerrno));
  else
    buflen2 = snprintf(buffer2, LOG_BUFSIZE, "%s %s\n",
                       log_prefix[llevel], buffer1);
  
  if(llevel <= bot_int16_variables[IVAR_LOGLEVEL].var && log_fds[llevel] != -1)
    if(log_write(log_fds[llevel], buffer2, buflen2) <= 0)
      log_fds[llevel] = -1;
  
  if(llevel <= log_filelevel && log_fdfile != -1)
    if(log_write(log_fdfile, buffer2, buflen2) <= 0)
      log_fdfile = -1;
}

int log_conf_level(struct mconf_item *mci, char *para)
{
  int level;

  /* as a number? */
  if(strlen(para) == 1)
  {
    
    level = atoi(para);
    
    if(level < LOG_FATAL || level > LOG_DEBUG2)
      level = -1;
    
  }
  
  /* as a string line LOG_WARN */
  else
  {
    for(level = 0; level <= LOG_DEBUG2; level++)
      if(!strcasecmp(log_name[level], para))
        break;
    
    if(level == LOG_DEBUG2 + 1)
      level = -1;
  }
  
  if(level == -1)
  {
    log_print(LOG_WARN, "invalid log level %s", para);
    return -1;
  }
  
  bot_int16_variables[IVAR_LOGLEVEL].var = level;
  log_print(LOG_INFO, "changed loglevel to %s (%i)",
            log_name[level], level);

  return 0;
}
