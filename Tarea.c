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

void insertar(struct HashTable* ht, int x) {
    int index = ht->h(x, ht->n);
    if (ht->bucket[index] == NULL) {
        ht->bucket[index] = (int*)malloc(sizeof(int));
        ht->bucket[index][0] = x;
    } else {
        int count = 0;
        while (ht->bucket[index][count] != 0) {
            count++;
            ht->bucket[index] = (int*)realloc(ht->bucket[index], (count + 1) * sizeof(int));
        }
        ht->bucket[index][count] = x;
    }
}

int eliminar(struct HashTable* ht, int x) {
    int index = ht->h(x, ht->n);
    if (ht->bucket[index] != NULL) {
        int count = 0;
        while (ht->bucket[index][count] != 0) {
            if (ht->bucket[index][count] == x) {
                int deleted = ht->bucket[index][count];
                for (int i = count; ht->bucket[index][i] != 0; i++) {
                    ht->bucket[index][i] = ht->bucket[index][i + 1];
                }
                return deleted;
            }
            count++;
        }
    }
    return -1;
}

int encontrar(struct HashTable* ht, int x) {
    int index = ht->h(x, ht->n);
    if (ht->bucket[index] != NULL) {
        int count = 0;
        while (ht->bucket[index][count] != 0) {
            if (ht->bucket[index][count] == x) {
                return ht->bucket[index][count];
            }
            count++;
        }
    }
    return -1;
}

int Modulo_1(int x, int n) {
    return x % n;
}

int Aleatorio_Fn(int x, int n) {
    return rand() % n;
}

int main()
{
    printf("Hello World");

    return 0;
}
