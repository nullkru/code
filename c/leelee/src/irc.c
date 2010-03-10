#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "api.h"
#include "irc.h"
#include "cmd.h"
#include "client.h"
#include "log.h"

#define IRC_BUFSIZE 2048

void irc_print(struct irc_msg *m)
{
  unsigned int i;
  
  debug(2, "prefix: %s", m->prefix ? m->prefix : "null");
  debug(2, "cmd: %s", m->cmd);
  debug(2, "dest: %s", m->dest);
  debug(2, "argc: %i", m->argc);
  
  for(i = 0; i < m->argc; i++)
    debug(2, "argv[%i]: %s", i, m->argv[i] ? m->argv[i] : "null");   
}

char *irc_parse_next(char *buffer)
{
  char *p;
  
  for(p = buffer; *p != '\0'; p++)
    if(*p == ' ')
      return p;
  
  return NULL;
}

int irc_parse_line(struct irc_msg *m, char *buffer)
{
  char *p = buffer;
  int last = 0;
  
  debug(1, "<<< %s", buffer);
  
  if(*p == ':')
  {
    m->prefix = ++p;

    if((p = irc_parse_next(p)) == NULL)
      return -1;
    
    *p++ = '\0';
  }
  else
    m->prefix = NULL;
  
  m->cmd = p;
  if((p = irc_parse_next(p)) == NULL)
    return -1;
  *p++ = '\0';
  
  m->dest = p;
  if((p = irc_parse_next(p)) == NULL)
    return -1;
  *p++ = '\0';
  
  for(m->argc = 0; m->argc < IRC_MAXARGS; m->argc++)
  {
    if(*p == ':')
    {
      last++;
      p++;
    }
    
    m->argv[m->argc] = p;
    if((p = irc_parse_next(p)) == NULL)
    {
      m->argc++;
      break;
    }
        
    if(last)
    {
      m->argc++;
      break;
    }
    
    *p++ = '\0';
  }
  
  m->argv[m->argc] = NULL;
  
  return 0;
}

void irc_parse_packet(char *buffer)
{
  struct irc_msg m;
  char *p;
  char *lastline = buffer;
  
  for(p = buffer; *p != '\0'; p++)
    if(*p == '\n' || *p == '\r')
    {
      if(p != lastline)
      {
        *p = '\0';
        if(irc_parse_line(&m, lastline) != -1)
           irc_print(&m);
        
        cmd_call(&m);
      }
      
      lastline = p + 1;
    }
  
}

void irc_send(char *cmd, char *dest, char *fmt, ...)
{
  char buffer1[IRC_BUFSIZE + 1];
  char buffer2[IRC_BUFSIZE + 3];
  int buflen2;
  va_list ap;
  
  va_start(ap, fmt);
  vsnprintf(buffer1, IRC_BUFSIZE, fmt, ap);
  va_end(ap);
  
  buflen2 = snprintf(buffer2, IRC_BUFSIZE, "%s %s %s",
                     cmd, dest, buffer1);
  
  debug(1, ">>> %s", buffer2);
  
  buffer2[buflen2++] = '\r';
  buffer2[buflen2++] = '\n';
  buffer2[buflen2]   = '\0';
  
  client_write(buffer2, strlen(buffer2));
}
