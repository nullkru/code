#ifndef TCLCOMMANDS_H
#define TCLCOMMANDS_H

int RandomCmd(ClientData clientData, Tcl_Interp *interp, int argc, const char *argv[]);
int RandomObjCmd(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj * const objv[]);
  
#endif
