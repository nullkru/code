/* $Id: getip.c,v 1.1 2003/02/07 14:05:52 smoli Exp $ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <linux/sockios.h>

#define IFACE "eth0"

struct in_addr get_ip(const char *interface) {
  
  struct ifreq        ifr;  
  struct sockaddr_in *si;
  int                 sock;
  
  strcpy(ifr.ifr_name, interface);
  
  sock = socket(AF_INET, SOCK_STREAM, 0);
  ifr.ifr_addr.sa_family = AF_INET;
  
  if(ioctl(sock, SIOCGIFADDR, &ifr) < 0)
    perror("SIOCGIFADDR");
  
  close(sock);
  
  si = (struct sockaddr_in *)&ifr.ifr_addr;
  
  return si->sin_addr;
}

int main() {
  
  printf("the address of "IFACE" is: %s\n", inet_ntoa(get_ip(IFACE)));
  
  return 0;
}
