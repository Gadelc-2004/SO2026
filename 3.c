#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

sem_t vagas;

void* carro(void* arg) 
{
  int id = *(int*)arg;
  printf("Carro %d esperando vaga\n", id);
  sem_wait(&vagas);
  printf("Carro %d estacionou\n", id);
  int s = (rand()%3)+1;
  sleep(s);
  printf("Carro %d saindo\n", id);
  sem_post(&vagas);
  return NULL;
}

int main() 
{
  srand(time(NULL));
  sem_init(&vagas, 0, 3);
  pthread_t t[8];
  int ids[8];
  for (int i = 0; i < 8; i++) 
  {
    ids[i] = i+1;
    pthread_create(&t[i], NULL, carro, &ids[i]);
    usleep(50000);
  }
  for (int i = 0; i < 8; i++) 
  {
    pthread_join(t[i], NULL);
  }
  sem_destroy(&vagas);
  return 0;
}

