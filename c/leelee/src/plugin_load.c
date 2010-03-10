#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <dlfcn.h>

#ifdef __OpenBSD__
 #define RTLD_LAZY DL_LAZY
#else
 #ifndef RTLD_LAZY
    #define RTLD_LAZY RTLD_NOW
 #endif
#endif

#include "api.h"
#include "log.h"
#include "irc.h"
#include "plugin_load.h"

struct plugin_list plugins[] = {{NULL},{NULL}};
struct plugin_list *plugin_listptr = NULL;
char *error = NULL;

static void (*plugin_init)(void);
static void (*plugin_fini)(void);


static struct plugin_list *get_plugin_by_name(char *name)
{
   FOR_EACH(plugins)
     {
	if(!strcasecmp(plugin_listptr->name, name))
	  return plugin_listptr;
     }
   return NULL;
}

void add_plugin(char *name)
{
   void *last_item = plugin_listptr, *handle;
   struct plugin_list *ptr = get_plugin_by_name(name);
   if(ptr)
     {
	log_print(LOG_WARN, "module `%s' already loaded", name);
	return;
     }
   plugin_listptr->name = calloc(strlen(name)+1, sizeof(char));
   strcpy(plugin_listptr->name, name);
   plugin_listptr = (plugin_listptr->next = (struct plugin_list*) malloc(sizeof(struct plugin_list)));
   plugin_listptr->last = last_item;

   handle = plugin_load(plugin_listptr->name);
   plugin_listptr->handle = handle;
   #ifdef __OpenBSD__
   *(void **) &plugin_init = plugin_register(handle, "_plugin_init");
   #else
   *(void **) &plugin_init = plugin_register(handle, "plugin_init");
   #endif
   plugin_init();
}


void remove_plugin(char *name)
{
   struct plugin_list *ptr = get_plugin_by_name(name);
   if(!ptr)
     {
	log_print(LOG_WARN, "module `%s' isn't loaded", name);
	return;
     }
   else if(ptr->last != NULL)
     {
	/* wenn aktuelles element naechstes element hat, next vom letzten element darauf setzen, sonst NULL */
	ptr->last->next = (ptr->next != NULL ? ptr->next : NULL);
	/* wenn aktuelles element naechstes element hat, last pointer vom naechsten auf last pointer vom aktuellen setzen*/
	if(ptr->next != NULL)
	  ptr->next->last = ptr->last;
	free(ptr->name);
	ptr->name = NULL;
     }
   else
     {
	/* erstes element */
	if(ptr->next != NULL)
	  ptr->next->last = ptr->last;
	free(ptr->name);
	ptr->name = NULL;
     }
   
   #ifdef __OpenBSD__
   *(void **) &plugin_fini = plugin_register(ptr->handle, "_plugin_fini");
   #else
   *(void **) &plugin_fini = plugin_register(ptr->handle, "plugin_fini");
   #endif
   plugin_fini();
   plugin_unload(ptr->handle);
}

void load_plugins(void)
{
   void *handle;
   
   log_print(LOG_STATUS, "loading plugins...");
   log_print(LOG_INFO, "%d plugins found", plugin_search("plugins"));
   
   FOR_EACH(plugins)
     {	
       log_print(LOG_INFO, "loading %s...", plugin_listptr->name);
       handle = plugin_load(plugin_listptr->name);
       plugin_listptr->handle = handle;
       #ifdef __OpenBSD__
       *(void **) &plugin_init = plugin_register(handle, "_plugin_init");
       #else
       *(void **) &plugin_init = plugin_register(handle, "plugin_init");
       #endif
       plugin_init();
     }   
}

void unload_plugins(void)
{
   log_print(LOG_STATUS, "unloading plugins...");
   
   FOR_EACH(plugins)
     {
	log_print(LOG_INFO, "unloading %s", plugin_listptr->name);
	*(void **) &plugin_fini = plugin_register(plugin_listptr->handle, "plugin_fini");
	 plugin_fini();
	 plugin_unload(plugin_listptr->handle);
     }
}

int plugin_verify(char *path)
{
  int ret;
  int (*plugin_check)(void);
  void *handle = plugin_load(path);
  *(void **) (&plugin_check) = plugin_register(handle, "plugin_check");
  ret = plugin_check();
  plugin_unload(handle);
  return (ret == PLUGIN_VERIFICATION ? 1 : 0);
}

int plugin_search(char *directory)
{
  char *pathname;
  char linkname[256+1];
  char *filename = NULL;
  struct dirent *dirp;
  struct stat statbuf;
  DIR *dirh;
  int result = 0;
  struct plugin_list *newitem;

  if ((dirh = opendir(directory)) == NULL)
   die_perror("opendir()");
 
  for(dirp = readdir(dirh), plugin_listptr = plugins; dirp != NULL; dirp = readdir(dirh))
   {
    if(!strcmp(".",dirp->d_name) || !strcmp("..",dirp->d_name))
      continue; 
    pathname = calloc(strlen(dirp->d_name)+strlen(directory)+2, sizeof(char));
    sprintf(pathname,"%s/%s", directory, dirp->d_name);
    if(lstat(pathname, &statbuf) == -1)
     {
      die_perror("stat");
      continue;
     }

    if(!strcmp(pathname+strlen(pathname)-strlen(PLUGIN_SUFFIX), PLUGIN_SUFFIX))
     {
      if(S_ISREG(statbuf.st_mode))
	   filename = strdup(pathname);
      else if(S_ISLNK(statbuf.st_mode))
	  {
	     readlink(pathname, linkname, 256);
	     filename = strdup(linkname);
	  }
      
      if(plugin_verify(filename))      
         {
	    plugin_listptr->name = calloc(strlen(filename)+1, sizeof(char));
	    strcpy(plugin_listptr->name, filename);
	    newitem = (struct plugin_list*) malloc(sizeof(struct plugin_list));
            newitem->last = plugin_listptr;
	    newitem->next = NULL;
	    newitem->name = NULL;
	    plugin_listptr->next = newitem;
	    plugin_listptr = newitem;
	    result++;
         }
	
     }
   }
  closedir(dirh);
  return result;
}

void *plugin_register(void *handle, char *function)
{
   void *ret = dlsym(handle, function);
   if ((error = dlerror()) != NULL)
     die(error);
   return ret;
}

void *plugin_load(char *name)
{
   void *handle = dlopen (name, RTLD_LAZY);
   if(!handle)
     die(dlerror());
   dlerror();
   return handle ? handle : NULL;
}

void plugin_unload(void *handle)
{
   if(dlclose(handle) != 0)
     die(dlerror());
   return;
}
