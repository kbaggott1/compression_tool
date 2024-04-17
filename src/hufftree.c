#include <stdio.h>
#include <stdlib.h>
#include "freqtable.h"

typedef struct Node {
    struct Node* left;
    struct Node* right;
    char data;
    int weight;
} Node;

typedef struct {
    Node** queue;
    int size;
    int capacity;
    
} PriorityQueue;

Node* create_node(char data, int weight) {
    Node* node = malloc(sizeof(Node));

    if(node == NULL) {
        return NULL;
    }

    node->data = data;
    node->weight = weight;

    return node;
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

    for(int i = 1; i < pPQ->size; i++) {
        pPQ->queue[i - 1] = pPQ->queue[i];
    }

    pPQ->size--;
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

    return pPQ;
}

Node* hufftree_init(FrequencyTable* pFt) {
    PriorityQueue* pPQ = pq_init(pFt);
    Node *node1, *node2, *internalNode;

    while(pPQ->size != 1) {
        node1 = pq_dequeue(pPQ);
        node2 = pq_dequeue(pPQ);

        internalNode = create_node(-1,node1->weight + node2->weight);
        
        if(node1->weight < node2->weight) {
            internalNode->left = node1;
            internalNode->right = node2;
        }
        else {
            internalNode->left = node2;
            internalNode->right = node1;
        }

        pq_enqueue(pPQ, internalNode);
    }

    return pq_dequeue(pPQ);
}

void hufftree_free(Node* root) {
    if(root->left != NULL) {
        hufftree_free(root->left);
    }
    if(root->right != NULL) {
        hufftree_free(root->right);
    }
    free(root);
    return;
}