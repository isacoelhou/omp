#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void MatrizQuadrado(int **A, int **B, int **R, int **R2, int L, int C) 
{
    int i, j, k;

    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
            R[i][j] = 0;
            for (k = 0; k < C; k++) {
                R[i][j] += A[i][k] * A[k][j];
            }}}

    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
            R2[i][j] = 0;
            for (k = 0; k < C; k++) {
                R2[i][j] += B[i][k] * B[k][j];
            }}}
}

void dif(int **A, int **B, int **R, int **R2, int L, int C) 
{
    MatrizQuadrado(A, B, R, R2, L, C);
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            R[i][j] = R[i][j] - R2[i][j];
        }}
}

void printMatriz(int **matriz, int L, int C)
{
    int i, j;
    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    int L, C;
    printf("Número de linhas: ");
    scanf("%d", &L);
    printf("Número de colunas: ");
    scanf("%d", &C);

    double time_spent = 0.0;
    clock_t begin = clock();


    printf("\n");
    int **A, **B, **R, **R2;
    int i, j;


    A = (int **)malloc(L * sizeof(int *));
    for (i = 0; i < L; i++) A[i] = (int *)malloc(C * sizeof(int));
   
    B = (int **)malloc(L * sizeof(int *));
    for (i = 0; i < L; i++) B[i] = (int *)malloc(C * sizeof(int));

    R = (int **)malloc(L * sizeof(int *));
    for (i = 0; i < L; i++)     R[i] = (int *)malloc(C * sizeof(int));

    R2 = (int **)malloc(L * sizeof(int *));
    for (i = 0; i < L; i++) 
        R2[i] = (int *)malloc(C * sizeof(int));
    
   
    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
            A[i][j] = rand() %10 + 1;
            B[i][j] = rand() %10 + 1;
    }}
    printMatriz(A, L, C);
    printMatriz(B, L, C);

    dif(A, B, R, R2, L, C);

    printf("Resultado:\n");
    printMatriz(R, L, C);
    

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%lf segundos\n", time_spent);


    for (i = 0; i < L; i++) {
        free(A[i]);
        free(B[i]);
        free(R[i]);
    }

    free(A);
    free(B);
    free(R);

    return 0;
}
