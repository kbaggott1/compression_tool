#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ASCII_SIZE 128


typedef struct {
    char* data;
    int* freq;
    int size;
} FrequencyTable;


void add_char(FrequencyTable* pFt, char c) {
    for(int i = 0; i < ASCII_SIZE; i++) {

        if(pFt->data[i] == c) {
            pFt->freq[i]++;
            return;
        }

        if(pFt->data[i] == '\0') {
            pFt->data[i] = c;
            pFt->freq[i] = 1;
            return;
        }
    }
}

void swap(int* a, int* b, char* ca, char* cb) {
    int temp = *a;
    *a = *b;
    *b = temp;

    char ctemp = *ca;
    *ca = *cb;
    *cb = ctemp;
}

int partition(FrequencyTable* pFt, int low, int high) {
    int pivot = pFt->freq[high];
    int i = (low - 1);
  
    for (int j = low; j < high; j++) {
        if (pFt->freq[j] < pivot) {
            i++;
            swap(&pFt->freq[i], &pFt->freq[j], &pFt->data[i], &pFt->data[j]);
        }
    }
  
    swap(&pFt->freq[i + 1], &pFt->freq[high], &pFt->data[i + 1], &pFt->data[high]);
    return (i + 1);
}

void quick_sort(FrequencyTable* pFt, int low, int high) {
    if (low < high) {
        int pi = partition(pFt, low, high);
  
        quick_sort(pFt, low, pi - 1);
        quick_sort(pFt, pi + 1, high);
    }
}

void freqtable_free(FrequencyTable* pFt) {
    free(pFt->data);
    free(pFt->freq);
    free(pFt);
}

FrequencyTable* freqtable_init(char* fileContents) {
    FrequencyTable* pFt = malloc(sizeof(FrequencyTable));

    if(pFt == NULL) {
        return NULL;
    }

    pFt->data = malloc(ASCII_SIZE);
    pFt->freq = malloc(ASCII_SIZE * sizeof(int));

    memset(pFt->data, 0, ASCII_SIZE * sizeof(char));
    memset(pFt->freq, 0, ASCII_SIZE * sizeof(int));

    for(int i = 0; i < strlen(fileContents); i++) {
        //printf("%c", fileContents[i]);
        add_char(pFt, fileContents[i]);
    }


    quick_sort(pFt, 0, ASCII_SIZE - 1);

    //shrink
    int arrStart;
    int newSize;
    for(int i = 0; i < ASCII_SIZE - 1; i++) {
        if(pFt->freq[i] != 0) {
            arrStart = i;
            newSize = ASCII_SIZE + 1 - i;
            break;
        }
    }

    char* dataTemp = malloc(newSize * sizeof(char));
    int* freqTemp = malloc(newSize * sizeof(int));

    if(dataTemp == NULL || freqTemp == NULL) {
        return NULL;
    }

    for(int i = 0; i < newSize - 1; i++) {
        dataTemp[i] = pFt->data[i + arrStart];
        freqTemp[i] = pFt->freq[i + arrStart];
    }

    free(pFt->data);
    free(pFt->freq);

    pFt->data = dataTemp;
    pFt->freq = freqTemp;
    pFt->size = newSize;

    return pFt;
}