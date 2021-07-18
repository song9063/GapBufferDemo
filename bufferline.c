/*
References:
 https://www.geeksforgeeks.org/gap-buffer-data-structure/
 https://nullprogram.com/blog/2017/09/07/
*/

#include <stdio.h>
#include <stdlib.h>

#include "bufferline.h"

#define GAP_GROWING_SIZE 4
#define BUFFER_GROWING_SIZE (GAP_GROWING_SIZE*2)

BUFFERLINE *bm_flnew(void){
    BUFFERLINE *pLine = (BUFFERLINE*)malloc(sizeof(BUFFERLINE));
    if(pLine == NULL) return NULL;
    pLine->buffer = (wchar_t*)malloc(2 * sizeof(wchar_t));
    pLine->buffer[0] = 0x00;
    pLine->buffer[1] = 0x00;
    pLine->gap_size = 2;
    pLine->gap_left = 0;
    pLine->gap_right = 1;
    pLine->size = 2;

    pLine->p_prev = NULL;
    pLine->p_next = NULL;
    
    return pLine;
}
void bm_flfree(BUFFERLINE *pLine){
    if(pLine->buffer != NULL){
        free(pLine->buffer);
        pLine->buffer = NULL;
    }

    if(pLine->p_prev != NULL)
        pLine->p_prev->p_next = NULL;
    
    if(pLine->p_next != NULL){
        pLine->p_next->p_prev = NULL;
        if(pLine->p_prev != NULL){
            pLine->p_prev->p_next = pLine->p_next;
            pLine->p_next->p_prev = pLine->p_prev;
        }
    }

    free(pLine);
    pLine = NULL;
}
int bm_flgrowbuf(BUFFERLINE *pLine){
    size_t i;
    wchar_t *btmp;
    btmp = (wchar_t *)realloc(pLine->buffer, (BUFFER_GROWING_SIZE * sizeof(wchar_t)) + (sizeof(wchar_t) * pLine->size));
    if(btmp == NULL){
        return FALSE;
    }
    pLine->buffer = btmp;
    for(i=pLine->size; i<pLine->size + BUFFER_GROWING_SIZE; i++)
        pLine->buffer[i] = 0x00;
    
    pLine->size += BUFFER_GROWING_SIZE;
    return TRUE;
}
int bm_flgrowgap(BUFFERLINE *pLine, size_t pos){
    size_t i;
    wchar_t tmp[pLine->size - pos];
    for(i=pos; i<pLine->size; i++)
        tmp[i-pos] = bm_flgetc(pLine, i);

    for(i=0; i<GAP_GROWING_SIZE; i++)
        pLine->buffer[i+pos] = 0x00;

    for(i=0; i<wcslen(tmp); i++)
        pLine->buffer[i+pos+GAP_GROWING_SIZE] = tmp[i];

    pLine->gap_right = pos + GAP_GROWING_SIZE -1;
    pLine->gap_size = pLine->gap_right-pLine->gap_left+1;

    return TRUE;
}
void bm_fldump(BUFFERLINE *pLine){
    size_t i;
    wchar_t c;
    i = bm_fllen(pLine);
    printf("\n\nLen: %ld, Size: %ld, Gap Size:%ld, Left: %ld, Right: %ld\n > ",
        i, pLine->size, pLine->gap_size, pLine->gap_left, pLine->gap_right);
    for(i=0; i<pLine->size; i++){
        c = pLine->buffer[i];
        putchar(c == 0x00 ? '_' : c);
    }
    putchar('\n');
}

size_t bm_fllen(BUFFERLINE *pLine){
    size_t len = 0;
    wchar_t c;
    size_t i = 0;
    while(i < pLine->size){
        c = pLine->buffer[i];
        if(c == 0x00 && i > pLine->size)
            break;
        
        if(c != 0x00)
            len++;
        i++;
    }
    return len;
}

/* Move left */
void bm_flmvl(BUFFERLINE *pLine, size_t pos){
    while(pos < pLine->gap_left){
        pLine->gap_left--;
        pLine->gap_right--;
        pLine->buffer[pLine->gap_right+1] = pLine->buffer[pLine->gap_left];
        pLine->buffer[pLine->gap_left] = 0x00;
    }
}

/* Move right */
void bm_flmvr(BUFFERLINE *pLine, size_t pos){
    while(pLine->gap_left < pos){
        pLine->gap_left++;
        pLine->gap_right++;
        pLine->buffer[pLine->gap_left-1] = pLine->buffer[pLine->gap_right];
        pLine->buffer[pLine->gap_right] = 0x00;
    }
}

/* Move gap */
void bm_flmv(BUFFERLINE *pLine, size_t pos){
    if(pos < pLine->gap_left)
        bm_flmvl(pLine, pos);
    else
        bm_flmvr(pLine, pos);
}

int bm_flinsert(BUFFERLINE *pLine, wchar_t *sz_in, const size_t pos){
    size_t len, buflen;
    size_t i;
    if(sz_in == NULL || pos < 0) return FALSE;
    len=wcslen(sz_in);
    i=0;

    if(pos != pLine->gap_left)
        bm_flmv(pLine, pos);
    
    buflen = bm_fllen(pLine);
    while(i < len){
        if(pLine->gap_right == pLine->gap_left){
            if(pLine->size <= (buflen+GAP_GROWING_SIZE))
                bm_flgrowbuf(pLine);
            bm_flgrowgap(pLine, pLine->gap_left);
        }

        pLine->buffer[pLine->gap_left] = sz_in[i];
        pLine->gap_left++;
        pLine->gap_size = pLine->gap_right - pLine->gap_left + 1;
        i++;
        buflen = bm_fllen(pLine);
    }
    
    return TRUE;
}

wchar_t bm_flgetc(BUFFERLINE *pLine, size_t pos){
    size_t len;
    if(pos < 0)
        return 0x00;

    if(pos < pLine->gap_left)
        return pLine->buffer[pos];

    len = bm_fllen(pLine);
    pos = pLine->gap_right - pLine->gap_left + pos + 1;
    if(pos >= pLine->size)
        return 0x00;

    return pLine->buffer[pos];
}