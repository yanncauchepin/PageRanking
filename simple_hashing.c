// simple_hashing.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "simple_hashing.h"

void init_hashing_table (struct hashing_table* A, hashing_function* hashing) {
    for (int i=0; i<HASHING_SIZE; i++)  {
        A->table[i].ref = DEFAULT_CELL_REF ;
        init_list (&(A->table[i].L)) ;
    }
    A->hashing = hashing ;
}

void clear_hashing_table (struct hashing_table* A) {
    for(int i=0; i<HASHING_SIZE; i++) {
        A->table[i].ref = DEFAULT_CELL_REF ;
        clear_list (&(A->table[i].L)) ;
    }
}

void insert_hashing_table (struct hashing_table* A, char* key, char* ref) {
    int hash = A->hashing(key) ;

    // Check if key and ref are identical
    if (strcmp(key, ref) == 0) {
      fprintf(stderr, "Error : key and ref cannot be identical.\n");
      return ;  // Exit the function in case of an error
    }

    // Check if the table at index hash is already referenced under another string
    if (strcmp(A->table[hash].ref, DEFAULT_CELL_REF) != 0 && strcmp(A->table[hash].ref, key) != 0) {
      fprintf(stderr, "Hashing error : the table at index %d is already referenced under the key %s.\n", hash, A->table[hash].ref);
      return ;  // Exit the function in case of an error
    }

    if (strcmp(A->table[hash].ref, DEFAULT_CELL_REF) == 0) {
        A->table[hash].ref = strdup(key) ;
    }

    add_to_head_list (&(A->table[hash].L), ref) ;
}

int search_in_hashing_table (struct hashing_table* A, char* key, char* ref) {
    return search_in_list ( &(A->table[(A->hashing(key))].L), ref) ;
}

void print_hashing_table (struct hashing_table* A) {
    printf("\nHASHING TABLE :\n\n") ;
    for (int i=0;i<HASHING_SIZE;i++) {
        if (A->table[i].L.nbelem>0) {
            printf("Cell %d | key '%s' : ", i, A->table[i].ref) ;
            print_list (&(A->table[i].L)) ;
            printf("\n") ;
        }
    }
}

int nbelem_hashing_table (struct hashing_table* A) {
    int nbelem = 0 ;
    for (int i=0;i<HASHING_SIZE;i++) {
        if (A->table[i].L.nbelem>0) {
            nbelem++ ;
        }
    }
    return nbelem ;
}

char** get_keys_from_hashing_table (struct hashing_table* A) {
    int nbelem = nbelem_hashing_table(A);

    if (nbelem == 0) {
        return NULL;
    }

    char** keys = (char**)malloc(nbelem * sizeof(char*));
    if (keys == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    int key_index = 0;
    for (int i = 0; i < HASHING_SIZE; i++) {
        if (A->table[i].L.nbelem > 0) {
            keys[key_index] = strdup(A->table[i].ref);
            key_index++;
        }
    }

    return keys;
}
