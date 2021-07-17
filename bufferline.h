#ifndef _BUFFER_LINE_H_
#define _BUFFER_LINE_H_

#include "bdef.h"
#include <string.h>

typedef struct _BUFFERLINE {
    char *buffer;
    size_t gap_size;
    size_t gap_left;
    size_t gap_right;
    size_t size;
} BUFFERLINE;

BUFFERLINE *bm_flnew(void);
void bm_flfree(BUFFERLINE *pLine);

int bm_flgrowbuf(BUFFERLINE *pLine);
int bm_flgrowgap(BUFFERLINE *pLine, size_t pos);

size_t bm_fllen(BUFFERLINE *pLine);

void bm_flmvl(BUFFERLINE *pLine, size_t pos);
void bm_flmvr(BUFFERLINE *pLine, size_t pos);
void bm_flmv(BUFFERLINE *pLine, size_t pos);

int bm_flinsert(BUFFERLINE *pLine, char *sz_in, size_t pos);
char bm_flgetc(BUFFERLINE *pLine, size_t pos);

void bm_fldump(BUFFERLINE *pLine);
#endif