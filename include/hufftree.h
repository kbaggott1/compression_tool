#ifndef HUFFTREE_H
#define HUFFTREE_H
#include "freqtable.h"

typedef struct Node {
    struct Node* parent;
    struct Node* left;
    struct Node* right;
    char data;
    int weight;
} Node;

Node* hufftree_init(FrequencyTable* pFt);
void hufftree_free(Node* root);

#endif