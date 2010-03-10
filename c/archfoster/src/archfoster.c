/* archfoster util to weed archlinux pkgs */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "0.1"
#define PACMAN "/usr/bin/pacman"
#define BUF 255
#define SEPERATOR "----------" 

/* functions */
int removepkg(void);
int help(void);
int get_pkgs(void);
int ask_pkg(char *acc_pkg, int no);
/* vars */
int rec = 0;

int main(int argc, char **argv)
{
  int opt;
  while ((opt = getopt (argc, argv, "vhra")) != EOF) {
    switch(opt) {
      case 'v':
         	printf("Version: %s\n", VERSION);
         	printf("coded by kru_ (mirk@chao.ch)\nhttp://chao.ch\n");
		printf("This is my first C programm so don't blame me or... "\
			"else you have my e-mail address.\n");
         	return 0;
         	break;
      case 'h':
         	help();
         	break;
      case 'r':
		printf("You chose recursive option\n");
		rec = 1;
		get_pkgs();
		break;
      default:
         	help();
		return 0;
		
	}
  }

  /* go go go */
	if(argv[1] == NULL || argv[1] == "r") {
  		get_pkgs();
	}
		
}

/* 
 * alle installierten pakete in ein array schreiben von dort
 * jedes paket abfragen ob behalten oder entfernen allenfalls 
 * informationen anzeigen
 */
int get_pkgs(void) {
	extern int rec;
	if( rec == 1 ){
		printf("Sorry not implemented yet\n");
		return 0;
	}
	else {
		FILE *pkgs;
		char line[256];
		/*
		 * hier ev speicher reservieren...
		 * realloc();
		 */
		pkgs = popen("/usr/bin/pacman -Qi | awk '{ print $1 }'", "r");
		//pkgs = popen("ls /", "r");
		int arrayno = 0;
		while(fgets(line, sizeof(line), pkgs)){
			printf("Package --> %s", line);
			/* \n entfernen */
			if(line[strlen(line)-1]=='\n')
			       	line[strlen(line)-1] = '\0';
			arrayno++;
			ask_pkg(line,arrayno);
		}
		return 0;
	}
}



int removepkg(void) {
	
	
	char *args[] = {
		"archfoster",
		"-Qs",
		NULL,
	};

	execve("/usr/bin/pacman", args, NULL);
	return 0;
}


int ask_pkg(char *acc_pkg, int no) {
	char getinput[8], answer;
	printf("Keep %s? [Ynipq], [h]elp:", acc_pkg);
	
	fgets(getinput,sizeof(getinput), stdin);
	sscanf(getinput, "%c", &answer);
	
	/* show pakage informations */
	int show_info(char *pkg) {
		/* acc_pkg in popen mit hilfe von snprintf setzen */
		printf("----- %s -----\n", pkg);
		popen("/usr/bin/pacman -Qs acc_pkg", "w");
		printf("%s\n",SEPERATOR);
	}

	int add_del(char *pkg, int num) {
		int del_pkg[BUF];
		del_pkg[num] = pkg;
		printf("%c\n", del_pkg[num]);
	}
	
	switch(answer) {
		case 'n':
			printf("-->delete it\n");
			add_del(acc_pkg,no);
			break;
		case 'y':
			printf("-->keep it\n");
			break;
		case 'i':
			show_info(acc_pkg);
			break;
		case 'q':
			printf("Stop here\n");	
			break;
		case 'p':
			printf("pre\n");
			break;
		case 'h':
			printf("\n %s\ny - keep package\n"\
				"n - delete it\n"\
				"i - show informations\n"\
				"p - go one step back\n"\
				"q - exit and delete packages\n");
			break;
		default:
			printf("-->default\n");
	}
}

int help(void) {
	printf("archfoster - weed unnecessary archlinux packages ;)\n");
	printf("Help:\n");
	printf("\t-h \t - this helptext\n");
	printf("\t-r \t - recursive option(ask all NUM installed packages)\n");
	printf("\t-v \t - print version,author infos and exit\n"); 
	return EXIT_SUCCESS;
}
