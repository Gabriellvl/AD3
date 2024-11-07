#include <stddef.h>
#include <stdint.h>
#include "acutest.h"
#include "../include/hashtable.h"

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

void test_hashtable_simple_add() {
    char* a = "abc";
    char* b = "bca";
    char* c = "cab";
    char* d = "cba";
    char* e = "bac";

    HashTable* ht = hashtable_init();

    TEST_ASSERT(hashtable_add(ht, a));
    TEST_ASSERT(hashtable_add(ht, b));
    TEST_ASSERT(hashtable_add(ht, c));
    TEST_ASSERT(hashtable_add(ht, d));
    TEST_ASSERT(hashtable_add(ht, e));
    TEST_ASSERT(hashtable_size(ht) == 5);

    TEST_ASSERT(!hashtable_add(ht, a));
    TEST_ASSERT(!hashtable_add(ht, b));
    TEST_ASSERT(!hashtable_add(ht, c));
    TEST_ASSERT(!hashtable_add(ht, d));
    TEST_ASSERT(!hashtable_add(ht, e));
    TEST_ASSERT(hashtable_size(ht) == 5);

    hashtable_free(ht);
}

void test_hashtable_simple_add_search() {
    char* a = "abc";
    char* b = "bca";
    char* c = "cab";
    char* d = "cba";
    char* e = "bac";

    HashTable* ht = hashtable_init();

    TEST_ASSERT(hashtable_add(ht, a));
    TEST_ASSERT(hashtable_add(ht, b));
    TEST_ASSERT(hashtable_add(ht, c));
    TEST_ASSERT(hashtable_add(ht, d));
    TEST_ASSERT(hashtable_add(ht, e));

    TEST_ASSERT(hashtable_search(ht, a));
    TEST_ASSERT(hashtable_search(ht, b));
    TEST_ASSERT(hashtable_search(ht, c));
    TEST_ASSERT(hashtable_search(ht, d));
    TEST_ASSERT(hashtable_search(ht, e));

    TEST_ASSERT(!hashtable_add(ht, a));
    TEST_ASSERT(!hashtable_add(ht, b));
    TEST_ASSERT(!hashtable_add(ht, c));
    TEST_ASSERT(!hashtable_add(ht, d));
    TEST_ASSERT(!hashtable_add(ht, e));

    hashtable_free(ht);
}

void test_hashtable_ascending() {
    HashTable* ht = hashtable_init();

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
        TEST_ASSERT(hashtable_size(ht) == i);
        TEST_ASSERT(hashtable_add(ht, strings[i]));
        size_t sample = next_random() % count;
        TEST_ASSERT(hashtable_search(ht, strings[i]));
        TEST_ASSERT(hashtable_search(ht, strings[sample]) == (sample <= i));
    }
    for (size_t i = 0; i < count; ++i) {
        TEST_ASSERT(hashtable_search(ht, strings[i]));
    }

    hashtable_free(ht);
}


void test_hashtable_independent_strings() {
    HashTable* ht = hashtable_init();

    char* original = "test";
    char* copy = malloc(strlen(original) + 1);
    strcpy(copy, original);

    TEST_ASSERT_(hashtable_add(ht, original), "should be able to add test string");
    TEST_ASSERT_(!hashtable_add(ht, copy), "should not be able to add other string with equal contents again");
    TEST_ASSERT_(hashtable_search(ht, original), "should find added string");
    TEST_ASSERT_(hashtable_search(ht, copy), "should be able to find other string with equal contents");

    hashtable_free(ht);
}


TEST_LIST = {
        { "HashTable simple add",               test_hashtable_simple_add },
        { "HashTable simple add and search",    test_hashtable_simple_add_search },
        { "HashTable add ascending",            test_hashtable_ascending },
        { "Hashtable independent strings",      test_hashtable_independent_strings },
        { NULL, NULL }
};