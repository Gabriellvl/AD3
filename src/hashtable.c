//
// Created by Gabriel Van Langenhove on 21/10/2024.
//

#include "../include/hashtable.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 1024
#define BUCKET_CAPACITY 64

struct Bucket
{
    char **keys;
    size_t num_keys;
};

struct HashTable
{
    struct Bucket **buckets;
    size_t size;
    size_t num_entries;
};

void hashtable_resize(HashTable* table);
void resize_bucket(struct Bucket* bucket);

HashTable* hashtable_init()
{
    HashTable *table = malloc(sizeof(HashTable));
    table->size = INITIAL_SIZE;
    table->num_entries = 0;

    table->buckets = malloc(table->size * sizeof(struct Bucket *));
    for (size_t i = 0; i < table->size; i++)
    {
        table->buckets[i] = malloc(sizeof(struct Bucket));
        table->buckets[i]->keys = malloc(BUCKET_CAPACITY * sizeof(char *));
        table->buckets[i]->num_keys = 0;
    }
    return table;
}

void hashtable_free(HashTable *table) {
    for (size_t i = 0; i < table->size; i++) {
        struct Bucket *bucket = table->buckets[i];
        for (size_t j = 0; j < bucket->num_keys; j++) {
            free(bucket->keys[j]);
        }
        free(bucket->keys);
        free(bucket);
    }
    free(table->buckets);
    free(table);
}

size_t hashtable_size(HashTable *table) {
    return table->num_entries;
}

// djb2 hashfunctie
// http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *key) {
    if (key == NULL || strlen(key) == 0)
    {
        return 0;
    }
    unsigned int hashval = 5381;
    int c;
    while ((c = *key++)) {
        hashval = ((hashval << 5) + hashval) + c;  // hashval = hashval * 33 + c
    }
    return hashval;
}

// Functie om de index te berekenen op basis van de hashwaarde
unsigned int get_bucket_index(HashTable *table, const char *key) {
    return hash(key) % table->size;
}

bool hashtable_add(HashTable *table, const char *key) {
    if (key == NULL || hashtable_search(table, key))
        return false;  // Sleutel bestaat al, voeg niet opnieuw toe

    unsigned int index = get_bucket_index(table, key);
    struct Bucket *bucket = table->buckets[index];

    // Als de bucket vol is, moet de tabel worden vergroot
    if (bucket->num_keys >= BUCKET_CAPACITY) {
        hashtable_resize(table);
        return hashtable_add(table, key);  // Probeer opnieuw na resizing
    }

    // Voeg de sleutel toe aan de bucket
    bucket->keys[bucket->num_keys++] = my_strdup(key);
    table->num_entries++;
    return true;
}

void hashtable_resize(HashTable *table) {
    size_t new_size = table->size * 2;
    struct Bucket **new_buckets = malloc(new_size * sizeof(struct Bucket *));

    // Maak nieuwe buckets
    for (size_t i = 0; i < new_size; i++) {
        new_buckets[i] = malloc(sizeof(struct Bucket));
        new_buckets[i]->keys = malloc(BUCKET_CAPACITY * sizeof(char *));
        new_buckets[i]->num_keys = 0;
    }

    // Verdeel de bestaande sleutels opnieuw
    for (size_t i = 0; i < table->size; i++) {
        struct Bucket *bucket = table->buckets[i];
        for (size_t j = 0; j < bucket->num_keys; j++) {
            char *key = bucket->keys[j];
            unsigned int new_index = hash(key) % new_size;
            new_buckets[new_index]->keys[new_buckets[new_index]->num_keys++] = key;
        }
        free(bucket->keys);
        free(bucket);
    }

    free(table->buckets);  // Oude buckets vrijgeven
    table->buckets = new_buckets;
    table->size = new_size;
}

bool hashtable_search(const HashTable *table, const char *key) {
    if (key == NULL)
        return false;

    unsigned int index = get_bucket_index((HashTable *)table, (char *)key);
    struct Bucket *bucket = table->buckets[index];

    // Zoek door de bucket
    for (size_t i = 0; i < bucket->num_keys; i++) {
        if (strcmp(bucket->keys[i], key) == 0) {
            return true;  // Sleutel gevonden
        }
    }
    return false;  // Sleutel niet gevonden
}






