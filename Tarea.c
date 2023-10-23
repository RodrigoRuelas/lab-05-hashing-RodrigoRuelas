#include <stdio.h>
#include <stdlib.h>

struct HashTable {
    int n;
    int (*h)(int, int);
    int **bucket;
};

struct HashTable* initHashTable(int (*hashFn)(int, int), int n) {
    struct HashTable* ht = (struct HashTable*)malloc(sizeof(struct HashTable));
    ht->n = n;
    ht->h = hashFn;
    ht->bucket = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        ht->bucket[i] = NULL;
    }
    return ht;
}

int main()
{
    printf("Hello World");

    return 0;
}
