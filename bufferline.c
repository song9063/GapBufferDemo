/*
References:
 https://www.geeksforgeeks.org/gap-buffer-data-structure/
 https://nullprogram.com/blog/2017/09/07/
*/

#include <stdio.h>
#include <stdlib.h>

#include "bufferline.h"

BUFFERLINE *bm_flnew(size_t buff_size, size_t gap_size){
    BUFFERLINE *pLine = (BUFFERLINE*)malloc(sizeof(BUFFERLINE));
    if(pLine == NULL) return NULL;
    memset(pLine->buffer, 0x00, buff_size);
    pLine->gap_size = gap_size;
    pLine->gap_left = 0;
    pLine->gap_right = pLine->gap_size - pLine->gap_left-1;
    pLine->size = buff_size;
    
    return pLine;
}
void bm_flfree(BUFFERLINE *pLine){
    free(pLine);
    pLine = NULL;
}
void bm_fldump(BUFFERLINE *pLine){
    size_t i;
    char c;
    i = bm_fllen(pLine);
    printf("\n\nLen: %ld, Gap Size:%ld, Left: %ld, Right: %ld\n",
        i, pLine->gap_size, pLine->gap_left, pLine->gap_right);
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
    if(pos < pLine->gap_left){
        bm_flmvl(pLine, pos);
    }else{
        bm_flmvr(pLine, pos);
    }
}

void bm_flinsert(BUFFERLINE *pLine, char *sz_in, size_t pos){
    size_t len=strlen(sz_in);
    size_t i=0;

    if(pos != pLine->gap_left){
        bm_flmv(pLine, pos);
    }

    while(i < len){
        if(pLine->gap_right == pLine->gap_left){
            // Todo. growing
            
            break;
        }

        pLine->buffer[pLine->gap_left] = sz_in[i];
        pLine->gap_left++;
        i++;
        pos++;
    }
}

char bm_flgetc(BUFFERLINE *pLine, size_t pos){
    size_t len;
    if(pos < 0){
        return 0x00;
    }
    if(pos < pLine->gap_left){
        return pLine->buffer[pos];
    }

    len = bm_fllen(pLine);
    pos = pLine->gap_right - pLine->gap_left + pos + 1;
    if(pos > len){
        return 0x00;
    }

    return pLine->buffer[pos];
}