#include <stdio.h>

typedef struct {
    unsigned char buffer;
    int bitCount;
    FILE *file;
} BitWriter;

int bit_write_to_file(char* filePath, char* fileContent);