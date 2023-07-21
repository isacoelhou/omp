#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void QuadradoandDiferenca(double **A, double **B, double **R, int L, int C, int threads) 
{
    int i, j;
    double resultado_soma_dif = 0.0;

    omp_set_num_threads(threads);


    #pragma omp parallel for shared(A, i) private(j)
    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
        A[i][j] = A[i][j] * A[i][j];
        }
    }

    #pragma omp parallel for shared(B, i) private(j)
    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
        B[i][j] = B[i][j] * B[i][j];
        }
    }

    //função realocada para calcular a diferença
    //excluindo uma das funções
    #pragma omp parallel for shared(R, i) firstprivate(A, B) private(j)
    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
        R[i][j] = A[i][j] - B[i][j];
        }
    }

    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
            resultado_soma_dif += R[i][j];
        }
    }

    //printf("A soma das diferenças é %.1lf\n", resultado_soma_dif);
}

void printMatriz(double **matriz, int L, int C)
{
    int i, j;
    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++){
            printf("%lf ", matriz[i][j]);
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

    double **A, **B, **R;
    int i, j;

    start_time = omp_get_wtime();
    //omp_set_num_threads(threads);

    A = (double **)malloc(L * sizeof(double *)); 
    for (i = 0; i < L; i++) 
        A[i] = (double *)malloc(C * sizeof(double));
    B = (double **)malloc(L * sizeof(double *)); 
    for (i = 0; i < L; i++) 
        B[i] = (double *)malloc(C * sizeof(double));
    R = (double **)malloc(L * sizeof(double *)); 
    for (i = 0; i < L; i++) 
        R[i] = (double *)malloc(C * sizeof(double));

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
    QuadradoandDiferenca(A, B, R, L, C, threads);

    //printMatriz(R, L, C);

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
