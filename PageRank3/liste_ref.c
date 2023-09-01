// liste_ref.c

#include <stdio.h>
#include <stdlib.h>
#include "liste_ref.h"

void init_liste (struct liste* L)
{
    L->nbelem = 0;
    L->tete = NIL;
    L->queue = NIL; // nouveau
}

void ajout_en_tete_liste (struct liste* L, int d)
{   struct maillon* M;

    M = (struct maillon*)malloc (sizeof (struct maillon));

    M->ref = d;
    M->suivant = L->tete;

    L->nbelem += 1;
    L->tete = M;

    //cas nouveau
    if (L->queue == NIL)    
        L->queue = M;       
}

void ajout_trier_liste  (struct liste* L, int d) {
    
    struct maillon *M, *N;
    M = L->tete;
    N = M ;
    while ((M != NIL) && (M->ref<=d)) {
        N=M ;
        M=M->suivant ;
    }
    
    struct maillon* I;

    I = (struct maillon*)malloc (sizeof (struct maillon));

    I->ref = d;
    I->suivant = M ;
    
    if (N != NIL) 
        N->suivant = I ;
    else 
        L->tete = I ;
    
    L->nbelem += 1;

    //cas nouveau
    if (M == NIL)    
        L->queue = I;
}

void ajout_en_queue_liste (struct liste* L, int d)
{   struct maillon* M;
    struct maillon* N;

    M = (struct maillon*)malloc (sizeof (struct maillon));
    M->ref = d;
    M->suivant = NIL;
    
    //cas nouveau
    if (L->nbelem == 0)
    {
        L->tete = M;
        L->queue = M;      
    } else
    {

/*
 * Ancien code, sans pointeur de queue
        N = L->tete;
        while (N->suivant != NIL)
            N = N->suivant;
 */
        N = L->queue;       // nouveau (décommenter le code ci-dessus)
/*
 *    for (int i = 0; i < L->nbelem-1; i++)
 *        N = N->suivant;
 */
// 3.
        N->suivant = M;
        L->queue = M;       // nouveau
    }
// 4.
    L->nbelem += 1;
}

void clear_liste (struct liste* L)
{   struct maillon *M, *S;

    M = L->tete;
    while (M != NIL)
    {   S = M->suivant;
        free (M);
        M = S;
    }
}

void imprimer_liste (struct liste* L)
{   struct maillon* M;

    printf ("[");
/* 1ère version de la boucle
 *  M = L->tete;
 *  for (int i = 0; i < L->nbelem; i++)
 *  {   printf ("%d, ", M->ref);
 *      M = M->suivant;
 *  }
 */
// 2ème version de la boucle
    M = L->tete;
    while (M != NIL)
    {   printf ("%d, ", M->ref);
        M = M->suivant;
    }
/* 3ème version de la boucle
 *  for (M = L->tete; M != NIL; M = M->suivant)
 *      printf ("%d, ", M->ref);
 */
    printf ("]\n");
}

int recherche_liste (struct liste* L, int d) {
    struct maillon *M ;
    M = L->tete;
    while ((M != NIL) && (M->ref<=d))
        M=M->suivant ;
    if (M->ref==d)
        return 1 ;
    else
        return 0 ;
}
