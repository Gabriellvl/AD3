//
// Created by Gabriel Van Langenhove on 25/11/2024.
//

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "utils.h"

// Compare two substrings lexicographically using 64-bit words
int compare_words(const char* s1, const char* s2, size_t len) {
    size_t i = 0;

    while (i + 8 <= len) {
        // Read 64-bit chunks from both substrings
        uint64_t word1 = *(const uint64_t*)(s1 + i);
        uint64_t word2 = *(const uint64_t*)(s2 + i);

        // If the chunks are different, find the exact byte difference
        if (word1 != word2) {
            uint64_t diff = word1 ^ word2; // XOR to identify differing bits

            // Find the first differing byte
            size_t differing_byte = __builtin_ctzll(diff) / 8;

            // Extract the differing byte from each word
            unsigned char c1 = (word1 >> (differing_byte * 8)) & 0xFF;
            unsigned char c2 = (word2 >> (differing_byte * 8)) & 0xFF;

            // Return the comparison result
            return (c1 < c2) ? -1 : 1;
        }
        i += 8; // Move to the next 64-bit block
    }

    // Compare any remaining bytes one by one
    while (i < len) {
        if (s1[i] < s2[i]) return -1;
        if (s1[i] > s2[i]) return 1;
        i++;
    }

    return 0; // Substrings are equal
}

char* double_string(const char* input, size_t len) {
    char* doubled = (char*)malloc(len * 2 + 1); // +1 for null terminator
    if (!doubled)
        return NULL;

    strcpy(doubled, input);
    strcat(doubled, input);

    return doubled;
}

size_t find_min_rotation(const char* doubled, size_t len) {
    size_t min_start = 0;

    for (size_t i = 1; i < len; i++) {
        // Compare the current rotation with the smallest found so far
        int cmp = compare_words(doubled + i, doubled + min_start, len);

        if (cmp < 0) {
            min_start = i;
        }
    }

    return min_start; // Return the starting index of the minimal rotation
}


char* lexicographically_minimal_string_rotation(const char* input) {
    if (!input || input[0] == '\0') {
        return my_strdup("");
    }

    size_t len = strlen(input);

    // Double the input string to simulate all rotations
    char* doubled = double_string(input, len);
    if (!doubled)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }


    size_t min_start = find_min_rotation(doubled, len);

    // Step 3: Create the resulting minimal rotation string
    char* rotation = malloc(len + 1);
    if (!rotation) {
        free(doubled); // Free the doubled string if result allocation fails
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Copy the minimal rotation into the result buffer
    strncpy(rotation, doubled + min_start, len);
    rotation[len] = '\0'; // Null-terminate the string

    free(doubled);
    return rotation;
}

