#ifndef UNIEKE_CYCLISCHE_STRINGS_SEARCHTREE_H
#define UNIEKE_CYCLISCHE_STRINGS_SEARCHTREE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct SearchTree SearchTree;

SearchTree* searchtree_init();

void searchtree_free(SearchTree*);

bool searchtree_search(const SearchTree*, const char*);

bool searchtree_add(SearchTree*, const char*);

size_t searchtree_size(SearchTree*);

#endif
