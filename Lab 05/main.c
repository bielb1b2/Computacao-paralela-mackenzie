// Gabriel Vitor De Souza
// 41908961

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10

int v[SIZE];

void* multiplyNumber (void *arg) {
  int *valor = (int *)(arg);
  if(*valor == 1){
    printf("Thread 1 Executando...\n");
    for (int i = 0; i < SIZE / 2; i++){
      v[i] = v[i] * 4;
    }
  }
  else {
      printf("Thread 2 Executando...\n");
      for (int i = SIZE / 2; i < SIZE; i++){
      v[i] = v[i] * 4;
    }
  }
  pthread_exit(multiplyNumber);
} 

int main() {
  pthread_t t1, t2;
  int a1 = 1;
  int a2 = 2;

  printf("Insira 10 números: \n");
  for(int i = 0; i < SIZE; i++) {
    
    scanf("%d", &v[i]);
  }

  pthread_create(&t1, NULL, multiplyNumber, (void *)(&a1));
  pthread_create(&t2, NULL, multiplyNumber, (void *)(&a2));

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  for(int i = 0; i < SIZE; i++) {
    printf("%d ", v[i]);
  }

  exit(0);
  
}