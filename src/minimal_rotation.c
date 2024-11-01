//
// Created by Gabriel Van Langenhove on 09/10/2024.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Functie voor het vinden van de lexicografisch kleinste rotatie met Booth's Algorithm
int booth(const char *s) {
    const int n = strlen(s);
    char doubled[2 * n + 1]; // Maak een dubbele string s + s
    strcpy(doubled, s);
    strcat(doubled, s);

    int f[2 * n];  // Array om "failure links" bij te houden
    memset(f, -1, sizeof(f));  // Initialiseer de array met -1

    int k = 0;  // Index van de lexicografisch kleinste rotatie
    for (int j = 1; j < 2 * n; j++) {
        int sj = doubled[j];
        int i = f[j - k - 1];

        // Zoek naar de juiste plek om te vergelijken
        while (i != -1 && sj != doubled[k + i + 1]) {
            if (sj < doubled[k + i + 1]) {
                k = j - i - 1;
            }
            i = f[i];
        }

        // Update de failure link
        if (sj != doubled[k + i + 1]) {
            if (sj < doubled[k]) {
                k = j;
            }
            f[j - k] = -1;
        } else {
            f[j - k] = i + 1;
        }
    }

    return k;
}

char* lexicographically_minimal_string_rotation(const char *input) {
    const int len = strlen(input);
    const int min_index = booth(input);

    // Dynamically allocate memory for the result
    char *rotation = (char*)malloc((len + 1) * sizeof(char));
    if (rotation == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Create the smallest rotation
    for (int i = 0; i < len; i++) {
        rotation[i] = input[(min_index + i) % len];
    }
    rotation[len] = '\0';  // Null-terminate the string

    return rotation;
}

