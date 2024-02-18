// list_ref.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_ref.h"

void init_list (struct list* L) {
    L->nbelem = 0;
    L->head = NIL;
    L->tail = NIL;
}

void add_to_head_list (struct list* L, char* d) {

    struct node* N;

    N = (struct node*) malloc (sizeof (struct node));

    N->ref = strdup(d);
    N->next = L->head;

    L->nbelem += 1;
    L->head = N;

    // Case of first insert
    if (L->tail == NIL)
        L->tail = N;
}

void add_sorted_list  (struct list* L, char* d) {

    struct node *M, *N;

    M = L->head;
    N = M ;
    while ((M != NIL) && (strcmp(M->ref,d)<0)) {
        N=M ;
        M=M->next ;
    }

    struct node* I;

    I = (struct node*) malloc (sizeof (struct node));

    I->ref = strdup(d);
    I->next = M ;

    if (N != NIL)
        N->next = I ;
    else
        L->head= I ;

    L->nbelem += 1;

    // Case of adding at the end of the list
    if (M == NIL)
        L->tail = I;
}

void add_to_tail_list (struct list* L, char* d) {

    struct node *M, *N;

    M = (struct node*) malloc (sizeof (struct node));
    M->ref = strdup(d);
    M->next = NIL;

    if (L->nbelem == 0) {
        L->head = M;
        L->tail = M;
    } else {
        N = L->tail;
        N->next = M;
        L->tail = M;
    }
    L->nbelem += 1;
}

void clear_list (struct list* L) {

    struct node *M, *S;

    M = L->head;
    while (M != NIL) {
        S = M->next;
        free (M);
        M = S;
    }
}

void print_list (struct list* L) {

    struct node* M;

    printf ("[ ");
    M = L->head;
    while (M != NIL) {
        printf ("'%s' ", M->ref);
        M = M->next;
    }
    printf ("]\n");
}

int search_in_list (struct list* L, char* d) {

    struct node *M ;

    M = L->head;
    while ((M != NIL) && (strcmp(M->ref, d) != 0)) {
        M = M->next;
    }
    return (M != NIL && strcmp(M->ref, d) == 0);
}
