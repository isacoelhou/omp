#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void MatrizQuadrado(int **A, int **B, int **R, int **R2, int L, int C) 
{
    int i, j, k;
    
    #pragma parallel omp for 
    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
            R[i][j] = 0;
            for (k = 0; k < C; k++) {
                R[i][j] += A[i][k] * A[k][j];
            }}}

    #pragma parallel omp for 
    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
            R2[i][j] = 0;
            for (k = 0; k < C; k++) {
                R2[i][j] += B[i][k] * B[k][j];
            }}}}

void dif(int **A, int **B, int **R, int **R2, int L, int C) 
{
    MatrizQuadrado(A, B, R, R2, L, C);
    #pragma parallel omp for 
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            R[i][j] = R[i][j] - R2[i][j];
        }}}

int main(){

    srand(time(NULL));
    double start_time, run_time;
    int L, C;

    printf("Número de linhas: ");
    scanf("%d", &L);
    printf("Número de colunas: ");
    scanf("%d", &C);

    int **A, **B, **R, **R2;
    int i, j;

    int numThreads = 8;
    start_time = omp_get_wtime();
    omp_set_num_threads(8);

    A = (int **)malloc(L * sizeof(int *));
    #pragma parallel omp for 
    for (i = 0; i < L; i++) A[i] = (int *)malloc(C * sizeof(int));
   
    B = (int **)malloc(L * sizeof(int *));
    #pragma parallel omp for 
    for (i = 0; i < L; i++) B[i] = (int *)malloc(C * sizeof(int));

    R = (int **)malloc(L * sizeof(int *));
    #pragma parallel omp for 
    for (i = 0; i < L; i++)     R[i] = (int *)malloc(C * sizeof(int));

    R2 = (int **)malloc(L * sizeof(int *));
    #pragma parallel omp for 
    for (i = 0; i < L; i++) 
        R2[i] = (int *)malloc(C * sizeof(int));

    #pragma parallel omp for 
    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
            A[i][j] = rand() %10 + 1;
            B[i][j] = rand() %10 + 1;
    }}

    dif(A, B, R, R2, L, C);

    run_time = omp_get_wtime() - start_time;
    printf("%lf s\n", run_time);
    
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