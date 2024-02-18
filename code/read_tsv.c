//lecture_tsv.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "read_tsv.h"
#include "simple_hashing.h"

Link* read_tsv (FILE *file, int* total_link_count) {

  char *buffer ;
  size_t buffer_size = 0 ;

  *total_link_count = 0 ;
  int link_count = 0;
  Link* links = NULL;

  while (getline(&buffer, &buffer_size, file) != -1) {
      if (buffer[0]!='#') {
          char first[1024] ;
          double second ;
          int third ;
          char *websites_chain = malloc(buffer_size) ;
          char fifth[1024] ;
          sscanf(buffer, "%1023s %lf %d %s %1023s", first, &second, &third, websites_chain, fifth) ;
          Link* single_links = extract_links(websites_chain, &link_count);
          links = realloc(links, (*total_link_count+link_count) * sizeof(Link)) ;
          memcpy(links + *total_link_count, single_links, link_count * sizeof(Link));
          free(websites_chain) ;
          free(single_links) ;
          *total_link_count += link_count ;
      }
    }
    free(buffer) ;

    return links ;
}

Link* extract_links(const char* input, int* link_count) {

    const char delimiter[] = ";";
    const char backward[] = "<";

    char* websites_chain = strdup(input);
    char* token = strtok(websites_chain, delimiter);
    char** history = NULL;
    int history_count = 0;

    Link* links = NULL;
    *link_count = 0;

    while (token != NULL) {
        if (strcmp(token, backward) == 0) {
            if (history_count > 0) {
                free(history[history_count-1]) ;
                history_count-- ;
            }
        } else {
            if (history_count == 0 ) {
              history = realloc(history, (history_count +1)*sizeof(char*)) ;
              history[history_count] = strdup(token) ;
              history_count++;
            } else {
                links = realloc(links, (*link_count + 1) * sizeof(Link));
                links[*link_count].source = strdup(history[history_count-1]);
                links[*link_count].destination = strdup(token);
                (*link_count)++;

                history = realloc(history, (history_count +1)*sizeof(char*)) ;
                history[history_count] = strdup(token) ;
                history_count++;
            }
        }
        token = strtok(NULL, delimiter);
    }

    free(websites_chain);

    for (int i = 0; i < history_count; i++) {
        free(history[i]);
    }
    free(history);

    return links;
}

void print_links (Link* links, int size) {
    printf("Links :\n");
    for(int i=0; i<size;i++) {
        printf("(%s, %s)\n", links[i].source, links[i].destination);
    }
}
