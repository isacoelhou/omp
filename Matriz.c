#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void dif(int **A, int **B, int **R, int L, int C) 
{
    int i, j;
    for (i = 0; i < L; i++) 
    {
        for (j = 0; j < C; j++) 
        {
            int square_A = A[i][j] * A[i][j];
            int square_B = B[i][j] * B[i][j];
            R[i][j] = square_A - square_B;
        }
    }
}

void printMatriz(int **matriz, int L, int C) 
{
    int i, j;
    for (i = 0; i < L; i++) 
    {
        for (j = 0; j < C; j++) 
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() 
{
        srand(time(NULL));
    int L, C;
    printf("N de L: ");
    scanf("%d", &L);
    printf("N de C: ");
    scanf("%d", &C);
     
    double time_spent = 0.0;
    clock_t begin = clock();

    printf("\n"); 
    int **A, **B, **R;
    int i, j;

    A = (int **)malloc(L * sizeof(int *));
    B = (int **)malloc(L * sizeof(int *));
     R = (int **)malloc(L * sizeof(int *));
    for (i = 0; i < L; i++) {
        A[i] = (int *)malloc(C * sizeof(int));
        B[i] = (int *)malloc(C * sizeof(int));
        R[i] = (int *)malloc(C * sizeof(int));
    }

    for (i = 0; i < L; i++) {
        for (j = 0; j < C; j++) {
            A[i][j] = rand() %10 + 1;
            B[i][j] = rand() %10 + 1;
    }}
   


    dif(A, B, R, L, C);
       clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%lf segundos\n", time_spent);
    //printMatriz(R, L, C);
    for (i = 0; i < L; i++) 
    {
        free(A[i]);
        free(B[i]);
        free(R[i]);
    }

    free(A);
    free(B);
    free(R);
    return 0;
}
