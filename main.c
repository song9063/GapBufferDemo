#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bufferline.h"

int main(){
    size_t i;
    size_t len;
    char c;
    BUFFERLINE *pLine = bm_flnew();
    if(pLine == NULL){
        printf("Error!");
        exit(-1);
    }

    printf("Hello buffer\n");

    bm_fldump(pLine);

    bm_flinsert(pLine, "Hello", 0);
    bm_fldump(pLine);
    
    bm_flinsert(pLine, "Busang", 5);
    bm_fldump(pLine);

    bm_flinsert(pLine, "O", 0);
    bm_fldump(pLine);

    bm_flinsert(pLine, "PPP", 0);
    bm_fldump(pLine);

    printf("Hello\n");

    i = 0;
    len = bm_fllen(pLine);
    while(i<len){
        c = bm_flgetc(pLine, i);
        if(c == 0x00)
            break;
        printf("\tCharacter at %ld: %c\n", i, c);
        i++;
    }

    bm_flfree(pLine);
    return 0;
}