//
// Created by Gabriel Van Langenhove on 30/11/2024.
//

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "acutest.h"
#include "../include/struct_utils.h"
#include "../include/hashtable.h"
#include "../include/searchtree.h"

#define MWC_A2 0xffa04e67b3c95d86

uint64_t rand_x, rand_y, rand_c;
uint64_t next_random() {
    const uint64_t result = rand_y;
    const __uint128_t t = MWC_A2 * (__uint128_t)rand_x + rand_c;
    rand_x = rand_y;
    rand_y = t;
    rand_c = t >> 64;
    return result;
}

// Generate a random string of specified length
char* generate_random_string(size_t length) {
    char* str = malloc(length + 1);
    for (size_t i = 0; i < length; ++i) {
        str[i] = 'a' + (next_random() % 26);
    }
    str[length] = '\0';
    return str;
}

void test_varying_lengths(const char* type) {
    void* structure = init_datastructure(type);

    const size_t small = 10;
    const size_t medium = 100;
    const size_t large = 1000;
    char* small_str = generate_random_string(small);
    char* medium_str = generate_random_string(medium);
    char* large_str = generate_random_string(large);


    TEST_ASSERT(add_to_datastructure(structure, small_str, type));
    TEST_ASSERT(add_to_datastructure(structure, medium_str, type));
    TEST_ASSERT(add_to_datastructure(structure, large_str, type));

    TEST_ASSERT(search_in_datastructure(structure, small_str, type));
    TEST_ASSERT(search_in_datastructure(structure, medium_str, type));
    TEST_ASSERT(search_in_datastructure(structure, small_str, type));

    TEST_ASSERT(!add_to_datastructure(structure, small_str, type));
    TEST_ASSERT(!add_to_datastructure(structure, medium_str, type));
    TEST_ASSERT(!add_to_datastructure(structure, large_str, type));

    free(small_str);
    free(medium_str);
    free(large_str);
    free_datastructure(structure, type);
}


void test_null_and_empty_strings(const char* type) {
    void* structure = init_datastructure(type);

    char* empty_string = "";
    TEST_ASSERT(add_to_datastructure(structure, empty_string, type));
    TEST_ASSERT(search_in_datastructure(structure, empty_string, type));
    TEST_ASSERT(!add_to_datastructure(structure, empty_string, type)); // Should not add duplicate

    char* null_string = NULL;

    TEST_ASSERT(!add_to_datastructure(structure, null_string, type));  // Should not add null
    TEST_ASSERT(!search_in_datastructure(structure, null_string, type));

    free_datastructure(structure, type);
}

void test_large_number_of_elements(const char* type) {
    void* structure = init_datastructure(type);

    const size_t num_elements = 100;
    char** strings = malloc(num_elements * sizeof(char*));
    for (size_t i = 0; i < num_elements; ++i) {
        strings[i] = generate_random_string(i);
        TEST_ASSERT(add_to_datastructure(structure, strings[i], type));
        TEST_ASSERT(search_in_datastructure(structure, strings[i], type));
    }

    // Verify all strings are present
    for (size_t i = 0; i < num_elements; ++i) {
        TEST_ASSERT(search_in_datastructure(structure, strings[i], type));
    }

    // Free all strings
    for (size_t i = 0; i < num_elements; ++i) {
        free(strings[i]);
    }
    free(strings);
    free_datastructure(structure, type);
}

void test_hashtable_collision_handling() {
    HashTable* ht = hashtable_init();

    // Add keys with deliberate collisions (keys with similar hashes)
    char* key1 = "test_key1";
    char* key2 = "test_key2"; // Assume key2 intentionally collides with key1
    char* key3 = "test_key3";

    TEST_ASSERT(hashtable_add(ht, key1));
    TEST_ASSERT(hashtable_add(ht, key2));
    TEST_ASSERT(hashtable_add(ht, key3));

    TEST_ASSERT(hashtable_search(ht, key1));
    TEST_ASSERT(hashtable_search(ht, key2));
    TEST_ASSERT(hashtable_search(ht, key3));

    hashtable_free(ht);
}

// -------------------
// help to compile

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

// ------------------

void test_searchtree_color_property() {
    SearchTree* st = searchtree_init();

    char* key1 = "alpha";
    char* key2 = "beta";
    char* key3 = "gamma";

    searchtree_add(st, key1);
    searchtree_add(st, key2);
    searchtree_add(st, key3);

    Node* root = st->root;
    TEST_ASSERT(root->color == BLACK);  // Root must always be black
    if (root->left) {
        TEST_ASSERT(root->left->color == RED || root->left->color == BLACK);
    }
    if (root->right) {
        TEST_ASSERT(root->right->color == RED || root->right->color == BLACK);
    }

    searchtree_free(st);
}

void test_hashtable_varying_lengths(){ test_varying_lengths("hashtable"); }
void test_hashtable_null_and_empty_strings(){ test_null_and_empty_strings("hashtable"); }
void test_hashtable_large_number_of_elements(){ test_large_number_of_elements("hashtable"); }

void test_trie_varying_lengths(){ test_varying_lengths("trie"); }
void test_trie_null_and_empty_strings(){ test_null_and_empty_strings("trie"); }
void test_trie_large_number_of_elements(){ test_large_number_of_elements("trie"); }

void test_searchtree_varying_lengths(){ test_varying_lengths("searchtree"); }
void test_searchtree_null_and_empty_strings(){ test_null_and_empty_strings("searchtree"); }
void test_searchtree_large_number_of_elements(){ test_large_number_of_elements("searchtree"); }

TEST_LIST = {
    { "Hashtable varying lengths",            test_hashtable_varying_lengths },
    { "Hashtable collision handling",         test_hashtable_collision_handling },
    { "Hashtable null and empty strings",     test_hashtable_null_and_empty_strings },
    { "Hashtable large number of elements",   test_hashtable_large_number_of_elements },

    { "Trie varying lengths",            test_trie_varying_lengths },
    { "Trie null and empty strings",     test_trie_null_and_empty_strings },
    { "Trie large number of elements",   test_trie_large_number_of_elements },

    { "Searchtree varying lengths",            test_searchtree_varying_lengths },
    { "Searchtree null and empty strings",     test_searchtree_null_and_empty_strings },
    { "Searchtree large number of elements",   test_searchtree_large_number_of_elements },
    { NULL, NULL },
};
