// simple_hashing.h

#if ! defined (SIMPLE_HASHING_H)
#define SIMPLE_HASHING_H 1

#include "list_ref.h"
#include <stdbool.h>

#define DEFAULT_CELL_REF "NULL"

struct cell {
    char* ref ;
    struct list L;
};

typedef int hashing_function (char*);

#define HASHING_SIZE 4999

struct hashing_table {
    struct cell table [HASHING_SIZE];
    hashing_function* hashing;
};

extern void init_hashing_table (struct hashing_table*, hashing_function*);

extern void clear_hashing_table (struct hashing_table*);

extern void insert_hashing_table (struct hashing_table*, char*, char*);

extern int search_in_hashing_table (struct hashing_table*, char*, char*);

extern void print_hashing_table (struct hashing_table*);

extern int nbelem_hashing_table (struct hashing_table*) ;

extern char** get_keys_from_hashing_table (struct hashing_table*) ;


#endif
