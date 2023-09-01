//hachage_simple.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hachage_simple.h"

#define SIZE_HACHAGE 4999


void init_table (struct table* A, fonction_hachage* fonct) {
    for (int i=0; i<SIZE_HACHAGE; i++)  {
        A->tab[i].ref = -1 ;
        init_liste (&(A->tab[i].L)) ;    
    }
    A->hash = fonct ;
}

void clear_table(struct table* A) {
    for(int i=0; i<SIZE_HACHAGE; i++) {
        clear_liste (&(A->tab[i].L)) ;
    }
}

void enregistrer_table (struct table* A, char* site, int cible) {
    ajout_trier_liste ( &(A->tab[(A->hash(site))].L), cible) ;
}

int rechercher_table (struct table* A, char* site, int cible) {
    return recherche_liste ( &(A->tab[(A->hash(site))].L), cible) ;
}

void imprimer_table (struct table*A) {
    printf("\n TABLE DE HACHAGE \n") ;
    for (int i=0;i<SIZE_HACHAGE;i++) {
        if (A->tab[i].L.nbelem!=0) {
            printf("Alvéole %d (ref : %d) :: \t", i, A->tab[i].ref) ;
            imprimer_liste (&(A->tab[i].L)) ;
            printf("\n") ;
        }
    }
}

