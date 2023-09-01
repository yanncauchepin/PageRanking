// hachage_simple.h

#if ! defined (HACHAGE_SIMPE_H)
#define HACHAGE_SIMPE_H 1

#include "liste_ref.h"
#include <stdbool.h>

struct alveole 
{
    int ref ;
    struct liste L;
};

typedef int fonction_hachage (char*);

#define SIZE_HACHAGE 4999

struct table 
{
    struct alveole tab [SIZE_HACHAGE];
    fonction_hachage* hash;
};

extern void init_table (struct table*, fonction_hachage*);

extern void clear_table (struct table*);

extern void enregistrer_table (struct table*, char*, int);

extern int rechercher_table (struct table*, char*, int);

extern void imprimer_table (struct table*);

#endif
