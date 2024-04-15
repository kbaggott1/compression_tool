#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freqtable.h"


char* cmpr_compress(char* fileContents) {
    FrequencyTable* pFt = freqtable_init(fileContents);

    for(int i = 0; i < pFt->size - 1; i++) {
        printf("HERE %c:%d\n", pFt->data[i], pFt->freq[i]);
    }
    
    freqtable_free(pFt);
    return NULL;
}