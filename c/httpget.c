/*
*von gichty!!!!
*/
 void download_url(char *url)
{
  char *host, *file, *protocol;
  char request[BUFSIZE];
  char buf[BUFSIZE];
  int bytes_read = 0;
  int i;
  SOCKET sock;
  FILE *f;
  if(host = strdup(strstr(url, "//")+2))
  {
     if(file = strstr(host, "/")+1)
     {
        for(i=0; i<strlen(host); i++)
        {
          if(host[i] == '/')
            host[i] = '\0';
        }
     }
  }
  
  log_print(LOG_INFO, "download url: host: %s\nfile: %s", host, file);
  
  sock = tcp_connect(host, 80);
  strncpy(request, "GET /", sizeof(request));
  strncat(request, file, sizeof(request));
  strncat(request, "\n", sizeof(request));
  tcp_socket_write(sock, request, sizeof(request));
  f = fopen(file, "w");
  while(bytes_read = tcp_socket_read(sock, buf, sizeof(buf)) != -1)
  {
     fwrite(buf, 1, strlen(buf), f);
  }
  fclose(f);
}
