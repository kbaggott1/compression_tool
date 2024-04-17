#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 8

typedef struct {
    unsigned char buffer;
    int bitCount;
    FILE *file;
} BitWriter;

void bit_writer_init(BitWriter *writer, FILE *outputFile) {
    writer->buffer = 0;
    writer->bitCount = 0;
    writer->file = outputFile;
}

void write_bit(BitWriter *writer, int bit) {
    if (bit) {
        writer->buffer |= (1 << (7 - writer->bitCount));
    }
    writer->bitCount++;

    if (writer->bitCount == BUFFER_SIZE) {
        fputc(writer->buffer, writer->file);
        writer->buffer = 0;
        writer->bitCount = 0;
    }
}

void flush_bits(BitWriter *writer) {
    if (writer->bitCount > 0) {
        fputc(writer->buffer, writer->file);
        writer->buffer = 0;
        writer->bitCount = 0;
    }
}

int bit_write_to_file(char* filePath, char* fileContent) {
    FILE* file = fopen(filePath, "wb");

    if(file == NULL) {
        perror("Could not write to filepath");
        return -1;
    }

    BitWriter writer;
    bit_writer_init(&writer, file);

    for (char* p = fileContent; *p; p++) {
        write_bit(&writer, *p == '1' ? 1 : 0);
    }

    flush_bits(&writer);
    fclose(file);
    return 0;
}
