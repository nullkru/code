#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <inttypes.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include <signal.h>
#include <errno.h>

#include "client.h"
#include "mconf.h"
#include "functions.h"
#include "irc.h"
#include "log.h"
#include "plugin_load.h"
#include "api.h"
#include "variables_data.h"
#include "tcl.h"

void usage(char *prog);

extern int errno;

int bot_term = 0;

void signal_handler(int signum)
{
  switch(signum)
  {
    case SIGINT:
    case SIGTERM:
    {
      bot_term++;
      log_print(LOG_INFO, "exit!");
      break;
    }
    case SIGPIPE:
    {
      /* broken pipe */
      bot_term++;
      break;
    }
    case SIGHUP:
    {
      if(mconf_file())
        log_print(LOG_WARN, "couldn't reload config file");
      
      break;
    }
  }
}

void loop(void)
{
  int ret;
  struct pollfd pfds[1];
  
  pfds[0].fd = client_fd;
  pfds[0].events = POLLIN;
  
  while(!bot_term)
  {
    if((ret = poll(pfds, 1, 10000)) == -1)
    {
      if(errno != EINTR)
      {
        log_perror(LOG_FATAL, "poll error");
        exit(-1);
      }
    }
    else if(ret && pfds[0].revents)
      client_read();
  }
   
}

int main(int argc, char *argv[])
{
  int ret;
  
  signal(SIGINT,  signal_handler);
  signal(SIGTERM, signal_handler);
  signal(SIGHUP,  signal_handler);
  signal(SIGPIPE, signal_handler);
   
  if((ret = mconf_line(argc, argv)) == -1)
    return -1;
  else if(ret)
    return 0;
  mconf_file();   
  init_tcl();
  
  if(bot_int16_variables[IVAR_USESSL].var)
    init_ssl();
  
  setup_hooks();
  load_plugins();
  client_connect();
  fct_login();

  loop();
  
  client_close();
  unload_plugins();
  
  return 0;
}
