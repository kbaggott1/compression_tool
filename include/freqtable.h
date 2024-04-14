#ifndef FREQTABLE_H
#define FREQTABLE_H
#define ASCII_SIZE 128

typedef struct {
    char* data;
    int* freq;
    int size;
} FrequencyTable;

FrequencyTable* freqtable_init(char* fileContents);

#endif