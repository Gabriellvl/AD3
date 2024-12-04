//
// Created by Gabriel Van Langenhove on 04/12/2024.
//

#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>

void* init_datastructure(const char* type);

bool add_to_datastructure(void* ds, const char* key, const char* type);

bool search_in_datastructure(const void* ds, const char* key, const char* type);

void free_datastructure(void* ds, const char* type);

#endif //STRUCTS_H
