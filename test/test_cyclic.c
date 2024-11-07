#include <stddef.h>
#include "acutest.h"
#include "../include/cyclic.h"

void test_cyclic_strings_simple() {
    char* a = "abc";
    char* b = "bca";
    char* c = "cab";

    char* la = lexicographically_minimal_string_rotation(a);
    char* lb = lexicographically_minimal_string_rotation(b);
    char* lc = lexicographically_minimal_string_rotation(c);

    TEST_ASSERT(strcmp(la, a) == 0);
    TEST_ASSERT(strcmp(lb, a) == 0);
    TEST_ASSERT(strcmp(lc, a) == 0);
}

void test_cyclic_strings_longer() {
    char* s = "barracuda";
    char* l = "abarracud";

    char* sa = lexicographically_minimal_string_rotation(s);


    TEST_ASSERT(strcmp(l, sa) == 0);
}

TEST_LIST = {
        { "Lexicographically smallest string - simple", test_cyclic_strings_simple},
        { "Lexicographically smallest string - longer", test_cyclic_strings_longer},

        { NULL, NULL }
};