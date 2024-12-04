//
// Created by Gabriel Van Langenhove on 01/11/2024.
//


#include <stdlib.h>
#include <string.h>

char* my_strdup(const char* s) {
    // Calculate the length of the string and allocate enough memory
    size_t len = strlen(s) + 1;  // +1 for the null terminator
    char* duplicate = malloc(len * sizeof(char));

    if (duplicate == NULL) {
        return NULL; // Return NULL if memory allocation failed
    }

    // Copy the content of the original string to the new memory location
    strcpy(duplicate, s);
    return duplicate;
}


