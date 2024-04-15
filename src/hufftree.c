#include <stdio.h>
#include <stdlib.h>
#include "freqtable.h"

typedef struct {
    Node** queue;
    int size;
    int capacity;
    
} PriorityQueue;

typedef struct {
    Node* parent;
    Node* left;
    Node* right;
    char data;
    int weight;
} Node;

Node* create_node(char data, int weight) {
    Node* node = malloc(sizeof(Node));

    if(node == NULL) {
        return NULL;
    }

    node->data = data;
    node->weight = weight;

    return node;
}

PriorityQueue* pq_init(FrequencyTable* pFt) {
    PriorityQueue* pPQ = malloc(sizeof(PriorityQueue));
    pPQ->queue = malloc(pFt->size * sizeof(Node*));
    pPQ->size = 0;
    pPQ->capacity = pFt->size;
    Node* pNodeTemp;

    for(int i = 0; i < pFt->size - 1; i++) {
        pNodeTemp = create_node(pFt->data[i], pFt->freq[i]);

        if(pNodeTemp) {
            pq_enqueue(pPQ, pNodeTemp);
        }  
    }
}

int pq_enqueue(PriorityQueue* pPQ, Node* pNewNode) {
    if(pPQ->size == pPQ->capacity) {
        int newCapacity = pPQ->capacity * 2;
        Node** temp = realloc(pPQ->queue, sizeof(Node*) * newCapacity);

        if(temp == NULL) {
            perror("Could not realloc mem for queue");
            return -1;
        }

        pPQ->queue = temp;
    }

    Node* pNode;
    int i;

    for(i = 0; i < pPQ->size; i++) {
        if(pPQ->queue[i]->weight > pNewNode->weight) {
            break;
        }
    }

    for(int j = pPQ->size; j > i; j--) {
        pPQ->queue[j] = pPQ->queue[j - 1];
    }

    pPQ->queue[i] = pNewNode;

    pPQ->size++;
    return 0;
}

Node* pq_dequeue(PriorityQueue* pPQ) {
    if(pPQ->size == 0) {
        return NULL;
    }

    Node* node = pPQ->queue[0];

    for(int i = 1; i < pPQ->size - 1; i++) {
        pPQ->queue[i - 1] = pPQ->queue[i];
    }

    return node;
}


Node* hufftree_init(FrequencyTable* pFt) {
    PriorityQueue* pPQ = pq_init(pFt);
    
    return NULL;
}

Node* hufftree_free(Node* root) {
    __THROW;
}