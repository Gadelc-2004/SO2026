#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int buffer[5];
int in = 0;
int out = 0;
sem_t mutex;
sem_t empty;
sem_t full;

void* produtor(void* arg)
{
  int id = *(int*)arg;
  while (1) 
  {
    int item = rand()%100;
    sem_wait(&empty);
    sem_wait(&mutex);
    buffer[in] = item;
    in = (in + 1) % 5;
    sem_post(&mutex);
    sem_post(&full);
    printf("Produtor %d inseriu %d\n", id, item);
    sleep((rand()%3)+1);
  }
  return NULL;
}

void* consumidor(void* arg) 
{
  int id = *(int*)arg;
  while (1) 
  {
    sem_wait(&full);
    sem_wait(&mutex);
    int item = buffer[out];
    out = (out + 1) % 5;
    sem_post(&mutex);
    sem_post(&empty);
    printf("Consumidor %d retirou %d\n", id, item);
    sleep((rand()%3)+1);
  }
  return NULL;
}

int main()
{
  srand(time(NULL));
  sem_init(&mutex, 0, 1);
  sem_init(&empty, 0, 5);
  sem_init(&full, 0, 0);
  pthread_t p[2], c[2];
  int pid[2] = {1,2};
  int cid[2] = {1,2};
  for (int i = 0; i < 2; i++)
  {
    pthread_create(&p[i], NULL, produtor, &pid[i]);
    pthread_create(&c[i], NULL, consumidor, &cid[i]);
  }
  for (int i = 0; i < 2; i++)
  {
    pthread_join(p[i], NULL);
    pthread_join(c[i], NULL);
  }
  sem_destroy(&mutex);
  sem_destroy(&empty);
  sem_destroy(&full);
  return 0;
}

