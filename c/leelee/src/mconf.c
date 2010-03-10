/*
 * Copyright 2004 Manuel Kohler
 * 
 * This file is part of habash.
 *
 * habash is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * habash is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with habash; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


/****************************************************************************
 * libc headers
 ****************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/****************************************************************************
 * server headers
 ****************************************************************************/
#include "bot.h"
#include "mconf.h"
#include "mconf_data.h"
#include "variables.h"
#include "log.h"

/****************************************************************************
 * defines
 ****************************************************************************/
#define DEFAULT_conffile "./bot.conf"
#define MCONF_BUFSIZE     512
#define MCONF_CHANGECOUNT 20

/****************************************************************************
 * prototypes
 ****************************************************************************/
int mconf_conf_help(struct mconf_item *mci, char *para);


/****************************************************************************
 * types
 ****************************************************************************/
/* struct mconf_change_section {
  struct mconf_section *section;
}; */

struct mconf_change {
  struct mconf_item *item; // which item is changed
  char              *para; // the new value
};

/****************************************************************************
 * globals
 ****************************************************************************/
int mconf_log;
char *mconf_filename;

struct mconf_change mconf_changelist[MCONF_CHANGECOUNT];
int mconf_changecount;


char mconf_chars[256] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/*
 * INIT AND EXIT MODULE
 */

/****************************************************************************
 * mconf_init()
 * intitialize mconf
 ****************************************************************************/

/*
 * SOME UTIL FUNCTIONS
 */

/****************************************************************************
 * mconf_find_by_keyword
 * searches for a item in mconf_list with the given keyword
 ****************************************************************************/
static struct mconf_item *mconf_find_by_keyword(char *keyword)
{
  int i;
  
  for(i = 0; i < MCONF_LISTCOUNT; i++)
    if(!strcasecmp(mconf_list[i].keyword, keyword))
      return &mconf_list[i];
  
  return NULL;
}


/****************************************************************************
 * mconf_find_by_keychar
 * searches for a item in mconf_list with the given key character
 ****************************************************************************/
static struct mconf_item *mconf_find_by_keychar(char keychar)
{
  int i;
  
  for(i = 0; i < MCONF_LISTCOUNT; i++)
    if(mconf_list[i].keychar == keychar)
      return &mconf_list[i];
  
  return NULL;
}





/*
 * GLOBAL FUNCTIONS FOR COMMAND LINE, CONFIG FILE AND INPUT
 */

/****************************************************************************
 * mconf_change_add()
 * adds item and parameter to the change list
 ****************************************************************************/
void mconf_change_add(struct mconf_item *item, char *para)
{
  mconf_changelist[mconf_changecount].para = para;
  mconf_changelist[mconf_changecount].item = item;
  
  ++mconf_changecount;
}

/****************************************************************************
 * mconf_change_add()
 * adds item and parameter to the change list
 ****************************************************************************/
void mconf_change_clear(void)
{
  mconf_changecount = 0;
}

/****************************************************************************
 * mconf_change_pointer()
 * changes the pointer value
 ****************************************************************************/
int mconf_change_pointer(struct mconf_item *mci, char *para)
{
  char *ptr;
  switch(mci->ptrtype)
  {
    case MCONF_CHARARRAY:
     
      if((ptr = strdup(para)) == NULL)
	 return -1;
       
      strncpy((char*)mci->pointer, ptr, CHAR_VARIABLE_SIZE-1);
      return 0;
     
    case MCONF_UINT16:

      *(uint16_t *)mci->pointer = (uint16_t)atoi(para);

      debug(1, "pointer %x changed to (uint16_t)%u",
            mci->pointer, *(uint16_t *)mci->pointer);
      return 0;
    
    case MCONF_UINT32:
      
      *(uint32_t *)mci->pointer = (uint32_t)atoi(para);
    
      debug(1, "pointer %x changed to (uint32_t)%u",
            mci->pointer, *(uint32_t *)mci->pointer);
      return 0;
  
    case MCONF_CHARPTR:

      if((ptr = strdup(para)) == NULL)  
        return -1;
      
      *(char **)mci->pointer = ptr;
      
      debug(1, "pointer %x changed to (char *) `%s'",
            mci->pointer, *(char **)mci->pointer);
      
    default:
      return 0;
  }
}

/****************************************************************************
 * mconf_change()
 * change config value
 ****************************************************************************/
int mconf_change_do(void)
{
  struct mconf_item *mci;
  int ret;
  int i;
  
  for(i = 0; i < mconf_changecount; i++)
  {
    mci = mconf_changelist[i].item;
    
    debug(1, "%s: keyword=`%s'; value=`%s'", __func__,
          mconf_changelist[i].item->keyword, mconf_changelist[i].para);
    
    /*
     * call the function if not NULL. return values are:
     * -1 -> error
     *  0 -> ok
     *  1 -> for exit with success
     */
    if(mci->handler)
    {
      ret = (mconf_changelist[i].item->handler)
              (mconf_changelist[i].item, mconf_changelist[i].para);
    
      if(ret == -1)
        return -1;
      
      else if(ret == 1)
        return 1;
    }
    
    if(mci->pointer)
    {
      if(mconf_change_pointer(mci, mconf_changelist[i].para))
        return -1;
    }
  }
  
  return 0;
}




/*
 * FUNCTIONS TO PARSE INPUT
 */
/****************************************************************************
 * mconf_input()
 * parses the stdin
 ****************************************************************************/





/*
 * FUNCTIONS TO PARSE CONFIG FILES
 */

/****************************************************************************
 * mconf_file_garbage()
 * remove all garbage character out of a config file buffer
 ****************************************************************************/
int mconf_file_garbage(char *buffer)
{
  char *ps;               /* keychar to test */
  char *pd      = buffer; /* were char to keep are kept ;) */
  int   comment = 0;      /* 1 when ps points to comment */
  int   string  = 0;      /* 1 when ps points to string in "" */
  
  /* test all keychars in buffer */
  for(ps = buffer; *ps != '\0'; ps++)
  {
    /* are we in a comment? */
    if(comment)
    {
      /* does the comment end? */
      if(*ps == '\n')
        comment--;
    }
    
    /* are we in a string? */
    else if(string)
    {
      /* does the string end? */
      if(*ps == '"')
        string--;
    }
    
    /* if we aren't in a string or comment */
    else
    {
      /* does a string or comment start? */
      if(*ps == '#')
        comment++;
      else if(*ps == '"')
        string++;
    }
    
    /* ok.. use string and comment to descide wether to keep the keychar */
    
    /* don't copy on comment */
    if(comment)
      continue;
    
    /* remove garbage if it's not in "..." */
    if(!string)
      if(!mconf_chars[(int)*ps])
        continue;
    
    /* cöpy */
    *pd++ = *ps;
  }
  
  if(string)
  {
    log_print(LOG_WARN, "unterminated string constant");
    return -1;
  }
  
  *pd = '\0';
  
  debug(1, "%s:\n<<<\n%s\n>>>",
        __func__, buffer);
  
  return 0;
}


/****************************************************************************
 * mconf_file_parse()
 * parse the clean buffer into the given struct mconf_change array
 ****************************************************************************/
int mconf_file_parse(char *buffer)
{
  char *keyword = NULL;
  
  /* parse values */
  int pos    = 0; // 0 = keyword expected, 1 = '=', 2 = value, 3 = ';'
  int string = 0; // 1 if we are in a string
  int line   = 1; // for nice stdout
  int count  = 0; // don't overflow mconf_chagelist
  
  /* points to the last line started parsing */  
  char *last;
  char *p;

  struct mconf_item *mciptr = NULL;
  
  /* parse the clean config buffer */
  for(p = buffer; *p != '\0'; p++)
  {    
    /* keep line number for nice stdout */
    if(*p == '\n')
    {
      line++;
      continue;
    }
    
    if(pos == 0)
    {
      if(isalpha(*p))
      {
        keyword = p;
        pos++;
      }
      else
        break;
    }
    else if(pos == 1)
    {
      if(*p == '=')
      {
        
        *p = '\0';
        
        if((mciptr = mconf_find_by_keyword(keyword)) == NULL)
        {
          log_print(LOG_WARN, "unknown keyword %s", keyword);
          return -1;
        }
        
        if(!mciptr->control & ~MCONF_FILE)
        {
          log_print(LOG_WARN, "keyword %s not allowed"
                    "in config files (ignoring)", mciptr->keyword);
          continue;
        }
        
        pos++;
      }
      else if(!isalpha(*p))
        break;
    }
    else if(pos == 2)
    {
      if(*p == '"')
        string++;
      else
      {
        mconf_change_add(mciptr, p);
        
        if(count >= MCONF_CHANGECOUNT)
        {
          log_print(LOG_WARN, "too many mconf items. ingoring from line %i", line);
          log_print(LOG_WARN, "to many mconf items. ingoring from line %i", line);
          *p = '\0';
        }

        pos++;
      }
    }
    else
    {
      if(string)
      {
        if(*p == '"')
        {
          *p = '\0';
          string--;
        }
      }
      else
      {
        if(*p == ';')
        {
          *p = '\0';
          pos = 0;
          last = p + 1;
        }
      }
    }
  }
  
  if(pos)
  {
    switch(pos)
    {
      case 0:
      log_print(LOG_WARN, "line %i: keyword missing", line);
      break;
      
      case 1:
      log_print(LOG_WARN, "line %i: '=' missing", line);
      break;
      
      case 2:
      log_print(LOG_WARN, "line %i: '=' missing", line);
      break;

      case 3:
      log_print(LOG_WARN, "line %i: ';' missing", line);
      break;
    }
    return 1;
  }
  
  return count;
}

/****************************************************************************
 * mconf_file()
 * loads a conffile
 ****************************************************************************/
int mconf_file(void)
{
  int ret;
  char *filename;
  int fd;
  
  char buffer[MCONF_BUFSIZE + 1];
  ssize_t buflen;
  
  
  /* choose right filename :) */
  if(mconf_filename)
    filename = strdup(bot_char_variables[CVAR_CONFIGFILE].var);
  else
    filename = DEFAULT_conffile;
  
  /* open configuration file */

  debug(1, "reading `%s' as conffile", filename);

  if((fd = open(filename, O_RDONLY)) == -1)
  {
    log_print(LOG_WARN, "couldn't load conffile %s: %s",
               filename, strerror(errno));
    return -1;
  }
    
  if((buflen = read(fd, buffer, MCONF_BUFSIZE)) == -1)
  {
    log_print(LOG_WARN, "conffile read error: %s",
               strerror(errno));
    return -1;
  }
  
  /* close config file */
  if(close(fd) == -1)
    log_print(LOG_WARN, "couldn't close conffile");

  if(buflen)
  {
    if(buflen == MCONF_BUFSIZE)
    {
      log_print(LOG_WARN, "conffile too long!");
      return -1;
    }
    else
      debug(1, "%i %i", buflen, MCONF_BUFSIZE);
    
    buffer[buflen] = '\0';
    
    mconf_change_clear();
    
    /* remove all garbage */
    if(mconf_file_garbage(buffer))
      return -1;
    
    /* parse the file */
    if(mconf_file_parse(buffer) == -1)
      return -1;
    
    /* do whats in the file */
    if((ret = mconf_change_do()))
      return ret;
  }
  
  log_print(LOG_INFO, "conffile loaded");
  
  return 0;
}


/*
 * FUNCTIONS TO PARSE COMMAND LINE OPTIONS
 */

/****************************************************************************
 * mconf_line()
 * parses the command line options
 ****************************************************************************/
int mconf_line(int argc, char *argv[])
{
  int i;
  struct mconf_item *ciptr = NULL;
  
  mconf_change_clear();
  
  for(i = 1; i < argc; i++)
  {
    if(argv[i][0] == '-')
    {
      /* "-<char>" syntax */
      if(strlen(argv[i]) == 2)
      {
        int j;
        
        if((ciptr = mconf_find_by_keychar(argv[i][1])) == NULL)
        {
          /* not found withing mconf_list.. what about aliaslist? */
          for(j = 0; j < MCONF_ALIASCOUNT ; j++)
            if(mconf_aliaslist[j].keychar == argv[i][1])
            {
              mconf_change_add(mconf_aliaslist[j].item,
                               mconf_aliaslist[j].para);
              break;
              /* don't use continue here */
            }
          
          /* don't make other stuff if we found an alias */
          if(j != MCONF_ALIASCOUNT)
            continue;
        }
      }
      
      /* "--<keyword>" syntax */
      else if(argv[i][1] == '-' && strlen(argv[i]) >= 3)
      {
        ciptr = mconf_find_by_keyword(argv[i] + 2);
      }
    }
    
    /* keyword not found? */
    if(ciptr == NULL)
    {
      log_print(LOG_WARN, "unknown option %s", argv[i]);
      
      /* print help page */
      mconf_conf_help(NULL, NULL);
      return -1;
    }
    
    /* keyword found */
    else
    {
      /* is this keyword allowed from command line? */
      if(!ciptr->control & ~MCONF_LINE)
      {
        log_print(LOG_WARN, "the keyword %s | %c is not allowd "
                  "from command line", ciptr->keychar, ciptr->keyword);
        continue;
      }
      
      if(argv[++i] == NULL)
      {
        log_print(LOG_WARN, "%c | %s needs the argument %s",
                   ciptr->keychar, ciptr->keyword, ciptr->parname);
        return -1;
      }

      mconf_change_add(ciptr, argv[i]);
    }
  }
  
  /* make the changes */
  return mconf_change_do();
}




/*
 * FUNCTIONS TO CONFIGURE MCONF ITSELFS
 */

/****************************************************************************
 * mconf_mconf_help()
 * print a small help page
 ****************************************************************************/
int mconf_conf_help(struct mconf_item *mci, char *para)
{
  int i;
  
  log_print(LOG_STATUS, "usage:\tserver [options]");
  log_print(LOG_STATUS, "available optins are:");
  
  for(i = 0; i < MCONF_LISTCOUNT; i++)
  {
    log_print(LOG_STATUS, "-%c | --%s",
              mconf_list[i].keychar, mconf_list[i].keyword);
    log_print(LOG_STATUS, "\t%s",
              mconf_list[i].helptxt);
  }
  
  for(i = 0; i < MCONF_ALIASCOUNT; i++)
  {
    log_print(LOG_STATUS, "-%c for --%s %s", mconf_aliaslist[i].keychar,
               mconf_aliaslist[i].item->keyword, mconf_aliaslist[i].para);
  }

  return 1;
}
