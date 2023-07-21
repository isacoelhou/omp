#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void QuadradoandDiferenca(double **A, double **B, double **R, int L, int C) 
{
    int i, j;
    double resultado_soma_dif = 0.0;

    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
        A[i][j] = A[i][j] * A[i][j];
        }
    }

    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
        B[i][j] = B[i][j] * B[i][j];
        }
    }

    //função realocada para calcular a diferença
    //excluindo uma das funções
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
    int L, C;
    printf("Número de linhas: ");
    scanf("%d", &L);
    printf("Número de colunas: ");
    scanf("%d", &C);

    double time_spent = 0.0;
    clock_t begin = clock();


    printf("\n");
    double **A, **B, **R, **R2;
    int i, j;


    A = (double **)malloc(L * sizeof(double *));
    for (i = 0; i < L; i++) A[i] = (double *)malloc(C * sizeof(double));
   
    B = (double **)malloc(L * sizeof(double *));
    for (i = 0; i < L; i++) B[i] = (double *)malloc(C * sizeof(double));

    R = (double **)malloc(L * sizeof(double *));
    for (i = 0; i < L; i++)     R[i] = (double *)malloc(C * sizeof(double));

    R2 = (double **)malloc(L * sizeof(double *));
    for (i = 0; i < L; i++) 
        R2[i] = (double *)malloc(C * sizeof(double));
    
   
    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
            A[i][j] = rand() %10 + 1;
            B[i][j] = rand() %10 + 1;
    }}
    //printMatriz(A, L, C);
    //printMatriz(B, L, C);

    QuadradoandDiferenca(A, B, R, L, C);

    //printf("Resultado:\n");
    //printMatriz(R, L, C);
    

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
