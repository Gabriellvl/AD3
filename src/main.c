#include "../include/cyclic.h"
#include "../include/struct_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>

#define MAX_LINE_LENGTH 4096
#define BATCH_SIZE 250 // 250 * 4097 = 1 024 250; < 1 048  576 = 1 MiB

// Function to handle command-line argument and select the appropriate data structure
void process_line(void* structure, const char* datastructuur, char* line);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <datastructuur>\n", argv[0]);
        return 1;
    }

    // Initialize the data structure based on command-line argument
    const char* type = argv[1];
    void* structure = init_datastructure(type);

    if (structure == NULL) {
        fprintf(stderr, "Failed to initialize the data structure\n");
        return 1;
    }

    // Batch buffer to store lines
    char* lines[BATCH_SIZE];
    int line_count = 0;

    // Buffer to store the input lines
    char line[MAX_LINE_LENGTH + 1];

    // Read lines from stdin
    while (fgets(line, sizeof(line), stdin))
    {
        // Remove newline character
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // Store the line in the batch
        lines[line_count++] = my_strdup(line);

        if (line_count >= BATCH_SIZE)
        {
            for (int i = 0; i < BATCH_SIZE; i++)
            {
                process_line(structure, type, lines[i]);
                free(lines[i]);
            }
            line_count = 0;
        }
    }

    // process the last remaining lines
    for (int i = 0; i < line_count; i++)
    {
        process_line(structure, type, lines[i]);
        free(lines[i]);
    }

    free_datastructure(structure, type);

    return 0;
}

void process_line(void* structure, const char* datastructuur, char* line) {
    char* minimal_rotation = lexicographically_minimal_string_rotation(line);

    if (!search_in_datastructure(structure, minimal_rotation, datastructuur)) {
        // Print the original line and add the rotation to the data structure
        printf("%s\n", line);
        add_to_datastructure(structure, minimal_rotation, datastructuur);
    }

    free(minimal_rotation);
}