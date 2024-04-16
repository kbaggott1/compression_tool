#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freqtable.h"
#include "hufftree.h"


void generate_huffman_codes(Node* node, char* code, char** huffmanCodes) {
    //THERE IS A PROBLEM HERE ):
    if (node == NULL) {
        return;
    }
    if (node->left == NULL && node->right == NULL) {
        huffmanCodes[(unsigned char)node->data] = strdup(code);
        printf("huffmanCodes[%d]: %s for char %c\n", node->data, code, node->data);
    } else {
        size_t len = strlen(code);
        char* newCode = malloc(len + 2);
        strcpy(newCode, code);
        newCode[len] = '0';
        newCode[len + 1] = '\0';
        generate_huffman_codes(node->left, newCode, huffmanCodes);
        newCode[len] = '1';
        generate_huffman_codes(node->right, newCode, huffmanCodes);
        free(newCode);
    }
}

char* encode(char* fileContents, char** huffmanCodes) {
    char* encoded = malloc(1);
    encoded[0] = '\0';

    
    printf("%d", 'a');
    for(int i = 0; i < strlen(fileContents) - 1; i++) {
        char* code = huffmanCodes[(unsigned char)fileContents[i]];
        size_t newLen = strlen(encoded) + strlen(code) + 1;
        encoded = realloc(encoded, newLen);
        
        if(encoded == NULL) {
            return NULL;
        }

        strcat(encoded, code);
    }

    return encoded;
}

char* cmpr_compress(char* fileContents) {
    FrequencyTable* pFt = freqtable_init(fileContents);
    Node* root = hufftree_init(pFt);

    char* huffmanCodes[256] = {0}; //256 bits in a char
    char* code = "";
    generate_huffman_codes(root, code, huffmanCodes);
    printf("gen codes\n");
    printf("%s\n", huffmanCodes[fileContents[0]]);
    //char* fileEncoded = encode(fileContents, huffmanCodes);

    //ufftree_free(root);
    //freqtable_free(pFt);
    return NULL;//return fileEncoded;
}