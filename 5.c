#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int chegadas = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
sem_t barreira;

void* worker(void* arg) 
{
  int id = *(int*)arg;
  int s = (rand()%3)+1;
  sleep(s*2);
  printf("Thread %d: Processando Parte A...\n", id);
  pthread_mutex_lock(&m);
  chegadas++;
  if(chegadas == 4) 
  {
    printf("4 chegadas\n");
    for (int i = 0; i < 4; i++) 
    {
      sem_post(&barreira);
    }
  }
  pthread_mutex_unlock(&m);
  sem_wait(&barreira);
  printf("Thread %d: Processando Parte B...\n", id);
  return NULL;
}

int main() 
{
  srand(time(NULL));
  sem_init(&barreira, 0, 0);
  pthread_t t[4];
  int ids[4];
  for (int i = 0; i < 4; i++) 
  {
    ids[i] = i+1;
    pthread_create(&t[i], NULL, worker, &ids[i]);
  }
  for (int i = 0; i < 4; i++) 
  {
    pthread_join(t[i], NULL);
  }
  sem_destroy(&barreira);
  return 0;
}

