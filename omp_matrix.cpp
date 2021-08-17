#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define TAM 2000

int A[TAM][TAM];
int B[TAM][TAM];
int C[TAM][TAM];

int main (void) {
    srand(time(NULL)); 
    struct timeval start, end;
    long mtime, seconds, useconds;
    int line;
    int x;

    // Iniciando valores para A e B
    for(int l = 0; l < TAM; l ++) {
        for(int c = 0; c < TAM; c ++) {
            A[l][c] = (rand()%10) + 1;
            B[l][c] = (rand()%10) + 1;
        }
    }

    gettimeofday(&start, NULL);

    // Computação
#pragma omp parallel for
    for (int loop = 0; loop < TAM; loop++) {
        line = loop;
        for (int c = 0; c < TAM; c++) {
            for (int i = 0; i < TAM; i++) {
                C[line][c] += A[line][i] * B[i][c];
            }
        }
    }

    // Checa o tempo de execução
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Matrizes %d por %d\n", TAM, TAM);
    printf("Tempo de execucao: %ldms\n", mtime);

    return 0;
}