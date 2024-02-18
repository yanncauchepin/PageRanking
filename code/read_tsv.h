// read_tsv.h

#if ! defined (READ_TSV_H)
#define READ_TSV_H 1

 /*
 * Allows reading the tsv file and creating the following data structure, representing the transition matrix of the internet pages graph:
 * - Hash table taking the char of a hub site as a key and storing its unique identifier int along with the list of unique identifier ints of websites it links to.
 * - Array containing the char of a website at the int-index of the array equivalent to its unique identifier in int.
 */

#include "simple_hashing.h"
#include <stdio.h>

typedef struct {
    char* source;
    char* destination;
} Link;

extern Link* read_tsv (FILE*, int*) ;

extern Link* extract_links(const char*, int*) ;

extern void print_links (Link*, int) ;

#endif
