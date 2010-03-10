#ifndef MCONF_H
#define MCONF_H


/****************************************************************************
 * some headers needed
 ****************************************************************************/
#include <stdio.h> 
#include <inttypes.h>


/****************************************************************************
 * defines
 ****************************************************************************/
#define MCONF_LINE  0x01 // command line options
#define MCONF_FILE  0x02 // config file
#define MCONF_INPUT 0x04 // stdin

/* to what type of data does struct mconf_item->pointer point? */
#define MCONF_NOTYPE  0 // nowhere
#define MCONF_UINT32  1 // to an uint32_t
#define MCONF_UINT16  2 // to an uint16_t
#define MCONF_CHARPTR 3 // to a char *
#define MCONF_CHARARRAY 4 // to a char[]

/****************************************************************************
 *  * types
 *  ****************************************************************************/
struct mconf_section;
struct mconf_item;

typedef int (mconf_shandler_t)(struct mconf_section *, int parc, char *parv[]);
typedef int (mconf_ihandler_t)(struct mconf_item *, char *para);

struct mconf_item {
  char              keychar; // for use like -<char> on command line
  char             *keyword; // for --<keyword> or in config file
  uint32_t          control; // see * defines *
  mconf_ihandler_t *handler; // the function for this item (or NULL)
  void             *pointer; // pointer to the save locations (or NULL)
  int               ptrtype; // jo... see enum mconf_type
  char             *parname; // the name of the argument
  char             *helptxt; // help text for the section item
};

struct mconf_section {
  char              *keyword; // NULL for default section
  struct mconf_item *items;   // all struct mconf_item in this section
  mconf_shandler_t  *handler; // the handler for this section
  char              *help;    // help text for the section
};

/* see mconf_line() for details of this struct */
struct mconf_alias {
  char               keychar;
  struct mconf_item *item;
  char              *para;
};


  
/****************************************************************************
 * functions
 ****************************************************************************/
void mconf_init       (void);
void mconf_exit       (void);
void mconf_register   (struct mconf_item *);
void mconf_unregister (void);
int  mconf_line       (int argc, char *argv[]);
int  mconf_file       (void);



#endif /* #ifndef CONF_H */
