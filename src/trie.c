//
// Created by Gabriel Van Langenhove on 01/11/2024.
//

#include "../include/trie.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct TrieNode {
    char character;
    bool is_leaf;
    struct TrieNode *left;
    struct TrieNode *middle;
    struct TrieNode *right;
} TrieNode;

struct Trie {
    TrieNode *root;
    size_t size;
};

// Function to create a new trie node
TrieNode* trie_create_node(char character) {
    TrieNode* node = malloc(sizeof(TrieNode));
    node->character = character;
    node->is_leaf = false;
    node->left = node->middle = node->right = NULL;
    return node;
}

// Initialize the trie
Trie* trie_init() {
    Trie* trie = malloc(sizeof(Trie));
    trie->root = NULL;
    trie->size = 0;
    return trie;
}

// Recursive helper function to add a word to the trie
void trie_add_recursive(TrieNode **root, const char *word, Trie *trie) {
    if (!*root) *root = trie_create_node(*word);

    if (*word < (*root)->character) {
        trie_add_recursive(&(*root)->left, word, trie);
    } else if (*word > (*root)->character) {
        trie_add_recursive(&(*root)->right, word, trie);
    } else {
        if (*(word + 1) == '\0') {
            if (!(*root)->is_leaf) {  // Only increase size if it's a new word
                (*root)->is_leaf = true;
                trie->size++;
            }
        } else {
            trie_add_recursive(&(*root)->middle, word + 1, trie);
        }
    }
}

// Public function to add a word to the trie
bool trie_add(Trie *trie, const char *word) {
    if (!trie || !word || trie_search(trie, word))
        return false;

    trie_add_recursive(&trie->root, word, trie);
    return true;
}

// Recursive helper function to search for a word in the trie
bool trie_search_recursive(TrieNode *root, const char *word) {
    if (!root) return false;

    if (*word < root->character)
        return trie_search_recursive(root->left, word);

    if (*word > root->character)
        return trie_search_recursive(root->right, word);

    if (*(word + 1) == '\0')
        return root->is_leaf;

    return trie_search_recursive(root->middle, word + 1);
}

// Public function to search for a word in the trie
bool trie_search(const Trie *trie, const char *word) {
    if (!trie || !word) return false;
    return trie_search_recursive(trie->root, word);
}

// Recursive helper function to free nodes
void trie_free_recursive(TrieNode *root) {
    if (!root) return;
    trie_free_recursive(root->left);
    trie_free_recursive(root->middle);
    trie_free_recursive(root->right);
    free(root);
}

// Public function to free the trie
void trie_free(Trie *trie) {
    if (!trie) return;
    trie_free_recursive(trie->root);
    free(trie);
}

// Public function to get the number of words in the trie
size_t trie_size(Trie *trie) {
    if (!trie) return 0;
    return trie->size;
}