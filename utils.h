// utils.h

#if ! defined (UTILS_H)
#define UTILS_H 1

extern int get_index_value (char**, int, char*) ;

extern void build_squared_matrix(double**, int) ;

extern void clear_squared_matrix (double**, int) ;

extern double* prod_scal_vec (double, double*, int) ;

extern double* prod_mat_vec (double**, double*, int) ;

extern double* normalize_vec (double*, int) ;

extern void sort_index(int*, double*, int) ;

extern double diff_vec_vec (double*, double*, int) ;

#endif
