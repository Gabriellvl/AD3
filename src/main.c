#include "../include/cyclic.h"
#include "../include/hashtable.h"
#include "../include/searchtree.h"
#include "../include/trie.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 4095

// Function to handle command-line argument and select the appropriate data structure
void* init_datastructure(const char* type);
bool add_to_datastructure(void* ds, const char* key, const char* type);
bool search_in_datastructure(const void* ds, const char* key, const char* type);
void free_datastructure(void* ds, const char* type);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <datastructuur>\n", argv[0]);
        return 1;
    }

    // Initialize the data structure based on command-line argument
    const char* datastructuur = argv[1];
    void* structure = init_datastructure(datastructuur);

    if (!structure) {
        fprintf(stderr, "Failed to initialize the data structure\n");
        return 1;
    }

    // Buffer to store the input lines
    char line[MAX_LINE_LENGTH + 1];

    // Read lines from stdin
    while (fgets(line, sizeof(line), stdin)) {
        // Remove newline character
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // Calculate the lexicographically minimal rotation
        char minimal_rotation[MAX_LINE_LENGTH + 1];
        char *result = lexicographically_minimal_string_rotation(line);
        strcpy(minimal_rotation, result);


        // Check if the minimal rotation has already been seen
        if (!search_in_datastructure(structure, minimal_rotation, datastructuur)) {
            // Print the string if it's a unique rotation
            printf("%s\n", line);
            // Add the rotation to the data structure
            add_to_datastructure(structure, minimal_rotation, datastructuur);
        }
    }

    // Free memory used by the data structure
    free_datastructure(structure, datastructuur);

    return 0;
}

// Initialize the appropriate data structure
void* init_datastructure(const char* type) {
    if (strcmp(type, "hashtable") == 0) {
        return hashtable_init();
    }
    if (strcmp(type, "trie") == 0) {
        return trie_init();
    }
    if (strcmp(type, "searchtree") == 0) {
        return searchtree_init();
    }

    fprintf(stderr, "Unknown data structure type: %s\n", type);
    return NULL;
}

// Add to the appropriate data structure
bool add_to_datastructure(void* ds, const char* key, const char* type) {
    if (strcmp(type, "hashtable") == 0) {
        return hashtable_add(ds, key);
    }
    if (strcmp(type, "trie") == 0) {
        return trie_add(ds, key);
    }
    if (strcmp(type, "searchtree") == 0) {
        return searchtree_add((SearchTree*)ds, key);
    }
    fprintf(stderr, "Unknown data structure type: %s\n", type);
    return false;
}

// Search in the appropriate data structure
bool search_in_datastructure(const void* ds, const char* key, const char* type) {
    if (strcmp(type, "hashtable") == 0) {
        return hashtable_search(ds, key);
    }
    if (strcmp(type, "trie") == 0) {
        return trie_search(ds, key);
    }
    if (strcmp(type, "searchtree") == 0) {
        return searchtree_search((const SearchTree*)ds, key);
    }
    fprintf(stderr, "Unknown data structure type: %s\n", type);
    return false;
}

// Free the appropriate data structure
void free_datastructure(void* ds, const char* type) {
    if (strcmp(type, "hashtable") == 0) {
        hashtable_free(ds);
    }
    if (strcmp(type, "trie") == 0) {
        trie_free(ds);
    }
    if (strcmp(type, "searchtree") == 0) {
        searchtree_free((SearchTree*)ds);
    }
    fprintf(stderr, "Unknown data structure type: %s\n", type);
}
