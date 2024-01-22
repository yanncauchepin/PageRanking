// utils.h

#if ! defined (UTILS_H)
#define UTILS_H 1

extern int get_index_value (char**, int, char*) ;

extern void build_squared_matrix(double**, int) ;

extern void clear_squared_matrix (double**, int) ;

extern double* multiply_scalar_with_vector (double, double*, int) ;

extern double* mutliply_matrix_with_vector (double**, double*, int) ;

extern double* normalize_vector (double*, int) ;

extern void sort_index(int*, double*, int) ;

extern double difference_vector_vector (double*, double*, int) ;

#endif
