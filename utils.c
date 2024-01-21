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

double* prod_scal_vec (double a, double*x, int size_x){
    for(int i=0;i<size_x;i++){
        x[i]=a*x[i];
    }
    return (x);
}

double* prod_mat_vec(double** m, double*x,int N){
    double* temp=(double*)malloc(N*sizeof(double));
    for(int j=0;j<N;j++){
        temp[j]=0;
    }
    for(int j=0;j<N;j++){
        temp[0]=temp[0]+m[0][j]*x[j];
    }
    for(int i=1;i<N;i++){
        for(int j=0;j<N;j++){
            temp[i]=temp[i]+m[i][j]*x[j];
        }
    }
    return(temp);
}

double* normalize_vec(double*x, int N){
    double somme = x[0];
    for(int i=1;i<N;i++){
        somme = somme + x[i];
    }
    for(int i=0;i<N;i++){
        x[i]=x[i]/somme;
    }
    return(x);
}

void sort_index(int* ind, double* vec, int size) {
    int ind_deja_tire[size] ;
    double max;
    int indice;
    for (int i=0 ; i<size ; i++) {
        ind_deja_tire[i] = 0 ;
    }
    for (int i=0 ; i<size ; i++) {
        indice = -1 ;
        max=-1.0;
        for (int j=0 ; j<size ; j++) {
            if (ind_deja_tire[j]==0) {
                if (vec[j]>max) {
                    indice=j ;
                    max=vec[j] ;
                }
            }
        }
        if(indice != -1)
        {
            ind_deja_tire[indice]=1 ;
            ind[i]=indice;
        }
    }
}

double diff_vec_vec(double*a,double*b,int lines){

    double diff=fabs(a[0]-b[0]);
    for(int i=1;i<lines;i++){
        diff = diff + fabs(a[i]-b[i]);
    }
    printf("Indice de convergence : %.10lf\n\n", diff);

    return(diff);
}
