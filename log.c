#include "log.h"

static void logdump( const char *buf, ...) {
}

void (*logwrite)( const char *, ...) = logdump ;

static boolean logit( boolean retcode, boolean beep_f, const char *buf, ...) {
	return retcode ;
}

boolean (*logger)( boolean, boolean, const char *, ...) = logit ;

/*
 * tell the user that this command is illegal while we are in
 * VIEW (read-only) mode
 */
boolean rdonly( void) {
	return logger( FALSE, TRUE, "(Key illegal in VIEW mode)");
}



boolean resterr( void) {
	return logger( FALSE, TRUE, "(That command is RESTRICTED)");
}


