// lecture_tsv.h

#if ! defined (LECTURE_TSV_H)
#define LECTURE_TSV_H 1

/*
 * Permet de lire le fichier tsv et de créer la structure de donnée suivante, représentant la matrice de transition du graphe des pages internet :
 * - Tableau de hachage prenant en paramètre le char d'un site hub et enregistrant son identifiant unique int et la liste des identifiants uniques int de sites aut vers lequel il renvoie.
 * - Tableau contenant le char d'un site à l'indice du tableau int équivalent à identifiant unique en int.
 */

#include "hachage_simple.h"
#include "sommaire_site.h"
#include <stdio.h>

#define SIZE1 700
#define SIZE2 40

extern void ajout_link (struct table*, char**, char* , char*) ;

extern void get_links_from_liste (struct table*, char**, char* ) ;

extern void get_struct_from_tsv (struct table*, char**, FILE* ) ;

#endif 
