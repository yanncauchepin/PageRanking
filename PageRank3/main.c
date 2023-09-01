//main.c 

#include <stdio.h>
#include <stdlib.h>
#include "lecture_tsv.h"
#include "hachage_simple.h"
#include "sommaire_site.h"
#include "liste_ref.h"

int hachage (char* site) {
    
    int i = 0 ;
    int nombreHache = 0 ;
    for (i = 0 ; site[i]!='\0' ; i++) {
        nombreHache += site[i] ;
    }
    nombreHache %= SIZE_HACHAGE ;
    
    return nombreHache ;
}

int main(int argc, char *argv[])
{
    // Ouverture du fichier source tsv
    FILE* fichier = NULL;
    fichier = fopen(argv[1], "r");

    if (fichier != NULL){
        
        //Création de la matrice
        struct table T ;
        init_table (&T, &hachage) ;
        
        
        //Création du sommaire 
        char** sommaire_site ;
        init_sommaire(sommaire_site) ;
        
        //Construction de la matrice de transition
        get_struct_from_tsv(&T, sommaire_site, fichier) ;
        
        //Affichage
        imprimer_sommaire(sommaire_site) ;
//         imprimer_table(&T) ;
        
        clear_table (&T) ;
        clear_sommaire (sommaire_site) ;
    }
    else 
        printf("Impossible d'ouvrir le fichier");
    
    fclose(fichier) ;
    
    return 0;
}
