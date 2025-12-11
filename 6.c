#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int buffer;
sem_t empty;
sem_t full;

void* produtor(void* arg)
{
  for (int i = 0; i <= 10; i++)
  {
    sem_wait(&empty);
    buffer = i;
    sem_post(&full);
    sleep(1);
  }
  return NULL;
}

void* consumidor(void* arg) 
{
  for(int i = 0; i <= 10; i++) 
  {
    sem_wait(&full);
    printf("%d\n", buffer);
    fflush(stdout);
    sem_post(&empty);
    sleep(1);
  }
  return NULL;
}

int main() 
{
  sem_init(&empty, 0, 1);
  sem_init(&full, 0, 0);
  pthread_t p, c;
  pthread_create(&p, NULL, produtor, NULL);
  pthread_create(&c, NULL, consumidor, NULL);
  pthread_join(p, NULL);
  pthread_join(c, NULL);
  sem_destroy(&empty);
  sem_destroy(&full);
  return 0;
}

