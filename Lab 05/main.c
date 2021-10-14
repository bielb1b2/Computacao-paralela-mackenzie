/*
  Gabriel Vitor de Souza - 41908961
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;
int x[3] = {2,4,6};
int y[3];
int A[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};

int m = 3;
int n = 3;

void *Pth_mat_vect(void* rank){
  long my_rank = (long) rank;
  int i, j;

  int local_m = m/thread_count;
  int my_first_row = my_rank*local_m;
  int my_last_row = (my_rank+1)*local_m - 1;
  
  for(i = my_first_row; i <= my_last_row; i++){
    y[i] = 0.0;
    for(j = 0; j < n; j++){
      y[i] += A[i][j]*x[j];

    }
  }
  return NULL;
} 

int main(int argc, char* argv[])
{

    long thread;
    pthread_t* thread_handles;

    thread_count = 3;
    thread_handles = malloc(thread_count*sizeof(pthread_t));

    for(thread = 0; thread < thread_count; thread++){
      pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void*) thread);
    }

    printf("Hello from the main thread\n");

        for(thread = 0;thread < thread_count;thread++)
    {
        pthread_join(thread_handles[thread],NULL);
    }

    free(thread_handles);


    for(int i = 0; i < thread_count; i++){ //Imprime valores de y
      printf("Linha %d = ", i);
      printf("%d\n", y[i]);
    
    }

    return 0;
}