#include <stddef.h>
#include <stdint.h>
#include "acutest.h"
#include "../include/trie.h"

#define MWC_A2 0xffa04e67b3c95d86

// rand() is deprecated, hence this small but efficient random number generator
uint64_t rand_x, rand_y, rand_c;
uint64_t next_random() {
    const uint64_t result = rand_y;
    const __uint128_t t = MWC_A2 * (__uint128_t)rand_x + rand_c;
    rand_x = rand_y;
    rand_y = t;
    rand_c = t >> 64;
    return result;
}

void test_trie_simple_add() {
    char* a = "abc";
    char* b = "bca";
    char* c = "cab";
    char* d = "cba";
    char* e = "bac";

    Trie* trie = trie_init();

    TEST_ASSERT(trie_add(trie, a));
    TEST_ASSERT(trie_add(trie, b));
    TEST_ASSERT(trie_add(trie, c));
    TEST_ASSERT(trie_add(trie, d));
    TEST_ASSERT(trie_add(trie, e));
    TEST_ASSERT(trie_size(trie) == 5);

    TEST_ASSERT(!trie_add(trie, a));
    TEST_ASSERT(!trie_add(trie, b));
    TEST_ASSERT(!trie_add(trie, c));
    TEST_ASSERT(!trie_add(trie, d));
    TEST_ASSERT(!trie_add(trie, e));
    TEST_ASSERT(trie_size(trie) == 5);

    trie_free(trie);
}

void test_trie_simple_add_search() {
    char* a = "abc";
    char* b = "bca";
    char* c = "cab";
    char* d = "cba";
    char* e = "bac";

    Trie* trie = trie_init();

    TEST_ASSERT(trie_add(trie, a));
    TEST_ASSERT(trie_add(trie, b));
    TEST_ASSERT(trie_add(trie, c));
    TEST_ASSERT(trie_add(trie, d));
    TEST_ASSERT(trie_add(trie, e));

    TEST_ASSERT(trie_search(trie, a));
    TEST_ASSERT(trie_search(trie, b));
    TEST_ASSERT(trie_search(trie, c));
    TEST_ASSERT(trie_search(trie, d));
    TEST_ASSERT(trie_search(trie, e));

    TEST_ASSERT(!trie_add(trie, a));
    TEST_ASSERT(!trie_add(trie, b));
    TEST_ASSERT(!trie_add(trie, c));
    TEST_ASSERT(!trie_add(trie, d));
    TEST_ASSERT(!trie_add(trie, e));

    trie_free(trie);
}

void test_trie_ascending() {
    Trie* trie = trie_init();

    const size_t count = 1000000;
    const size_t maxlen = 8;
    char strings[count][maxlen];

    for (size_t i = 0; i < count; ++i) {
        size_t k = i;
        for (size_t j = 0; j < maxlen - 1; ++j) {
            strings[i][j] = (char) ((k % 64) + 63);
            k /= 64;
        }
        strings[i][maxlen - 1] = '\0';
    }
    for (size_t i = 0; i < count; ++i) {
        TEST_ASSERT(trie_size(trie) == i);
        TEST_ASSERT(trie_add(trie, strings[i]));
        size_t sample = next_random() % count;
        TEST_ASSERT(trie_search(trie, strings[i]));
        TEST_ASSERT(trie_search(trie, strings[sample]) == (sample <= i));
    }
    for (size_t i = 0; i < count; ++i) {
        TEST_ASSERT(trie_search(trie, strings[i]));
    }

    trie_free(trie);
}


void test_trie_independent_strings() {
    Trie* trie = trie_init();

    char* original = "test";
    char* copy = malloc(strlen(original) + 1);
    strcpy(copy, original);

    TEST_ASSERT_(trie_add(trie, original), "should be able to add test string");
    TEST_ASSERT_(!trie_add(trie, copy), "should not be able to add other string with equal contents again");
    TEST_ASSERT_(trie_search(trie, original), "should find added string");
    TEST_ASSERT_(trie_search(trie, copy), "should be able to find other string with equal contents");

    trie_free(trie);
}


TEST_LIST = {
        { "Trie simple add",               test_trie_simple_add },
        { "Trie simple add and search",    test_trie_simple_add_search },
        { "Trie add ascending",            test_trie_ascending },
        { "Trie independent strings",      test_trie_independent_strings },
        { NULL, NULL }
};