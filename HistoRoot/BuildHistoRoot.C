//	BuildHistoRoot.C -- build HistoRoot library
/*
 *	This Root macro will build the HistoRoot library from the macro
 *	HistoRoot.C.
 *
 *	Note the compiled library runs ~100 times faster than the macro.
 *
 *	USAGE:
 *		root -l -n BuildHistoRoot.C
 *		(-l => omit splash, -n => don't execute logon/logoff macros)
 */

void BuildHistoRoot()
{
	// compile the macro: keep it, force compile, Optimize
	int retval=gSystem->CompileMacro("HistoRoot.C","kfO");
	if(retval == 0) {
		fprintf(stderr,
			"***********************************\n"
			"*** Compiling the macro failed. ***\n"
			"***********************************\n"
			);
		gSystem->Exec("rm -f HistoRoot*.so");
	} else {
		fprintf(stderr,"Building the HistoRoot library succeeded.\n");
	}

	gApplication->Terminate(1);
}
