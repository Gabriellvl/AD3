#include <stddef.h>
#include <stdint.h>
#include "acutest.h"
#include "../include/searchtree.h"

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

void test_searchtree_simple_add() {
    char* a = "abc";
    char* b = "bca";
    char* c = "cab";
    char* d = "cba";
    char* e = "bac";

    SearchTree* st = searchtree_init();

    TEST_ASSERT(searchtree_add(st, a));
    TEST_ASSERT(searchtree_add(st, b));
    TEST_ASSERT(searchtree_add(st, c));
    TEST_ASSERT(searchtree_add(st, d));
    TEST_ASSERT(searchtree_add(st, e));
    TEST_ASSERT(searchtree_size(st) == 5);

    TEST_ASSERT(!searchtree_add(st, a));
    TEST_ASSERT(!searchtree_add(st, b));
    TEST_ASSERT(!searchtree_add(st, c));
    TEST_ASSERT(!searchtree_add(st, d));
    TEST_ASSERT(!searchtree_add(st, e));
    TEST_ASSERT(searchtree_size(st) == 5);

    searchtree_free(st);
}

void test_searchtree_simple_add_search() {
    char* a = "abc";
    char* b = "bca";
    char* c = "cab";
    char* d = "cba";
    char* e = "bac";

    SearchTree* st = searchtree_init();

    TEST_ASSERT(searchtree_add(st, a));
    TEST_ASSERT(searchtree_add(st, b));
    TEST_ASSERT(searchtree_add(st, c));
    TEST_ASSERT(searchtree_add(st, d));
    TEST_ASSERT(searchtree_add(st, e));

    TEST_ASSERT(searchtree_search(st, a));
    TEST_ASSERT(searchtree_search(st, b));
    TEST_ASSERT(searchtree_search(st, c));
    TEST_ASSERT(searchtree_search(st, d));
    TEST_ASSERT(searchtree_search(st, e));

    TEST_ASSERT(!searchtree_add(st, a));
    TEST_ASSERT(!searchtree_add(st, b));
    TEST_ASSERT(!searchtree_add(st, c));
    TEST_ASSERT(!searchtree_add(st, d));
    TEST_ASSERT(!searchtree_add(st, e));

    searchtree_free(st);
}

void test_searchtree_ascending() {
    SearchTree* st = searchtree_init();

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
        TEST_ASSERT(searchtree_size(st) == i);
        TEST_ASSERT(searchtree_add(st, strings[i]));
        size_t sample = next_random() % count;
        TEST_ASSERT(searchtree_search(st, strings[i]));
        TEST_ASSERT(searchtree_search(st, strings[sample]) == (sample <= i));
    }
    for (size_t i = 0; i < count; ++i) {
        TEST_ASSERT(searchtree_search(st, strings[i]));
    }

    searchtree_free(st);
}


void test_searchtree_independent_strings() {
    SearchTree* st = searchtree_init();

    char* original = "test";
    char* copy = malloc(strlen(original) + 1);
    strcpy(copy, original);

    TEST_ASSERT_(searchtree_add(st, original), "should be able to add test string");
    TEST_ASSERT_(!searchtree_add(st, copy), "should not be able to add other string with equal contents again");
    TEST_ASSERT_(searchtree_search(st, original), "should find added string");
    TEST_ASSERT_(searchtree_search(st, copy), "should be able to find other string with equal contents");

    searchtree_free(st);
}


TEST_LIST = {
        { "SearchTree simple add",               test_searchtree_simple_add },
        { "SearchTree simple add and search",    test_searchtree_simple_add_search },
        { "SearchTree add ascending",            test_searchtree_ascending },
        { "SearchTree independent strings",      test_searchtree_independent_strings },
        { NULL, NULL }
};