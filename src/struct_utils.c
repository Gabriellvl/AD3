//
// Created by Gabriel Van Langenhove on 04/12/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/struct_utils.h"

#include "../include/hashtable.h"
#include "../include/trie.h"
#include "../include/searchtree.h"

typedef enum { RED, BLACK } Color;

typedef struct Node {
    char* key;
    Color color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

struct SearchTree {
    Node* root;
    size_t size;
};

// Initialize the appropriate data structure
void* init_datastructure(const char* type) {
    if (strcmp(type, "hashtable") == 0) {
        return hashtable_init();
    }
    if (strcmp(type, "trie") == 0) {
        return trie_init();
    }
    if (strcmp(type, "searchtree") == 0) {
        return searchtree_init();
    }

    fprintf(stderr, "Unknown data structure type: %s\nInside init struct", type);
    return NULL;
}

// Add to the appropriate data structure
bool add_to_datastructure(void* ds, const char* key, const char* type) {
    if (strcmp(type, "hashtable") == 0) {
        return hashtable_add(ds, key);
    }
    if (strcmp(type, "trie") == 0) {
        return trie_add(ds, key);
    }
    if (strcmp(type, "searchtree") == 0) {
        return searchtree_add(ds, key);
    }

    fprintf(stderr, "Unknown data structure type: %s\nFailed to add to struct", type);
    return false;
}

// Search in the appropriate data structure
bool search_in_datastructure(const void* ds, const char* key, const char* type) {
    if (strcmp(type, "hashtable") == 0) {
        return hashtable_search(ds, key);
    }
    if (strcmp(type, "trie") == 0) {
        return trie_search(ds, key);
    }
    if (strcmp(type, "searchtree") == 0) {
        return searchtree_search(ds, key);
    }

    fprintf(stderr, "Unknown data structure type: %s\nFailed to search in struct", type);
    return false;
}

// Free the appropriate data structure
void free_datastructure(void* ds, const char* type) {
    if (strcmp(type, "hashtable") == 0) {
        hashtable_free(ds);
    }
    else if (strcmp(type, "trie") == 0) {
        trie_free(ds);
    }
    else if (strcmp(type, "searchtree") == 0) {
        searchtree_free(ds);
    }
    else
    {
        fprintf(stderr, "Unknown data structure type: %s\nFailed to free struct", type);
    }
}
