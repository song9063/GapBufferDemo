#ifndef _BUFFER_LINE_H_
#define _BUFFER_LINE_H_

#include "bdef.h"
#include <string.h>
#include <wchar.h>

/*
* Todo: caching for length
*/
typedef struct _BUFFERLINE {
    wchar_t *buffer;
    size_t gap_size;
    size_t gap_left;
    size_t gap_right;
    size_t size;

    struct _BUFFERLINE *p_prev;
    struct _BUFFERLINE *p_next;
} BUFFERLINE;

/* Make new instance */
BUFFERLINE *bm_flnew(void);

/* Destroy */
void bm_flfree(BUFFERLINE *pLine);

/* Grow up buffer */
int bm_flgrowbuf(BUFFERLINE *pLine);

/* Grow up gap buffer */
int bm_flgrowgap(BUFFERLINE *pLine, size_t pos);


/* Calculate length of string without gap */
size_t bm_fllen(BUFFERLINE *pLine);

/* has one more characters before gap_left? */
int bm_flhascl(BUFFERLINE *pLine);

/* has one more characters before gap_left? */
int bm_flhascr(BUFFERLINE *pLine);

/* Move gap to left */
void bm_flmvl(BUFFERLINE *pLine, size_t pos);

/* Move gap right */
void bm_flmvr(BUFFERLINE *pLine, size_t pos);

/* Move gap buffer */
void bm_flmv(BUFFERLINE *pLine, size_t pos);


/* Insert text to gap buffer */
int bm_flinsert(BUFFERLINE *pLine, wchar_t *sz_in, const size_t pos);

/* 
* Delete one character before gap_left(Backspace) 
* It will return TRUE if gap_left is greater than 0
* otherwise will return FALSE.
*/
int bm_flrml(BUFFERLINE *pLine);

/* 
* Delete one character after gap_right(Del) 
* It will return TRUE if exists one or more characters after gap_right.
* otherwise will return FALSE.
*/
int bm_flrmr(BUFFERLINE *pLine);

/* Retrive character at */
wchar_t bm_flgetc(BUFFERLINE *pLine, size_t pos);


/* Dump buffer for debug */
void bm_fldump(BUFFERLINE *pLine);
void bm_flprint(BUFFERLINE *pLine);

#endif