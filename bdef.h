#ifndef _B_DEFINE_H_
#define _B_DEFINE_H_
#ifdef	FALSE
#undef	FALSE
#endif
#ifdef	TRUE
#undef	TRUE
#endif

#define FALSE   0		/* False, no, bad, etc.         */
#define TRUE    1		/* True, yes, good, etc.        */
#define ABORT   2		/* Death, ^G, abort, etc.       */
#endif