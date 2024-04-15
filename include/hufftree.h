#ifndef HUFFTREE_H
#define HUFFTREE_H
#include "freqtable.h"

typedef struct {
    Node* parent;
    Node* left;
    Node* right;
    char data;
    int weight;
} Node;

Node* hufftree_init(FrequencyTable* pFt);

#endif