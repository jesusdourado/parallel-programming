#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

#define TAM 10
#define THREADS 3

int A[TAM][TAM];
int B[TAM][TAM];
int C[TAM][TAM];

void *threadWork(void *arg) {
    int current = (int)(size_t)arg;
    int end;
    int begin = (current * (TAM/THREADS));

    if(current + 1 == THREADS) {
        end = TAM;
    } else {
        end = begin + TAM/THREADS;
    }

    for (int l = begin; l < end; l ++) {
        for(int c = 0; c < TAM; c ++) {
            for(int i = 0; i < TAM; i ++) {
                C[l][c] += A[l][i] * B[i][c];
            }
        }
    }
}

int main (void) {
    srand(time(NULL)); 

    struct timeval start, end;
    long mtime, seconds, useconds;
    pthread_t t[TAM];

    // Iniciando valores para A e B
    for(int l = 0; l < TAM; l ++) {
        for(int c = 0; c < TAM; c ++) {
            A[l][c] = (rand()%10) + 1;
            B[l][c] = (rand()%10) + 1;
        }
    }

    gettimeofday(&start, NULL);

    // Computação
    for (int i = 0; i < THREADS; i ++) {
        pthread_create(&t[i], NULL, threadWork, (void *)i);
    }

    // Esperando as threads finalizarem
    for(int i = 0; i < THREADS; i ++ ) {
        pthread_join(t[i], NULL);
    }

    // Checa o tempo de execução
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Matrizes %d por %d\n", TAM, TAM);
    printf("Quantidade de threads usadas: %d\n", THREADS);
    printf("Tempo de execucao: %ldms\n", mtime);

    return 0;
}