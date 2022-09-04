/*	vt52.c
 *
 * The routines in this file
 * provide support for VT52 style terminals
 * over a serial line. The serial I/O services are
 * provided by routines in "termio.c". It compiles
 * into nothing if not a VT52 style device. The
 * bell on the VT52 is terrible, so the "beep"
 * routine is conditionalized on defining BEL.
 *
 *	modified by Petri Kutvonen
 */

#define	termdef	1		/* don't define "term" external */

#include        <stdio.h>
#include        <string.h>
#include        <stdarg.h>
#include        <mint/osbind.h>
#include        "debug.h"
#include        "estruct.h"
#include        "terminal.h"

#if     VT52

#define NROW    24		/* Screen size.                 */
#define NCOL    80		/* Edit if you want to.         */
#define	MARGIN	8		/* size of minimim margin and   */
#define	SCRSIZ	64		/* scroll size for extended lines */
#define	NPAUSE	100		/* # times thru update to pause */
#define BIAS    0x20		/* Origin 0 coordinate bias.    */
#define ESC     0x1B		/* ESC character.               */
#define BEL     0x07		/* ascii bell character         */

#define BC_CON  2

extern void ttopen(void);		/* Forward references.          */
extern void ttflush(void);
extern void ttclose(void);
static void vt52move(int, int);
static void vt52eeol(void);
static void vt52eeop(void);
static void vt52beep(void);
static void vt52open(void);
static int vt52cres(char *);
static void vt52kopen(void);
static void vt52kclose(void);

static int stputc(unicode_t c);
static int stgetc(void);
static void st52rev(int);


#if COLOR
extern int vt52fcol();
extern int vt52bcol();
#endif

boolean eolexist = TRUE ;       /* does clear to EOL exist?     */
boolean revexist = TRUE ;      /* does reverse video exist?    */
boolean sgarbf = TRUE ;         /* State of screen unknown      */

char sres[ 16] ;




/*
 * Dispatch table.
 * All the hard fields just point into the terminal I/O code.
 */
struct terminal term = {
	NROW,
	NCOL,
	NROW,
	NROW,
	NCOL,
	NCOL,
	MARGIN,
	SCRSIZ,
	NPAUSE,
	&vt52open,
	&ttclose,
	&vt52kopen,
	&vt52kclose,
	&stgetc,
	&stputc,
	&ttflush,
	&vt52move,
	&vt52eeol,
	&vt52eeop,
	&vt52beep,
	&st52rev,
	&vt52cres
#if	COLOR
	    , &vt52fcol,
	&vt52bcol
#endif
#if	SCROLLCODE
	    , NULL
#endif
};

static int stputc(unicode_t c) {
    /* No unicode support here. */
    Bconout(BC_CON, (int)(c & 0xff));
    return 0;
}

static int stgetc(void) {
    return Crawcin() & 0xff;
}

static void vt52move(int row, int col)
{
	stputc(ESC);
	stputc('Y');
	stputc(row + BIAS);
	stputc(col + BIAS);
}

static void vt52eeol(void)
{
	stputc(ESC);
	stputc('K');
}

static void vt52eeop(void)
{
	stputc(ESC);
	stputc('J');
}

/*
 * Set the reverse video state.
 * TRUE = reverse video, FALSE = normal video.
 */
static void st52rev(int status)
{
    stputc(ESC);
    stputc(status ? 'p' : 'q');
}

static int vt52cres(char *ch)
{				/* change screen resolution - (not here though) */
	return TRUE;
}

#if	COLOR
vt52fcol()
{				/* set the forground color [NOT IMPLIMENTED] */
}

vt52bcol()
{				/* set the background color [NOT IMPLIMENTED] */
}
#endif

void vt52beep(void)
{
#ifdef  BEL
	stputc(BEL);
	ttflush();
#endif
}

void vt52open(void)
{
#if     V7 | BSD
	char *cp;
	char *getenv();

	if ((cp = getenv("TERM")) == NULL) {
		puts("Shell variable TERM not defined!");
		exit(1);
	}
	if (strcmp(cp, "vt52") != 0 && strcmp(cp, "z19") != 0) {
		puts("Terminal type not 'vt52'or 'z19' !");
		exit(1);
	}
#endif
    strcpy(sres, "TOS");
    revexist = TRUE;
    ttopen();
}

void vt52kopen(void)
{
}

void vt52kclose(void)
{
}

/*
void pr(const char *s) {
    for (const char *p = s; *p; p++) {
        Bconout(1, *p);
    }
}

void rsprintf(const char *fmt, ...) {
    static char  buffer[1024];
    va_list args;
    va_start(args,fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);

    pr(buffer);
}

*/

#endif
