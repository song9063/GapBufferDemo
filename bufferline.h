#ifndef _BUFFER_LINE_H_
#define _BUFFER_LINE_H_

#include "bdef.h"
#include <string.h>
#include <wchar.h>

typedef struct _BUFFERLINE {
    wchar_t *buffer;
    size_t gap_size;
    size_t gap_left;
    size_t gap_right;
    size_t size;
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


/* Move gap to left */
void bm_flmvl(BUFFERLINE *pLine, size_t pos);

/* Move gap right */
void bm_flmvr(BUFFERLINE *pLine, size_t pos);

/* Move gap buffer */
void bm_flmv(BUFFERLINE *pLine, size_t pos);


/* Insert text to gap buffer */
int bm_flinsert(BUFFERLINE *pLine, wchar_t *sz_in, size_t pos);

/* Retrive character at */
wchar_t bm_flgetc(BUFFERLINE *pLine, size_t pos);


/* Dump buffer for debug */
void bm_fldump(BUFFERLINE *pLine);

#endif