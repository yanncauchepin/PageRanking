//main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list_ref.h"
#include "read_tsv.h"
#include "utils.h"
#include "simple_hashing.h"

// TO DO LIST
// Check whether there are website which are include into destination but not present in hashing_table due to lack of link to others websites.
// Check whether we have to change columns and row in the building of transition_matrix
// Check for a better hashing function and how to handle error in hashing, maybe size of hashing
// Check how to free allocated memory of transition_matrix without having double free or corruption abordet core dumped
// data test.tsv works but there is errors with paths_finished.tsv -> produced by free hashing table

void monitor_initialisation (double* damping_factor, double* threshold, double* q, int size, int* custom, char** list_custom, int* init_number, char** websites) {

    printf("Enter the value of the damping factor, between 0 and 1 : ") ;
    scanf("%lf", damping_factor) ;
    printf("\n") ;

    int pow_ ;
    printf("Enter the power p of the convergence threshold index 10e-p : ") ;
    scanf("%d", &pow_) ;
    *threshold = pow(10,(-1)*pow_);
    printf("\n") ;

    printf("Specify classical pageranking (0) or customized (1) : ") ;
    scanf("%d", custom) ;
    while (*custom!=0 && *custom !=1) {
        printf("\nError. Must be either equal to 0 or 1.\n") ;
        printf("Specify classical pageranking (0) or customized (1) : ") ;
        scanf("%d", custom) ;
    }
    printf("\n") ;

    if (*custom==0) {
        for (int i=0;i<size;i++){
            q[i] = 1.0/size;
        }
        *init_number = size;
    } else {
        *init_number = 0 ;
        char website[256] ;
        printf("Enter a website name to customized. Enter 'None' to stop : ") ;
        fgets(website, sizeof(website), stdin);
        //website[strcspn(website, "\n")] = '\0';
        printf("\n") ;
        while (strcmp(website, "None") != 0) {
            printf("Enter a website name to customized. Enter 'None' to stop : ") ;
            fgets(website, sizeof(website), stdin);
            //website[strcspn(website, "\n")] = '\0';
            printf("\n") ;
            if (get_index_value(websites, size, website) != -1) {
                (*init_number) ++ ;
                list_custom = (char**) realloc (list_custom, *init_number*sizeof(char*));
                list_custom[*init_number-1] = strdup(website) ;
            } else {
                printf("Website not include in data.\n") ;
            }
        }
        for(int i=0;i<size;i++){
            q[i] = 0;
        }
        for (int i=0; i<*init_number; i++) {
            int k = get_index_value(websites, size, list_custom[i]) ;
            q[k] = 1.0/ *init_number ;
        }
        printf("Number of customized websites : %d.\n", *init_number) ;
  }


}

void fill_transition_matrix (double** matrix, int size, struct hashing_table* T, char** websites) {
    int j ;
    for (int i=0; i<size; i++) {
        char* website_source = strdup(websites[i]) ;
        int hash = T->hashing(website_source) ;
        int nbelem = T->table[hash].L.nbelem ;
        if (nbelem > 0) {
            struct node* node = T->table[hash].L.head ;
            while (node != NIL) {
                char* website_destination = node->ref ;
                j = get_index_value(websites, size, website_destination) ;
                matrix[i][j] = 1/nbelem ;
                node = node->next ;
            }
        }
    }
}

int hashing (char* website) {

    int i = 0 ;
    int hash = 0 ;
    for (i = 0 ; website[i]!='\0' ; i++) {
        hash += website[i] ;
    }
    hash %= HASHING_SIZE ;

    return hash ;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
       // Not enough arguments provided, display a message and exit
       printf("Usage : %s <file_name>\n", argv[0]);
       return 1;
    }

    FILE *file = fopen(argv[1], "r") ;

    if (file == NULL) {
        printf("Unable to open the file.\n");

    } else {

        // READING FILE TSV
        printf("\n> READING FILE TSV\n") ;

        struct hashing_table T ;
        init_hashing_table (&T, &hashing) ;

        int link_count = 0;
        Link* links = read_tsv(file, &link_count) ;
        //print_links(links, link_count) ;

        for (int i = 0; i < link_count; i++) {
            if (search_in_hashing_table(&T, links[i].source, links[i].destination)==0)
                insert_hashing_table(&T, links[i].source, links[i].destination) ;
        }
        for (int i=0;i<link_count;i++) {
            free(links[i].source) ;
            free(links[i].destination) ;
        }
        //print_hashing_table (&T) ;

        // BUILD DATA
        printf("\n> BUILD DATA\n") ;

        int size = nbelem_hashing_table(&T) ;
        char** websites = get_keys_from_hashing_table(&T);

        double** transition_matrix = (double**) malloc (size*sizeof(double*));
        build_squared_matrix(transition_matrix, size) ;

        fill_transition_matrix(transition_matrix, size, &T, websites) ;

        // ERROR
        //clear_hashing_table (&T) ;

        // INITIALISATION
        printf("\n> INITIALISATION\n") ;

        double damping_factor ;
        double constant_factor ;
        double threshold ;
        int custom ;
        char** list_custom = NULL ;
        int init_number ;
        double* q = (double*) malloc (size*sizeof(double));
        double* q_prec = (double*) malloc (size*sizeof(double));

        monitor_initialisation (&damping_factor, &threshold, q, size, &custom, list_custom, &init_number, websites) ;

        constant_factor = (1.0-damping_factor)/init_number ;

        // PAGERANKING
        printf("\n> PAGERANKING\n") ;
        printf("\n") ;

        double sum ;
        int iteration = 0;

        do {

            memmove (q_prec, q, size*sizeof(double));

            // Adding the first term of q
            q = multiply_scalar_with_vector (damping_factor, mutliply_matrix_with_vector(transition_matrix,q_prec, size), size) ;

            // Computing sum q_prec[i]
            sum = 0;
            for (int i=0;i<size;i++){
                sum = sum + q_prec[i];
            }
            sum = sum*constant_factor;

            // Adding the second term of q
            if (custom==1) {
                for (int i=0 ; i<init_number ; i++) {
                    int k = get_index_value(websites, size, list_custom[i]) ;
                    q[k] = q[k] + sum ;
                }
            } else {
                for (int i=0 ; i<size ; i++) {
                      q[i] = q[i] + sum ;
                  }
            }

            // Normalization of q
            q = normalize_vector (q,size);
            iteration++ ;

            printf("Iteration : %d\n", iteration);

        } while (difference_vector_vector(q, q_prec, size) > threshold);

        // DISPLAY RESULTS
        printf("\n> DISPLAY RESULTS\n") ;

        // Display websites with the highest scores
        int* sorted_index = (int*) malloc (size*sizeof(int));
        sort_index(sorted_index, q, size) ;
        printf("Top 20 websites with the best ranks : \n") ;
        for (int i=0 ; i<20 ; i++) {
            printf("\t%s (%d) :: %.6lf\n", websites[sorted_index[i]], sorted_index[i], q[sorted_index[i]]);
        }
        printf("\n") ;

        // Load sorted results in an output file
        FILE * file_output ;
        file_output = fopen("output.txt", "w");
        printf("Loading sorted results in an output file.\n") ;
        if (file_output == NULL) {
            printf("Unable to create the output file.\n");
        } else {
            for (int i=0;i<size;i++) {
                fprintf(file_output, "%s \"%.8lf\n\"", websites[sorted_index[i]],q[sorted_index[i]]);
            }
        }
        fclose(file_output);

        // CLEARING ALLOCATED MEMORY
        printf("\n> CLEARING ALLOCATED MEMORY\n") ;

        free(list_custom) ;
        free(sorted_index) ;
        free(q) ;
        free(q_prec) ;
        // ERROR
        //clear_squared_matrix(transition_matrix, size) ;
        for (int i=0;i<size;i++) {
            free(websites[i]) ;
        }
    }
    fclose(file) ;

    return 0;
}
