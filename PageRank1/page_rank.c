#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STRING 40
#define SIZE_BUFFER 1000000
#define SIZE_BUFFER2 150

void lecture_fichier(FILE* fp, char** node, double** matrix, int lines) {

    char buffer[SIZE_BUFFER];
    char *token;
    int i = 0;
    int j = 0 ;
    fgets(buffer, sizeof(buffer), fp); //1ere ligne, noms des noeuds
    token = strtok(buffer, " \n");
    j=0;
    while (token) {
        strcpy(node[j], token) ;
        ++j;
        token = strtok(NULL, " \n");
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        j = 0;
        token = strtok(buffer, " \n");
        while (token) {
            matrix[i][j] = atof(token);
            ++j;
            token = strtok(NULL, " \n");
        }
        ++i;
    }
}

int size_matrix(FILE* fp) {

    int c, lines=-1; //On ne compte pas la ligne contenant les noms des noeuds
    while((c = fgetc(fp)) != EOF) {
        if(c == '\n')
            lines++;
    }
    rewind(fp);
    return lines ;

}

void build_matrix(double** matrix, int lines) {

    for(int j=0;j<lines;j++)
        matrix[j]=(double*)malloc(lines*sizeof(double));
}


void clear_matrix(double** matrix, int lines) {

    for(int j=0;j<lines;j++)
        free(matrix[j]);
    free(matrix) ;
}

void affichage_matrix (double** matrix, int taille) {

    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            printf("%.3lf ", matrix[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}

void build_node (char** node, int lines) {

    for(int j=0;j<lines;j++)
        node[j]=(char*)malloc(MAX_STRING);

}

void clear_node (char** node, int lines) {

    for(int j=0;j<lines;j++)
        free(node[j]);
    free(node);
}

void affichage_node (char** node, int taille) {

    for (int i = 0; i < taille ; i++) {
        printf("%d :: %s \n", i, node[i]);
    }
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

void trier_indice(int* ind, double* vec, int size) {

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
        if(indice != -1) {
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

int main(int argc, char* argv[]) {

    /* Lecture de fichier_________________________________________________________________________________________________*/

    if (argc < 2) {
        printf("Erreur, format attendu: %s fichier.txt\n", argv[0]); // ?
        exit(EXIT_FAILURE);
    }
    FILE *fp;
    fp = fopen(argv[1],"r");
    if ( fp == NULL ){
        puts ("Acces au fichier impossible");
    }
    int lines = size_matrix(fp) ;
    double** matrix = (double **)malloc(lines*sizeof(double*));
    build_matrix(matrix, lines) ;
    char** node = (char **)malloc(lines*sizeof(char*)) ;
    build_node(node, lines) ;
    lecture_fichier(fp, node, matrix, lines) ;
    fclose(fp);

    //affichage_node(node,10) ;
    //affichage_matrix(matrix,10) ;
    /*Fin de lecture du fichier_________________________________________________________________________________________________*/

    /*Algorithme Pagerank_________________________________________________________________________________________________*/
    //Initialisation du paramÃƒÂ©trage pagerank

    double beta;
    printf("Entrer la valeur du parametre beta, entre 0 et 1 : ") ;
    scanf("%lf", &beta) ;
    printf("%.3lf \n",beta);
    double diff;
    int diffp ;
    printf("\nEntrer la puissance p de l'indice de convergence seuil 10e-p : ") ;
    scanf("%d", &diffp) ;
    diff = pow(10,(-1)*diffp);
    printf("%.10lf \n", diff) ;

    //Initialisation du vecteur initial

    double* q=(double*)malloc(lines*sizeof(double));
    int value ;
    printf("\nPreciser pageranking classique (0) ou personnalise (1) : ") ;
    scanf("%d", &value) ;
    int nb ;
    int* perso;
    if (value==0) {
        for (int i=0;i<lines;i++){
            q[i] = 1.0/lines;
        }
        nb=lines;
    }
    else if (value==1) {
        printf("\nPreciser le nombre de pages a personnaliser : ") ;
        scanf("%d", &nb) ;
        perso=(int*)malloc(nb*sizeof(int));
        for(int i=0;i<nb;i++){
        	printf("\nDonner l'indice de la page %d a personnaliser : ",i+1) ;
        	scanf("%d", &perso[i]) ;
        }
        printf("%d \n",perso[0]);
        for(int i=0;i<lines;i++){
            q[i] = 0;
        }
        for(int i=0;i<nb;i++){
        	q[perso[i]] = 1.0/nb ;
        }
        fflush( stdout );
        printf("%.3lf \n",q[36]);
    }
    printf("\n") ;

    //Initialisation des derniers paramÃƒÂ¨tres

    double constante = (1.0-beta)/nb; // (1-beta / N)
    double* q_prec=(double*)malloc(lines*sizeof(double)); //q_precedent donc q(k-1)
    memmove (q_prec, q, lines*sizeof(double)); // Copie de q dans q_prec (donc q(k-1) = q(k))

    //Algorithme pagerank

    double somme ;
    int iter = 0;
    do{
        memmove (q_prec, q, lines*sizeof(double)); // Copie de q dans q_prec (donc q(k-1) = q(k))

        //Ajout du premier terme de q

        q = prod_scal_vec(beta,prod_mat_vec(matrix,q_prec, lines), lines) ;

        // Calcul somme q_prec[i]

        somme = 0;
        for(int j=0;j<lines;j++){
            somme = somme + q_prec[j];
        }
        somme = somme*constante;

        //Ajout du second terme de q

        if (value==1) {
        for (int k=0 ; k<nb ; k++) {
            q[perso[k]] = q[perso[k]] + somme ;
        }
    }
    else {
    	for (int k=0 ; k<lines ; k++) {
            q[k] = q[k] + somme ;
        }
    }

        // Normalisation q

        q=normalize_vec(q,lines);
        iter++;
        printf("Iteration : %d\n",iter);
    }while(diff_vec_vec(q,q_prec,lines) > diff );
    printf("\n\n") ;

    //Affichage des sites ayant les plus gros scores

    int* ind_trier=(int*)malloc(lines*sizeof(int));
    trier_indice(ind_trier, q, lines) ;
    printf("Les 20 sites ayant les meilleurs rangs :\n\n") ;
    for(int i=0 ; i<20 ; i++) {
        printf("\t%s (%d) :: %.6lf\n", node[ind_trier[i]], ind_trier[i], q[ind_trier[i]]);
    }
    printf("\n\n") ;

    /*Fin de l'algorithme Pagerank_________________________________________________________________________________________________*/

    FILE * fsortie;
    fsortie = fopen("vecteur.txt", "w");
    if(fsortie == NULL){
        printf("Creation du fichier impossible\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<lines;i++){
        fprintf(fsortie, "%s \"%.15lf\n\"",node[i],q[i]);
    }
    fclose(fsortie);
    if (value==1)
        free(perso) ;
    free(ind_trier) ;
    free(q) ;
    free(q_prec) ;

    //clear_matrix(matrix, lines) ;

    //clear_node(node,lines) ;

    return(0);
}
