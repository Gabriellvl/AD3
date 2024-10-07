#ifndef UNIEKE_CYCLISCHE_STRINGS_TRIE_H
#define UNIEKE_CYCLISCHE_STRINGS_TRIE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Trie Trie;

Trie* trie_init();

void trie_free(Trie*);

bool trie_search(const Trie*, const char*);

bool trie_add(Trie*, const char*);

size_t trie_size(Trie*);

#endif
