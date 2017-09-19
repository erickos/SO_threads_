#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#define NT 10
#define SIZE 100

pthread_mutex_t mutex;
int counter=1;
int matriz[SIZE][NT];

int somaColuna[NT];

void imprime_matriz(){
	int i, j;

	for(j=0;j<NT;j++){
		//printf("%d\t", matriz[j][i]);
		printf( "Soma da coluna  %d (thread %d) = %d\n", j, j, somaColuna[j]);
	}
	printf("\n");
}

void* inicializa_matriz(void *p){
	int i, j, n, soma;
	n = (int)(size_t)p;
	pthread_mutex_lock(&mutex);	
	for(j=0;j<SIZE;j++)
	{
		matriz[j][n] = rand()%100;
		somaColuna[n] += matriz[j][n];
	}
	pthread_mutex_unlock(&mutex);	
	pthread_exit(NULL);
}

int main(int argc, char **argv) {
  int i;
  pthread_t tid[NT];

  pthread_mutex_init(&mutex, NULL);

  srand(time(NULL));


  for(i=0;i<NT;i++)
  	pthread_create(&tid[i], NULL, inicializa_matriz, (void *)(size_t) i);
  for(i=0;i<NT;i++)
  	pthread_join(tid[i], NULL);

  imprime_matriz();

  pthread_mutex_destroy(&mutex);	

  return 0;

}
