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
    pLine->buffer = (char*)malloc(1);
    pLine->gap_size = 1;
    pLine->gap_left = 0;
    pLine->gap_right = pLine->gap_size - pLine->gap_left-1;
    pLine->size = 1;
    
    return pLine;
}
void bm_flfree(BUFFERLINE *pLine){
    if(pLine->buffer != NULL){
        free(pLine->buffer);
        pLine->buffer = NULL;
    }
    free(pLine);
    pLine = NULL;
}
int bm_flgrowbuf(BUFFERLINE *pLine){
    size_t i;
    char *buffCopy;
    buffCopy = pLine->buffer;
    printf("Add buffer space %ld -> %ld", pLine->size, pLine->size+BUFFER_GROWING_SIZE);
    pLine->buffer = (char *)realloc(pLine->buffer, BUFFER_GROWING_SIZE * sizeof(char));
    if(pLine->buffer == NULL){
        free(buffCopy);
        /*bm_flfree(pLine);*/
        return FALSE;            
    }
    for(i=pLine->size; i<pLine->size + BUFFER_GROWING_SIZE; i++){
        pLine->buffer[i] = 0x00;
    }
    pLine->size += BUFFER_GROWING_SIZE;
    return TRUE;
}
int bm_flgrowgap(BUFFERLINE *pLine, size_t pos){
    size_t i;
    char tmp[pLine->size];
    for(i=pos; i<pLine->size; i++)
        tmp[i-pos] = pLine->buffer[i];

    for(i=0; i<GAP_GROWING_SIZE; i++)
        pLine->buffer[i+pos] = 0x00;

    for(i=0; i<pos + GAP_GROWING_SIZE; i++)
        pLine->buffer[i+pos+GAP_GROWING_SIZE] = tmp[i];

    pLine->gap_right += GAP_GROWING_SIZE;
    pLine->gap_size = pLine->gap_right-pLine->gap_left;

    return TRUE;
}
void bm_fldump(BUFFERLINE *pLine){
    size_t i;
    char c;
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
    char c;
    size_t i = 0;
    while(i < pLine->size){
        c = pLine->buffer[i];
        if(c == 0x00 && i > pLine->gap_right)
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

int bm_flinsert(BUFFERLINE *pLine, char *sz_in, size_t pos){
    size_t len;
    size_t i;
    if(sz_in == NULL) return FALSE;
    len=strlen(sz_in);
    i=0;

    if(pos != pLine->gap_left)
        bm_flmv(pLine, pos);

    while(i < len){

        if(pLine->gap_right == pLine->gap_left){
            if(pLine->size < (pLine->gap_right+GAP_GROWING_SIZE)){
                bm_flgrowbuf(pLine);
            }
            bm_flgrowgap(pLine, pos);
        }
            

        pLine->buffer[pLine->gap_left] = sz_in[i];
        pLine->gap_left++;
        i++;
        pos++;
    }
    return TRUE;
}

char bm_flgetc(BUFFERLINE *pLine, size_t pos){
    size_t len;
    if(pos < 0)
        return 0x00;

    if(pos < pLine->gap_left)
        return pLine->buffer[pos];

    len = bm_fllen(pLine);
    pos = pLine->gap_right - pLine->gap_left + pos + 1;
    if(pos > len)
        return 0x00;

    return pLine->buffer[pos];
}