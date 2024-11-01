//
// Created by Gabriel Van Langenhove on 01/11/2024.
//

#include "searchtree.h"
#include <assert.h>

int main_test() {
    SearchTree* tree = searchtree_init();
    assert(searchtree_add(tree, "hello"));           // Add an element
    assert(searchtree_search(tree, "hello"));        // Verify the element exists
    assert(!searchtree_search(tree, "world"));       // Verify a non-existent element
    searchtree_free(tree);                           // Clean up
    return 0;
}

