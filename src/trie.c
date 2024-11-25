//
// Created by Gabriel Van Langenhove on 01/11/2024.
//

#include "../include/trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Node structure for the compressed trie
typedef struct TrieNode {
    char *substring;              // Compressed string for the node
    struct TrieNode **children;   // Dynamic array of children
    bool is_leaf;                 // Indicates if this node represents the end of a word
    size_t num_children;          // Number of children
    size_t capacity;              // Capacity of the children array
} TrieNode;

// Main trie structure
struct Trie {
    TrieNode *root;   // Root node of the trie
    size_t size;      // Total number of words in the trie
};

// Helper function to create a new trie node
TrieNode *trie_create_node(const char *substring) {
    TrieNode *node = malloc(sizeof(TrieNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed for TrieNode\n");
        exit(EXIT_FAILURE);
    }

    node->substring = substring ? strdup(substring) : NULL;
    node->children = NULL;
    node->is_leaf = false;
    node->num_children = 0;
    node->capacity = 0;

    return node;
}

// Helper function to free a trie node and its children recursively
void trie_free_node(TrieNode *node) {
    if (!node) return;

    free(node->substring);

    for (size_t i = 0; i < node->num_children; i++) {
        trie_free_node(node->children[i]);
    }

    free(node->children);
    free(node);
}

// Initialize a new compressed trie
Trie *trie_init() {
    Trie *trie = malloc(sizeof(Trie));
    if (!trie) {
        fprintf(stderr, "Memory allocation failed for Trie\n");
        exit(EXIT_FAILURE);
    }

    trie->root = trie_create_node(NULL);
    trie->size = 0;

    return trie;
}

// Helper function to find the longest common prefix
size_t trie_longest_common_prefix(const char *a, const char *b) {
    size_t i = 0;
    while (a[i] && b[i] && a[i] == b[i]) {
        i++;
    }
    return i;
}

// Helper function to add a child to a node
void trie_add_child(TrieNode *parent, TrieNode *child) {
    if (parent->num_children == parent->capacity) {
        size_t new_capacity = parent->capacity == 0 ? 4 : parent->capacity * 2;
        parent->children = realloc(parent->children, new_capacity * sizeof(TrieNode *));
        if (!parent->children) {
            fprintf(stderr, "Memory reallocation failed for children array\n");
            exit(EXIT_FAILURE);
        }
        parent->capacity = new_capacity;
    }

    parent->children[parent->num_children++] = child;
}

// Recursive helper function to add a word to the trie
bool trie_add_recursive(TrieNode *node, const char *key) {
    if (!*key) {  // If the key is empty, mark the node as a leaf
        if (!node->is_leaf) {
            node->is_leaf = true;
            return true;
        }
        return false;
    }

    // Traverse through children to find a match
    for (size_t i = 0; i < node->num_children; i++) {
        TrieNode *child = node->children[i];
        size_t prefix_length = trie_longest_common_prefix(key, child->substring);

        if (prefix_length > 0) {
            if (prefix_length == strlen(child->substring)) {
                // Continue adding to the matching child
                return trie_add_recursive(child, key + prefix_length);
            }
            // Split the child node
            TrieNode *split_node = trie_create_node(child->substring + prefix_length);
            split_node->children = child->children;
            split_node->num_children = child->num_children;
            split_node->capacity = child->capacity;
            split_node->is_leaf = child->is_leaf;

            child->substring = strndup(child->substring, prefix_length);
            child->children = NULL;
            child->num_children = 0;
            child->capacity = 0;
            child->is_leaf = false;

            trie_add_child(child, split_node);
            TrieNode *new_child = trie_create_node(key + prefix_length);
            new_child->is_leaf = true;
            trie_add_child(child, new_child);

            return true;
        }
    }

    // If no match, create a new child
    TrieNode *new_child = trie_create_node(key);
    new_child->is_leaf = true;
    trie_add_child(node, new_child);

    return true;
}

// Add a word to the trie
bool trie_add(Trie *trie, const char *key) {
    if (!trie || !key) return false;

    if (trie_add_recursive(trie->root, key)) {
        trie->size++;
        return true;
    }
    return false;
}

// Recursive helper function to search for a word in the trie
bool trie_search_recursive(const TrieNode *node, const char *key) {
    if (!*key) return node->is_leaf;

    for (size_t i = 0; i < node->num_children; i++) {
        const TrieNode *child = node->children[i];
        size_t prefix_length = trie_longest_common_prefix(key, child->substring);

        if (prefix_length == strlen(child->substring)) {
            return trie_search_recursive(child, key + prefix_length);
        }
    }

    return false;
}

// Search for a word in the trie
bool trie_search(const Trie *trie, const char *key) {
    if (!trie || !key) return false;

    return trie_search_recursive(trie->root, key);
}

// Free the trie and its nodes
void trie_free(Trie *trie) {
    if (!trie) return;

    trie_free_node(trie->root);
    free(trie);
}

// Get the size of the trie
size_t trie_size(Trie *trie) {
    return trie ? trie->size : 0;
}

