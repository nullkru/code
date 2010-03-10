#include "../config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <openssl/ssl.h>
/*#include <pthread.h>*/

#include "bot.h"
#include "irc.h"
#include "log.h"
#include "client.h"
#include "variables.h"
#include "ssl.h"

#define CLIENT_INBUFSIZE 2048

int client_fd = -1;
static char buffer[CLIENT_INBUFSIZE + 1];
/*pthread_t *newthread;*/

/*
 * write and read streams for buffering
 */

/*
 * client_connect()
 * tries to connect to the given server
 */
void client_connect(void)
{
  struct hostent *host;
  struct sockaddr_in addr;
  int flags;
  
  /* log_print(LOG_INFO, "resolving hostname..."); */
  
  host = gethostbyname(bot_char_variables[CVAR_HOST].var);
  
  if(!host)
  {
    log_print(LOG_FATAL, "couldn't resolve %s\n", bot_char_variables[CVAR_HOST].var);
    exit(-1);
  }
    
  if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
  {
    log_perror(LOG_FATAL, "socket error");
    exit(-1);
  }
  
  bzero(&addr, sizeof(struct sockaddr_in));
  
  addr.sin_family = AF_INET;
  addr.sin_port=htons(bot_int16_variables[IVAR_PORT].var);
  
  memcpy(&addr.sin_addr, host->h_addr, host->h_length);
  
  log_print(LOG_STATUS, "connecting %s (port %u)...",
            inet_ntoa(addr.sin_addr), htons(addr.sin_port));
  
  if(connect(client_fd, (struct sockaddr*)&addr,
             sizeof(struct sockaddr_in))==-1)
  {
    log_perror(LOG_FATAL, "connect error");
    exit(-1);
  }
  
  if(bot_int16_variables[IVAR_USESSL].var)
	ssl_handshake(client_fd);
  else
     {
	flags = fcntl(client_fd, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(client_fd, F_SETFL, flags);
     }
  
  log_print(LOG_STATUS, "connected");
}

void client_close(void)
{
  if(close(client_fd))
  {
    log_perror(LOG_FATAL, "couln't close socket");
    exit(-1);
  }
}

void client_write(const char *buffer, size_t buflen)
{
  int ret;
  
  if(bot_int16_variables[IVAR_USESSL].var)
     ret = SSL_write(ssl, buffer, buflen);
  else
     ret = write(client_fd, buffer, buflen);
  
  if(ret == -1)
  {
    log_perror(LOG_FATAL, "client write error");
    exit(-1);
  }
  else if(!ret)
  {
    log_print(LOG_WARN, "server closed connection :/");
    exit(-1);
  }
}

void client_read(void)
{
  int ret;
       
  if(bot_int16_variables[IVAR_USESSL].var)
     ret = SSL_read(ssl, buffer, CLIENT_INBUFSIZE);
  else
     ret = read(client_fd, buffer, CLIENT_INBUFSIZE);
     
  if(ret == -1)
  {
    log_perror(LOG_FATAL, "client read error");
    exit(-1);
  }
  else if(!ret)
  {
    log_print(LOG_WARN, "server closed connection");
    exit(-1);
  }
  
  /* NULL-terminate buffer for irc_parse() */
  buffer[ret] = '\0';
  
  /*newthread = (pthread_t*) malloc(sizeof(pthread_t));*/
  /* parse buffer */
  /* pthread_create(newthread, NULL, (void*)&irc_parse_packet, buffer); */
  irc_parse_packet(buffer);
}
