// liste_ref.h

#if ! defined (LISTE_REF_H)
#define LISTE_REF_H 1

/*
 * Le type struct liste permet de représenter des listes chaînées
 * avec pointeur de queue.
 * - Le champ ref contient la clé unique (int) du site internet (char).
 * - Le champ nbelem contient le score hub du site hub, soit la taille du vecteur cible.
 * La liste vide est codée par tete = queue = NIL et nbelem = 0.
 * Les maillons sont alloués dynamiquement.
 * Le champ suivant du dernier maillon vaut NIL
 */

struct maillon {
    int ref;
    struct maillon* suivant;
};

#define NIL (struct maillon*)0

struct liste {
    struct maillon* tete;
    struct maillon* queue;
    int nbelem;
};

extern void init_liste (struct liste*);

extern void clear_liste (struct liste*);

extern void ajout_en_tete_liste (struct liste*, int);

extern void ajout_trier_liste (struct liste*, int) ;

extern void ajout_en_queue_liste (struct liste*, int);

extern void imprimer_liste (struct liste*);

extern int recherche_liste (struct liste*, int) ;
 
#endif
