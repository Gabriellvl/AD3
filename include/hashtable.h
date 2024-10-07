#ifndef UNIEKE_CYCLISCHE_STRINGS_HASHTABLE_H
#define UNIEKE_CYCLISCHE_STRINGS_HASHTABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct HashTable HashTable;

HashTable* hashtable_init();

void hashtable_free(HashTable*);

bool hashtable_search(const HashTable*, const char*);

bool hashtable_add(HashTable*, const char*);

size_t hashtable_size(HashTable*);

#endif
