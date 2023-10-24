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
        ht->bucket[index] = (int*)malloc(2 * sizeof(int));
        ht->bucket[index][0] = x;
        ht->bucket[index][1] = 0;
    } else {
        int count = 0;
        while (ht->bucket[index][count + 1] != 0) {
            count++;
        }
        ht->bucket[index] = (int*)realloc(ht->bucket[index], (count + 2) * sizeof(int));
        ht->bucket[index][count] = x;
        ht->bucket[index][count + 1] = 0;
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

int (*RandomHashFun(int M, int n))(int, int) {
    int *fnTable = (int*)malloc(M * sizeof(int));
    for (int x = 0; x < M; x++) {
        fnTable[x] = Aleatorio_Fn(x, n);
    }
    
    int randomHash(int x, int n) {
        return fnTable[x];
    }
    
    return randomHash;
}
int main()
{
    int M1 = Modulo_1(5, 10);
    int M2 = Modulo_1(15, 10);
    int M3 = Modulo_1(123456, 10);
    printf("Modulo_1 de M1 = %d\n", M1);
    printf("Modulo_1 de M2 = %d\n", M2);
    printf("Modulo_1 de M3 = %d\n", M3);
    struct HashTable* ht1 = initHashTable(Modulo_1, 10);
    insertar(ht1, 5);
    insertar(ht1, 15);
    int elemento = encontrar(ht1, 15);
    printf("Elemento encontrado en ht1: %d\n", elemento);
    int elemento_eliminado = eliminar(ht1, 15);
    printf("Elemento eliminado en ht1: %d\n", elemento_eliminado);
    int elemento2 = encontrar(ht1, 15);
    printf("Elemento encontrado en ht1: %d\n", elemento2);

    printf("\n");

    int R1 = Aleatorio_Fn(52, 10);
    int R2 = Aleatorio_Fn(1234567, 10);
    printf("Aleatorio_Fn de R1 = %d\n", R1);
    printf("Aleatorio_Fn de R2 = %d\n", R2);
    struct HashTable* ht2 = initHashTable(Aleatorio_Fn, 10);
    insertar(ht2, 1234567);
    int encontrado1 = encontrar(ht2, 1234567);
    printf("Elemento encontrado en ht2: %d\n", encontrado1);
    
    printf("\n");

    int M = 100000;
    int (*randomFn2)(int) = RandomHashFun(M);
    int resultado1 = randomFn2(52);
    int resultado2 = randomFn2(324);
    printf("Resultado 1: %d\n", resultado1);
    printf("Resultado 2: %d\n", resultado2);
    return 0;
}
