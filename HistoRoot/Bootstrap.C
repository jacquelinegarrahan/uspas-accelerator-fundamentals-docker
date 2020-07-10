//	Bootstrap.C -- bootstrap HistoRoot
/*
	This Root macro attempts to load the HistoRoot library; if that fails
	it warns the user and loads the macro. Then it creates the
	HistoRootWindow to run the HistoRoot application.

	The environment variable HISTOROOT_LIB must point to the library 
	(setup by the calling shell script).

	USAGE:
		root -l -n Bootstrap.C

	Note the HistoRoot program will use the environment variable ARGS
	as a list of files to open.
*/

#include <stdlib.h>
#include <TApplication.h>

void Bootstrap()
{
	printf("Bootstrap() entered.\n");

	const char *lib = getenv("HISTOROOT_LIB");
	if(!lib) {
		fprintf(stderr,"INTERNAL ERROR -- HISTOROOT_LIB not set\n");
		gApplication->Terminate(1);
	}

	int retval = gSystem->Load(lib);
	if(retval != 0) {
		fprintf(stderr,
			"*********************************************\n"
			"*** Loading the compiled library failed,  ***\n"
			"*** So we will run the macro instead.     ***\n"
			"*** This will work fine, but can be       ***\n"
			"*** ~100 times slower on large files.     ***\n"
			"*** See the documentation for how to      ***\n"
			"*** compile the macro to speed it up.     ***\n"
			"*********************************************\n"
			);
		gROOT->ProcessLineSync(".L HistoRoot.C");
	}

	new HistoRootWindow();
}
