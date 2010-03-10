#ifndef PLUGIN_LOAD_H
#define PLUGIN_LOAD_H

#define die(x) { fprintf (stderr, "%s\n", x); exit(EXIT_FAILURE); }
#define die_perror(x) { perror(x); exit(EXIT_FAILURE); }

#define FOR_EACH(x) for(plugin_listptr = x; plugin_listptr->name != NULL || plugin_listptr->next != NULL; plugin_listptr = plugin_listptr->next)

#define list_add(x, y) x->name = calloc(strlen(y)+1, sizeof(char)); \
                       strcpy(x->name, y); \
                       x = (x->next = (struct plugin_list*) malloc(sizeof(struct plugin_list)));

struct plugin_list
{
  char *name;             /* plugin name */
  void *handle;           /* handle for dlsym() / GetProcAddress() */
  struct plugin_list *last, *next;
};

#ifdef WIN32
 #define PLUGIN_SUFFIX ".dll"
#else
 #define PLUGIN_SUFFIX ".so"
#endif

int plugin_verify(char *path);
int plugin_search(char *directory);
void add_plugin(char *name);
void remove_plugin(char *name);
void *plugin_load(char *name);
void plugin_unload(void *handle);
void *plugin_register(void *handle, char *function);
void load_plugins(void);
void unload_plugins(void);  

extern char *error;
extern struct plugin_list plugins[];
extern struct plugin_list *plugin_listptr;

#endif
