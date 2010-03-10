/*
 *  shame [0.2j3/public]
 *  by pf1shy (aka k0kane || digitalenemy || the raping gn0me :)
 *  <pf1shy@segfault.ch>
 *  Mon Jan 21 01:04:26 CET 2002
 *
 *  coded for buttP!RATEZ/UGCiA/interwn.nl.
 *
 *  credits: LordSommer (i took "int resolve" from him), scut (grabbb.c gave me many ideas, heh :).
 *
 *  shouts to (yes i know this is lame..):
 *  buttP!RATEZ: dopestar, cy_, sh0rdy, d1saster,
 *  r00t, module, modify, preamble, eth1cal, philer, ryker (du scheiss taliban :), brainstorm (na p1mp), jak-AWAY, rob,
 *  x[beast]x, phel0n, fut0n, nu|L, ezs, ugcia.net, interwn.nl, woh, electronic souls, trippin smurfs, woot-project, 0xff.
 *
 *  BE NICE!
 *
 *  PS: code cleaned up with indent...i hope you can read it now ;x
 *
 *  oh yeah...and for the lamers, usage: nohup ./shame2 -s 128.0.0.1 -e 128.255.255.255 -p 31337 &
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include "banner.h"

#define LOGO "+"
#define HEAD "+ shame [0.2j3/\033[1mpublic\033[0m]\n  by pf1shy <pf1shy@segfault.ch>\n\n"
#define UBERPROC "/USR/SBIN/CROND                                                                      "

/* #define DEBUG */

pid_t wait(int *status);

/* globs! */
int sock, verbose = 0, s_mode = 0;
unsigned short int port = 0, t_out = 3;

/* functions */
unsigned long int resolve(char *host);
void timeout() { close(sock); }
void wazzzup(char *box);	/* wazzzzzzzzzzzzzup mang!@# */
void usage(char *app, int mc);
void dolog(char *string, char *outfile);

/* go go go! */
int main(int argc, char **argv)
{
    int c;
    char buf[128];
    FILE *infile;
    int childs = 0, maxchilds = 40, start_ip_stat = 0, end_ip_stat = 0;
    unsigned long int start_ip, end_ip, cnt;
    char phile[64];
    struct in_addr addr;

    printf("%s", HEAD);
    if (argc < 2)
	usage(argv[0], maxchilds);

    while ((c = getopt(argc, argv, "vi:c:t:s:e:p:h")) != EOF) {
	switch (c) {
	case 'i':
	    snprintf(phile, sizeof(phile), optarg);
	    break;
	case 'p':
	    port = atoi(optarg);
	    break;
	case 'c':
	    maxchilds = atoi(optarg);
	    break;
	case 't':
	    t_out = atoi(optarg);
	    break;
	case 'v':
	    verbose = 1;
	    break;
	case 's':
	    start_ip = resolve(optarg);
	    start_ip_stat = 1;
	    break;
	case 'e':
	    end_ip = resolve(optarg);
	    end_ip_stat = 1;
	    break;
	case 'h':
	    usage(argv[0], maxchilds);
	default:
	    usage(argv[0], maxchilds);
	}
    }
    /* a special "wurst" for lamers ;p */
    if (start_ip_stat ^ end_ip_stat) {
	printf("%s you must supply an ip-range through using BOTH options (-s and -e), lamer...\n",
	     LOGO);
	exit(0);
    }
    if (port == 0) {
	printf("%s supply a valid port, lamer...\n", LOGO);
	exit(0);
    }
    if (start_ip_stat == 1 && end_ip_stat == 1
	&& (start_ip == -1 || end_ip == -1)) {
	printf("%s supply a valid ip-range, lamer...\n", LOGO);	/* im sorry if you typed 255.255.255.255 ...but who tha fuck wants to scan that?! */
	exit(0);
    }
    if (start_ip_stat == 1 && end_ip_stat == 1)
	s_mode = 0;
    else {
	s_mode = 1;
	if ((infile = fopen(phile, "r")) == NULL) {
	    printf("%s supply a valid file or use the ip-range mode, lamer...\n", LOGO);
	    exit(0);
	}
    }
    /* end */

    strcpy(argv[0], UBERPROC);
    /* add a // if you dont want that :( */

#ifdef DEBUG
    printf
	("\n%s debug:\n  file = %s\n  verbose = %i\n  port = %d\n  maxchild = %i\n  scan mode = %i\n",
	 LOGO, phile, verbose, port, maxchilds, s_mode);
#endif

    if (s_mode == 1) {
	while (fgets(buf, sizeof(buf), infile) != NULL) {
	    if (buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = '\0';
	    if (childs >= maxchilds)
		wait(NULL);

	    switch (fork()) {	/* forki0ni */
	    case 0:
		wazzzup(buf);
		exit(0);
	    case -1:
		perror("fork");
		exit(-1);
	    default:
		childs++;
		break;
		while (childs--)
		    wait(NULL);
	    }
	}
    } else {			/* ok..this part is VERY buggy...but who cares... */
	for (cnt = ntohl(start_ip); cnt <= ntohl(end_ip); cnt++) {
	    if ((cnt & 0xff) == 256)	/* hi ezs, null etc ;p */
		cnt++;
	    if ((cnt & 0xff) == -1)
		cnt++;
	    if (childs >= maxchilds)
		wait(NULL);

	    addr.s_addr = htonl(cnt);
	    snprintf(buf, sizeof(buf), "%s", inet_ntoa(addr));
	    switch (fork()) {
	    case 0:
		wazzzup(buf);
		exit(0);
	    case -1:
		perror("fork");
		exit(-1);
	    default:
		childs++;
		break;
		while (childs--)
		    wait(NULL);
	    }
	}
    }
    exit(0);
}
unsigned long int resolve(char *host)
{				/* stolen from lordsommer :) */
    struct hostent *he;
    unsigned long int resolved;
    he = gethostbyname(host);
    if (he != NULL)
	memcpy(&resolved, he->h_addr, he->h_length);
    else
	resolved = inet_addr(host);
    return resolved;
}

void wazzzup(char *box)
{				/* waaaazzzzzzzzzzzuuuuuuuuuuuuuppp!! */
    int recvd = 0, i = 0;
    char buf[512], write[512], tmp[32];
    struct sockaddr_in unf;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    unf.sin_family = AF_INET;
    if (s_mode == 1)
	unf.sin_addr.s_addr = resolve(box);
    else
	unf.sin_addr.s_addr = inet_addr(box);
    unf.sin_port = htons(port);

    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	exit(0);

    signal(SIGALRM, timeout);
    alarm(t_out);
    if (connect(sock, (struct sockaddr *) &unf, sizeof(unf)) == -1) {
	alarm(0);
	exit(0);
    } else {
	memset(buf, '\0', sizeof(buf));
	recvd = recv(sock, buf, sizeof(buf), 0);
	if (recvd > 0) {
	    if (buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = '\0';
	    if (verbose)
		printf("%s [%s:%d] - %s\n",
		       (char *) inet_ntoa(unf.sin_addr), box, port, buf);
	    snprintf(tmp, sizeof(tmp), "banner[%d].log", port);
	    snprintf(write, sizeof(write), "%s [%s] - %s\n",
		     (char *) inet_ntoa(unf.sin_addr), box, buf);
	    dolog(write, tmp);

	    if (port == 21) {
		while (banner_21[i++].version != NULL) {
		    if (strstr(buf, banner_21[i].version)) {
			snprintf(write, sizeof(write), "%s [%s] - %s\n", (char *) inet_ntoa(unf.sin_addr), box, buf);
			dolog(write, banner_21[i++].log);
			goto hoe;
		    }
		}
	    } else if (port == 23) {
		while (banner_23[i++].version != NULL) {
		    if (strstr(buf, banner_23[i].version)) {
			snprintf(write, sizeof(write), "%s [%s] - %s\n", (char *) inet_ntoa(unf.sin_addr), box, buf);
			dolog(write, banner_23[i++].log);
			goto hoe;
		    }
		}
	    } else if (port == 22) {
		while (banner_22[i++].version != NULL) {
		    if (strstr(buf, banner_22[i].version)) {
			snprintf(write, sizeof(write), "%s [%s] - %s\n", (char *) inet_ntoa(unf.sin_addr), box, buf);
			dolog(write, banner_22[i].log);
			goto hoe;
		    }
		}
		/* and so on....
		   } else if (port == 22) {
		   while (banner_22[i].version != NULL) {
		   if (strstr(buf, banner_22[i].version)) {
		   snprintf(write, sizeof(write), "%s [%s] - %s\n", (char *) inet_ntoa(unf.sin_addr), box, buf);
		   dolog(write, banner_22[i++].log);
		   goto hoe;
		   }
		   } */
	    }
	}
    }
  hoe:
    alarm(0);
    exit(0);
}

void dolog(char *string, char *outfile)
{				/* our uberleet++ log thingy! */
    FILE *output;
    output = fopen(outfile, "aw+");
    fprintf(output, string);
    fclose(output);
}

void usage(char *app, int mc)
{				/* the usage. very very important! */
    printf("%s usage: %s <(-s startip -e endip) | (-i infile)> <-p port> [options]\n\n", LOGO, app);

    /*printf("%s e.g.\n  bash-2.05$ nohup %s -s 69.1.1.1 -e 69.69.69.69 -p 21 &\n", LOGO, app);
       printf("  bash-2.05$ nohup %s -i file_with_hosts -p 21 &\n\n", app); */
    /* this tool is not for lamers! */

    printf("%s options\n"
	   "  -c childs\t\tdefault is %i\n"
	   "  -t timeout\t\tdefault is %i\n"
	   "  -v\t\t\tverbose mode\n", LOGO, mc, t_out);
    exit(0);
}

/* <°))>< *sniff* *sniff* */
