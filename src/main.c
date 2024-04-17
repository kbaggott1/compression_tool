#include <stdio.h>
#include <stdlib.h>
#include "cmpr.h"
#include <string.h>
#include "bitwriter.h"
#define COMPRESSED_EXT ".cmpr"

char* read_line(FILE* pFile) {
    size_t bufferSize = 1000;
    char* line = malloc(bufferSize);
    line[0] = '\0';

    while(fgets(line, bufferSize, pFile)) {
        if(line == NULL) {
            free(line);
            return NULL;
        }

        if(line[strlen(line) - 1] == '\n') {
            return line;
        }
        

        bufferSize *= 2;
        line = realloc(line, bufferSize);
    }

    //if file doesnt end with new line
    if(strlen(line) > 0) {
        return strcat(line, "\n");
    }
    return NULL;
}

char* get_file_contents(char* filePath) {
    FILE* pFile = fopen(filePath, "r");
    size_t fileContentSize = 1000;

    if(pFile == NULL) {
        perror("File not found and could not be opened.");
        return NULL;
    }

    char* line;
    char* fileContents = malloc(fileContentSize);

    if(fileContents == NULL) {
        perror("Could not allocate mem for file contents.");
        return NULL;
    }

    fileContents[0] = '\0';

    while((line = read_line(pFile)) != NULL) {

        if((strlen(fileContents) + strlen(line)) >= fileContentSize ) {
            fileContentSize *= 2;
            fileContents = realloc(fileContents, fileContentSize);
            if(fileContents == NULL) {
                perror("Could not realloc mem to fileContents");
                return NULL;
            }
        }
        strcat(fileContents, line);
        free(line);
    }

    return fileContents;
}

int main(int argc, char *argv[]) {
    char* fileContents;
    char* encodedContents;
    char* filePath;
    char* newFilePath;

    // fileContents = get_file_contents("test.txt");
    // encodedContents = cmpr_compress(fileContents);
    if( argc == 2 ) {
        filePath = argv[1];
        
        printf("Compressing file %s\n", filePath);
        fileContents = get_file_contents(filePath);

        encodedContents = cmpr_compress(fileContents);
        newFilePath = malloc(strlen(filePath) + strlen(COMPRESSED_EXT) + 1);

        if(newFilePath == NULL) {
            perror("Could not realloc mem for newFilePath");
            return -1;
        }

        strcat(strcpy(newFilePath, filePath), COMPRESSED_EXT);
        bit_write_to_file(newFilePath, encodedContents);

        free(fileContents);
        free(encodedContents);
        free(newFilePath);
    }
    else if( argc > 2 ) {
        printf("Too many arguments supplied.\n");
    }
    else {
        printf("One argument expected.\n");
    }
}