#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bufferline.h"

int main(){
    size_t i;
    BUFFERLINE *pLine = bm_flnew();
    if(pLine == NULL){
        printf("Error!");
        exit(-1);
    }

    printf("Hello buffer\n");

    bm_fldump(pLine);

    bm_flinsert(pLine, L"Hello", 0);
    bm_fldump(pLine);

    bm_flinsert(pLine, L"Busang", 5);
    bm_fldump(pLine);

    bm_flinsert(pLine, L"12", 0);
    bm_fldump(pLine);

    bm_flinsert(pLine, L"3456", 0);
    bm_fldump(pLine);

    bm_flinsert(pLine, L"Song", 17);
    bm_fldump(pLine);

    bm_flprint(pLine);

    printf("\n\n\nMove!\n");
    for(i=0; i<3; i++){
        bm_flmv(pLine, i);
        bm_fldump(pLine);
    }

    printf("\n\n\nMove to end!\n");
    i = bm_fllen(pLine);
    bm_flmv(pLine, i);
    bm_fldump(pLine);
    
    bm_flfree(pLine);
    return 0;
}