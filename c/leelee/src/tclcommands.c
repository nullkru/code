#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <tcl.h>

#include "log.h"
#include "tclcommands.h"

int RandomCmd(ClientData clientData, Tcl_Interp *interp,
	      int argc, const char *argv[])
{
   int random, error,
       limit = 0;
   
   if (argc > 2)
     {
	interp->result = "Usage: random ?range?";
	return TCL_ERROR;
     }
   else if (argc == 2)
     {
	error = Tcl_GetInt(interp, argv[1], &limit);
	if (error != TCL_OK)
	  return error;
     }
   srand(time(NULL));
   random = rand();
   if (limit != 0)
     random = random % limit;
   sprintf(interp->result, "%d", random);
   return TCL_OK;
}

int RandomObjCmd(ClientData clientData, Tcl_Interp *interp,
		 int objc, Tcl_Obj * const objv[])
{
   Tcl_Obj *resultPtr;
   int random, error,
       limit = 0;
   
   if (objc > 2)
     {
	Tcl_AppendResult(interp, "Usage: random ?range?", NULL);
	return TCL_ERROR;
     }
   else if(objc == 2)
     {
	error = Tcl_GetIntFromObj(interp, objv[1], &limit);
	if(error != TCL_OK)
	  return error;
     }
   srand(time(NULL));
   random = rand();
   if (limit != 0)
     random = random % limit;
   resultPtr = Tcl_GetObjResult(interp);
   Tcl_SetIntObj(resultPtr, random);
   return TCL_OK;
}
