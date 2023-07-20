#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void MatrizQuadrado(int **A, int **B, int **R, int **R2, int L, int C, int threads) 
{
    int i, j, k;
    omp_set_num_threads(threads);

    #pragma omp parallel for shared(A, R) private(i, j, k)
    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
            R[i][j] = 0;
            for (k = 0; k < C; k++) {
                R[i][j] += A[i][k] * A[k][j];
            }
        }
    }

    #pragma omp parallel for shared(B, R2) private(i, j, k)
    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
            R2[i][j] = 0;
            for (k = 0; k < C; k++) {
                R2[i][j] += B[i][k] * B[k][j];
            }
        }
    }
}

void dif(int **A, int **B, int **R, int **R2, int L, int C, int threads) 
{
    int i, j;
    omp_set_num_threads(threads);

    MatrizQuadrado(A, B, R, R2, L, C, threads);
    #pragma omp parallel for shared(R, R2) private(i, j)
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            R[i][j] = R[i][j] - R2[i][j];
        }
    }
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
    double start_time, run_time;
    int L, C, threads;

    printf("Número de linhas: ");
    scanf("%d", &L);
    printf("Número de colunas: ");
    scanf("%d", &C);
    printf("Número de threads: ");
    scanf("%d", &threads);

    int **A, **B, **R, **R2;
    int i, j;

    int numThreads = 8;
    start_time = omp_get_wtime();
    omp_set_num_threads(numThreads);

    A = (int **)malloc(L * sizeof(int *)); 
    for (i = 0; i < L; i++) A[i] = (int *)malloc(C * sizeof(int));
   
    B = (int **)malloc(L * sizeof(int *)); 
    for (i = 0; i < L; i++) B[i] = (int *)malloc(C * sizeof(int));

    R = (int **)malloc(L * sizeof(int *)); 
    for (i = 0; i < L; i++) R[i] = (int *)malloc(C * sizeof(int));

    R2 = (int **)malloc(L * sizeof(int *)); 
    for (i = 0; i < L; i++) R2[i] = (int *)malloc(C * sizeof(int));

    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
            A[i][j] = rand() % 10 + 1;
            B[i][j] = rand() % 10 + 1;
        }
    }
    //printMatriz(A, L, C);
    //printf("\n");
    //printMatriz(B, L, C);
    //printf("\n");
    dif(A, B, R, R2, L, C, threads);

    //printMatriz(R, L, C);

    run_time = omp_get_wtime() - start_time;
    printf("%lf s\n", run_time);
    
    for (i = 0; i < L; i++) {
        free(A[i]);
        free(B[i]);
        free(R[i]);
        free(R2[i]);
    }

    free(A);
    free(B);
    free(R);
    free(R2);

    return 0;
}
