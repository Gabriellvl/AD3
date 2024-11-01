//
// Created by Gabriel Van Langenhove on 01/11/2024.
//

#include "../include/searchtree.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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

// Function to check if a node is red
bool is_red(Node* node) {
    return node != NULL && node->color == RED;
}

// Helper function to create a new node with is_red initialized
Node* searchtree_create_node(const char* key, Color color, Node* parent) {
    Node* node = malloc(sizeof(Node));
    node->key = strdup(key);  // Duplicate the key
    node->color = color;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    return node;
}

// Function to initialize the search tree
SearchTree* searchtree_init() {
    SearchTree* tree = malloc(sizeof(SearchTree));
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

// Helper function to free nodes
void free_node(Node* node) {
    if (node) {
        free(node->key);
        free_node(node->left);
        free_node(node->right);
        free(node);
    }
}

// Function to free the entire search tree
void searchtree_free(SearchTree* tree) {
    if (tree) {
        free_node(tree->root);
        free(tree);
    }
}

// Rotate left at node x
void rotate_left(SearchTree* tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left)
      y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent)
      tree->root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Rotate right at node x
void rotate_right(SearchTree* tree, Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right)
      y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent)
      tree->root = y;
    else if (x == x->parent->right)
      x->parent->right = y;
    else
      x->parent->left = y;
    y->right = x;
    x->parent = y;
}

// Helper function to fix Red-Black Tree properties after insertion
void insert_fixup(SearchTree* tree, Node* z) {
    // Loop to correct tree properties if the parent of z is red
    while (is_red(z->parent)) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;  // Uncle node
            if (is_red(y)) {
                // Case 1: Uncle is red, recolor and move up the tree
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    // Case 2: z is a right child, rotate to reduce to case 3
                    z = z->parent;
                    rotate_left(tree, z);
                }
                // Case 3: z is a left child, recolor and rotate right
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotate_right(tree, z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;  // Uncle node
            if (is_red(y)) {
                // Mirror Case 1: Uncle is red, recolor and move up the tree
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    // Mirror Case 2: z is a left child, rotate to reduce to case 3
                    z = z->parent;
                    rotate_right(tree, z);
                }
                // Mirror Case 3: z is a right child, recolor and rotate left
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotate_left(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;  // Ensure the root is always black
}

// Add a node to the Red-Black Tree
bool searchtree_add(SearchTree* tree, const char* key) {
    Node* y = NULL;
    Node* x = tree->root;

    // Check if key already exists in the tree
    while (x) {
        y = x;
        int cmp = strcmp(key, x->key);
        if (cmp == 0) return false;  // Key already exists
        x = (cmp < 0) ? x->left : x->right;
    }

    // Create the new node
    Node* z = searchtree_create_node(key, RED, y);
    if (!y) tree->root = z;  // Tree was empty
    else if (strcmp(key, y->key) < 0) y->left = z;
    else y->right = z;

    tree->size++;
    insert_fixup(tree, z);  // Fix Red-Black properties after insertion
    return true;
}

// Search for a key in the Red-Black Tree
bool searchtree_search(const SearchTree* tree, const char* key) {
    Node* x = tree->root;
    while (x) {
        int cmp = strcmp(key, x->key);
        if (cmp == 0) return true;
        x = (cmp < 0) ? x->left : x->right;
    }
    return false;
}

// Return the size of the Red-Black Tree
size_t searchtree_size(SearchTree* tree) {
    return tree ? tree->size : 0;
}

