// utils.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"

int get_index_value(char** list, int size, char* value) {
    for (int i = 0; i < size; i++) {
        if (strcmp(list[i], value) == 0) {
            return i;
        }
    }
    return -1;
}

void build_squared_matrix (double** matrix, int size) {
    for(int i=0;i<size;i++)
        matrix[i]=(double*)malloc(size*sizeof(double));
    for(int i=0;i<size;i++) {
        for (int j=0;j<size;j++) {
            matrix[i][j] = 0 ;
        }
    }
}

void clear_squared_matrix(double** matrix, int size) {
    for(int i=0;i<size;i++)
        free(matrix[i]);
    free(matrix) ;
}

double* multiply_scalar_with_vector (double scalar, double* vector, int size){
    for(int i=0;i<size;i++){
        vector[i]=scalar*vector[i];
    }
    return vector ;
}

double* mutliply_matrix_with_vector (double** matrix, double* vector, int size){
    double* result = (double*) malloc (size*sizeof(double));
    for(int i=0;i<size;i++){
        result[i]=0;
    }
    for(int i=0;i<size;i++){
        result[0]=result[0]+matrix[0][i]*vector[i];
    }
    for(int i=1;i<size;i++){
        for(int j=0;j<size;j++){
            result[i]=result[i]+matrix[i][j]*vector[j];
        }
    }
    return(result);
}

double* normalize_vector (double* vector, int size){
    double sum = vector[0];
    for(int i=1;i<size;i++){
        sum = sum + vector[i];
    }
    for(int i=0;i<size;i++){
        vector[i]=vector[i]/sum;
    }
    return vector;
}

void sort_index (int* sorted_index, double* vector, int size) {
    int already_sorted_index[size] ;
    double max;
    int index;
    for (int i=0 ; i<size ; i++) {
        already_sorted_index[i] = 0 ;
    }
    for (int i=0 ; i<size ; i++) {
        index = -1 ;
        max = -1.0;
        for (int j=0 ; j<size ; j++) {
            if (already_sorted_index[j]==0) {
                if (vector[j]>max) {
                    index=j ;
                    max=vector[j] ;
                }
            }
        }
        if (index != -1) {
            already_sorted_index[index]=1 ;
            sorted_index[i]=index;
        }
    }
}

double difference_vector_vector (double* a,double* b, int size){

    double difference = fabs(a[0]-b[0]);
    for(int i=1;i<size;i++){
        difference = difference + fabs(a[i]-b[i]);
    }
    printf("Convergence index : %.10lf\n\n", difference);

    return difference;
}
