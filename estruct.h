/* estruct.h -- */

#ifndef _ESTRUCT_H_
#define _ESTRUCT_H_

/*      ESTRUCT.H
 *
 *      Structure and preprocessor defines
 *
 *	written by Dave G. Conroy
 *	modified by Steve Wilhite, George Jones
 *      substantially modified by Daniel Lawrence
 *	modified by Petri Kutvonen
 */


#ifdef	MSDOS
#undef	MSDOS
#endif

/* Machine/OS definitions. */

#if defined(AUTOCONF) || defined(BSD) || defined(SYSV) || defined(__atarist__)

/* Make an intelligent guess about the target system. */

#if defined(BSD) || defined(sun) || defined(ultrix) || defined(__osf__)
#ifndef BSD
#define BSD 1 /* Berkeley UNIX */
#endif
#else
#define	BSD 0
#endif

#if defined(SVR4) || defined(__linux__)	/* ex. SunOS 5.3 */
#define SVR4 1
#define SYSV 1
#undef BSD
#endif

#if defined(SYSV) || defined(u3b2) || defined(_AIX) || (defined(i386) && defined(unix)) || (defined( __unix__) && !defined(__atarist__))
#define	USG 1 /* System V UNIX */
#else
#define	USG 0
#endif

#else
# define BSD	0		/* UNIX BSD 4.2 and ULTRIX      */
# define USG	1		/* UNIX system V                */
#endif	/*autoconf */

#define MSDOS	0		/* MS-DOS                       */

/*	Compiler definitions	*/
#ifndef	AUTOCONF
# define UNIX	1		/* a random UNIX compiler */
#else
# define UNIX	(BSD | USG)
#endif	/*autoconf */

#ifndef AUTOCONF
# define ATARIST 0
#else
# define ATARIST __atarist__
#endif

/*	Debugging options	*/

#define	RAMSIZE	0		/* dynamic RAM memory usage tracking */
#if RAMSIZE
#define	RAMSHOW	1		/* auto dynamic RAM reporting */
#endif

#ifndef	AUTOCONF

/*   Special keyboard definitions            */

#define VT220	0		/* Use keypad escapes P.K.      */
#define VT100   0		/* Handle VT100 style keypad.   */

/*	Terminal Output definitions		*/

#define ANSI    0		/* ANSI escape sequences        */
#define VT52    0		/* VT52 terminal (Zenith).      */
#define TERMCAP 0		/* Use TERMCAP                  */
#define	IBMPC	1		/* IBM-PC CGA/MONO/EGA driver   */

#else

#define	VT220	UNIX
#define	VT100	0

#define	ANSI	0
#define	VT52	ATARIST
#define	TERMCAP	UNIX
#define	IBMPC	MSDOS

#endif /* Autoconf. */

/*	Configuration options	*/

#define	CFENCE	1  /* fench matching in CMODE                      */
#define	VISMAC	0  /* update display during keyboard macros        */

#ifndef	AUTOCONF

#define	COLOR	1  /* color commands and windows                   */
#define	FILOCK	0  /* file locking under unix BSD 4.2              */

#else

#define	COLOR	MSDOS
#ifdef  SVR4
#define FILOCK  1
#else
#define	FILOCK	BSD
#endif

#endif /* Autoconf. */

#define	CLEAN	0  /* de-alloc memory on exit                      */

#ifndef	AUTOCONF
# define XONXOFF	0  /* don't disable XON-XOFF flow control P.K.     */
#else
# define XONXOFF	UNIX
#endif /* Autoconf. */

#define	PKCODE	1      /* include my extensions P.K., define always    */
#define SCROLLCODE 1   /* scrolling code P.K.                          */

/* Define some ability flags. */

#if	IBMPC
#define	MEMMAP	1
#else
#define	MEMMAP	0
#endif

#if	USG | BSD
# define ENVFUNC	1
#else
# define ENVFUNC	0
#endif

/*	Dynamic RAM tracking and reporting redefinitions	*/

#if	RAMSIZE
#include <stdlib.h>
void *allocate( size_t size) ;
void release( void *ptr) ;
#define	malloc	allocate
#define	free	release
#endif

/*	De-allocate memory always on exit (if the operating system or
	main program can not
*/

#if	CLEAN
#define	exit(a)	cexit(a)

void cexit( int status) ;
#endif

#endif

/* end of estruct.h */
