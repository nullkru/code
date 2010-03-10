
#ifndef TCL_H
#define TCL_H

void init_tcl(void);
int execute_tcl_script(const char *file);
void fini_tcl();
int find_tcl_scripts(char *directory);
  
#endif
