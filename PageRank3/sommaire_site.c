//sommaire_site.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sommaire_site.h"

int size_sommaire ;

void init_sommaire (char** sommaire_site) {
    
    size_sommaire = 0 ;
    sommaire_site = (char**) malloc (sizeof(char*)) ;
}

int rechercher_sommaire (struct table* A, char** sommaire_site, char* site) {
    
    int id ;
    id = A->tab[(A->hash(site))].ref ;

    if (id != -1) /*&& (id < size_sommaire))*/ {
//         if (strcmp(sommaire_site[id], site)==0) 
            return id ;
//         else
//             return 0 ;
    } else 
        return -1 ;
}

int ajout_sommaire (struct table* A, char** sommaire_site, char* site) {
       
    int id ;
    id = A->tab[(A->hash(site))].ref ;
    
    if (id == -1) {
        size_sommaire +=1 ;
        A->tab[(A->hash(site))].ref = size_sommaire ;
        sommaire_site = (char**) realloc(sommaire_site, size_sommaire*sizeof(char*)) ;
//         sommaire_site[size_sommaire-1] = strdup(site) ;
        sommaire_site[size_sommaire-1] = (char*) malloc(/*(strlen(site)+1)*/40*sizeof(char)) ;
//         for (int j=0 ; site[j] !='\0' ; j++) {
//             sommaire_site[size_sommaire][j] = site[j] ;
//         }
        strcpy(sommaire_site[size_sommaire-1], site) ;
//         for (int i=0 ; i < size_sommaire ; i++) {
//             printf("id %d :: %s\n", size_sommaire, sommaire_site[size_sommaire]) ;
//         }
//         printf("\n%d\t%s\t%s\n", size_sommaire-1,site, sommaire_site[size_sommaire-1]) ;
        return size_sommaire ;
    } else 
        return 0 ;
}

void imprimer_sommaire (char** sommaire_site) {
    int i = 0 ;
    printf("\nSOMMAIRE SITE \n") ;
    for (i=0 ; i < size_sommaire ; i++) {
        printf("id %d :: \n", i) ;
    }
}

void clear_sommaire (char** sommaire_site) {
//     for (int i=0; i < size_sommaire ; i++) {
//         free(sommaire_site[i]) ;
//     }
    free(sommaire_site) ;
    
}
