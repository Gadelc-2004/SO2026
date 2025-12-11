#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

sem_t forks[5];

void* philosopher(void* arg)
{
  int id = *(int*)arg;
  while(1)
  {
    printf("Filosofo %d pensando\n", id);
    sleep((rand()%3)+1);
    if(id % 2 == 0)
    {
      sem_wait(&forks[id]);
      sem_wait(&forks[(id+1)%5]);
    } else 
    {
      sem_wait(&forks[(id+1)%5]);
      sem_wait(&forks[id]);
    }
    printf("Filosofo %d comendo\n", id);
    sleep((rand()%2)+1);
    sem_post(&forks[id]);
    sem_post(&forks[(id+1)%5]);
  }
  return NULL;
}

int main()
{
  srand(time(NULL));
  for(int i = 0; i < 5; i++)
  {
    sem_init(&forks[i], 0, 1);
  }
  pthread_t t[5];
  int ids[5];
  for(int i = 0; i < 5; i++) {
    ids[i] = i;
    pthread_create(&t[i], NULL, philosopher, &ids[i]);
  }
  for(int i = 0; i < 5; i++)
  {
    pthread_join(t[i], NULL);
  }
  for(int i = 0; i < 5; i++)
  {
    sem_destroy(&forks[i]);
  }
  return 0;
}
