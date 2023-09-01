//lecture_tsv.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lecture_tsv.h"
#define SIZE1 700
#define SIZE2 40


void ajout_link (struct table* T, char** sommaire_site, char* site_hub, char* site_aut) {
    
    int id_hub, id_aut ;
//     
    id_hub = rechercher_sommaire (T, sommaire_site, site_hub) ;
    id_aut = rechercher_sommaire (T, sommaire_site, site_aut) ;
//     
    if (id_hub == -1)
        id_hub = ajout_sommaire (T, sommaire_site, site_hub) ;
    if (id_aut == -1)
        id_aut = ajout_sommaire (T, sommaire_site, site_aut) ;
    if ((id_hub == 0) || (id_aut ==0))
        printf("\n\n ERREUR : COLLISION DE HACHAGE \n\n") ;
//     else  
        printf("%d %d\n", id_hub, id_aut) ;
//         enregistrer_table (T, site_hub, id_aut) ;

}

void get_links_from_liste (struct table* T, char** sommaire_site, char* liste) {
    
    char* site = strtok(liste, ";") ;
    char** hist ;
    hist = (char**) malloc(sizeof(char*[SIZE2])) ;
    hist[0] = site ;
    site = strtok(NULL, ";") ;
    int compt = 0 ;
    int size = 1 ;
    int i_aut = 0 ;
    int i_hub = 0 ;
    
    while (site != NULL) {

        if (strcmp (site,"<") != 0) {
            size +=1 ;
            i_aut = size-1 ;
            i_hub = i_aut -1 ;
            hist = (char**) realloc(hist, size*sizeof(char*[SIZE2])) ;
            hist[size-1] = site ;
            site = strtok(NULL, ";") ;
            ajout_link (T, sommaire_site, hist[i_hub], hist[i_aut]) ;
        }
        else {
            i_hub =i_aut-compt ;
            while ((strcmp(site,"<")==0) && (site != NULL)) { 
                compt +=1 ;
                i_hub -=1 ; 
                site = strtok(NULL, ";") ;
            }
            if (strcmp(site,"<")!=0) {
                size +=1 ;
                i_aut = size-1 ;
                hist = (char**) realloc(hist, size*sizeof(char*[SIZE2])) ;
                hist[size-1] = site ;
                site = strtok(NULL, ";") ;
                ajout_link (T, sommaire_site, hist[i_hub], hist[i_aut]) ;
            }           
        }
    }
    printf("\n") ;
    free (hist) ;
}

void get_struct_from_tsv (struct table* T, char** sommaire_site, FILE* fichier) {
       
    char buffer[SIZE1] = " " ;
    
    while (fgets(buffer, SIZE1, fichier) !=NULL ) {
        
        if (buffer[0]!='#') {
            
            char donnee1[SIZE2] ;
            double donnee2 ;
            int donnee3 ;
            char liste[SIZE1] ;
            char donnee5[SIZE2] ;
            sscanf(buffer, "%s %lf %d %s %s", donnee1, &donnee2, &donnee3, liste, donnee5) ;
            get_links_from_liste (T, sommaire_site, liste) ;
           
        }
    }    
}

