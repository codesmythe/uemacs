#ifndef _INPUT_H_
#define _INPUT_H_

#include "edef.h"

int mlyesno( char *prompt) ;
int mlreply( char *prompt, char *buf, int nbuf) ;
int mlreplyt( char *prompt, char *buf, int nbuf, int eolchar) ;
int ectoc( int c) ;
int ctoec( int c) ;
fn_t getname( void) ;
int tgetc( void) ;
int get1key( void) ;
int getcmd( void) ;
int getstring( char *prompt, char *buf, int nbuf, int eolchar) ;
void outstring( char *s) ;
void ostring( char *s) ;

#endif