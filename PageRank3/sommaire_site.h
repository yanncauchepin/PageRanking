//sommaire_site.h

#if ! defined (SOMMAIRE_SITE_H)
#define SOMMAIRE_SITE_H 1

#include "hachage_simple.h"

extern void init_sommaire (char**) ;

extern int rechercher_sommaire (struct table* A, char**, char* site) ;

extern int ajout_sommaire (struct table* A,  char**, char* site) ;

extern void clear_sommaire (char**) ;

#endif
