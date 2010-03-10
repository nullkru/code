#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#include <tcl.h>

#include "variables.h"
#include "tclcommands.h"
#include "tcl.h"
#include "log.h"

#define TCL_SCRIPT_DIR "scripts"

static Tcl_Interp *bot_interp = NULL;

static struct scriptlist
{
   char *filename;
   struct scriptlist *next;
} script_list =
{
     NULL,
     NULL
};

int loaded_scripts = 0;
int total_scripts = 0;

static struct scriptlist *scriptptr = &script_list;

/* list routines */
#define FOR_EACH_SCRIPT for(scriptptr = &script_list; scriptptr->next != NULL; scriptptr = scriptptr->next)
static void add_script(const char *filename)
{
   scriptptr->filename = malloc(strlen(filename)+1);
   strcpy(scriptptr->filename, filename);
   scriptptr = (scriptptr->next = (struct scriptlist*) malloc(sizeof(struct scriptlist)));
   scriptptr->next = NULL;
}

void init_tcl(void)
{
   int ret, i;
   char buf[20];
   
   if((bot_interp = Tcl_CreateInterp()) == NULL)
        {
	   log_print(LOG_WARN, "coudln't create tcl interpreter");
	   return;
	}
  
   if (Tcl_Init(bot_interp) != TCL_OK)
     {
          Tcl_DeleteInterp(bot_interp);
          bot_interp = NULL;
	  log_print(LOG_WARN, "coudln't init tcl");
          return;
     }

   #ifdef DEBUG
   Tcl_SetVar(bot_interp,"debugmode","1", 0);
   #endif
   
   for(i=0; i < CHAR_VARIABLES; i++)
   {
     Tcl_SetVar(bot_interp, bot_char_variables[i].name, bot_char_variables[i].var != NULL ? bot_char_variables[i].var : "(null)", 0);
     /*if(Tcl_LinkVar(bot_interp, bot_char_variables[i].name, (char *) &bot_char_variables[i].var, TCL_LINK_STRING) != TCL_OK)
           log_print(LOG_WARN, "coudln't link variable `%s': %s", bot_char_variables[i].name, bot_interp->result);*/ // needs malloc() or TclAlloc()ed block of memory
   }

   for(i=0; i < INT16_VARIABLES; i++)
     {
	sprintf(buf, "%d", bot_int16_variables[i].var);
	Tcl_SetVar(bot_interp, bot_int16_variables[i].name, buf, 0);
        if(Tcl_LinkVar(bot_interp, bot_int16_variables[i].name, (char *) &bot_int16_variables[i].var, TCL_LINK_INT) != TCL_OK)
             log_print(LOG_WARN, "coudln't link variable `%s': %s", bot_int16_variables[i].name, bot_interp->result);
     }
   
   Tcl_CreateCommand(bot_interp, "random", RandomCmd, NULL, NULL);
   Tcl_CreateObjCommand(bot_interp, "orandom", RandomObjCmd, NULL, NULL);
      
   Tcl_PkgProvide(bot_interp, "botapi", "1.0");
   
   if(find_tcl_scripts(TCL_SCRIPT_DIR))
     log_print(LOG_INFO, "loading tcl scripts...");
     
   FOR_EACH_SCRIPT
     {
	ret = execute_tcl_script(scriptptr->filename);
	if(ret == 1)
	  loaded_scripts++;
	total_scripts++;
     }
   
   log_print(LOG_INFO, "%d out of %d scripts were valid", loaded_scripts, total_scripts);
}

int execute_tcl_script(const char *file)
{
   if(Tcl_EvalFile(bot_interp, file) == TCL_OK)
     {
	log_print(LOG_INFO, "%s executed", file);
	return 1;
     }
   else
     {
	log_print(LOG_WARN, "coudln't execute script `%s': %s",
		             file, bot_interp->result);
	return 0;
     }
}

void fini_tcl(void)
{
   Tcl_DeleteInterp(bot_interp);
}

int find_tcl_scripts(char *directory)
{
   char *pathname;
   char linkname[256+1];
   struct dirent *dirp;
   struct stat statbuf;
   DIR *dirh;
   int result = 0;
   
   if ((dirh = opendir(directory)) == NULL)
     {
	log_print(LOG_WARN, "coudln't open dir `%s'", directory);
	return -1;
     }
   
   for(dirp = readdir(dirh); dirp != NULL; dirp = readdir(dirh))
     {
	
	if(!strcmp(".",dirp->d_name) || !strcmp("..",dirp->d_name))
	  continue;
	pathname = calloc(strlen(dirp->d_name)+strlen(directory)+2, sizeof(char));
	sprintf(pathname,"%s/%s", directory, dirp->d_name);
	if(lstat(pathname, &statbuf) == -1)
	  {
	     log_print(LOG_WARN, "coudln't stat `%s'", pathname);
	     continue;
	  }
	if(!strcmp(pathname+strlen(pathname)-4, ".tcl"))
	  {
	     if(S_ISREG(statbuf.st_mode))
	       {
		  add_script(pathname);
		  result++;
	       }
	     else if(S_ISLNK(statbuf.st_mode))
	       {
		  readlink(pathname, linkname, 256);
		  add_script(linkname);
		  result++;
	       }
	     
	  }
	
     }
   closedir(dirh);
   return result;
}
