#ifndef _BUFFER_LINE_
#define _BUFFER_LINE_

#include <string.h>

#define DEFAULT_BUFFERSIZE 30

typedef struct _BUFFERLINE {
    char buffer[DEFAULT_BUFFERSIZE];
    size_t gap_size;
    size_t gap_left;
    size_t gap_right;
    size_t size;
} BUFFERLINE;

BUFFERLINE *bm_flnew(size_t buff_size, size_t gap_size);
void bm_flfree(BUFFERLINE *pLine);
void bm_fldump(BUFFERLINE *pLine);

size_t bm_fllen(BUFFERLINE *pLine);

void bm_flmvl(BUFFERLINE *pLine, size_t pos);
void bm_flmvr(BUFFERLINE *pLine, size_t pos);
void bm_flmv(BUFFERLINE *pLine, size_t pos);

void bm_flinsert(BUFFERLINE *pLine, char *sz_in, size_t pos);
char bm_flgetc(BUFFERLINE *pLine, size_t pos);
#endif